#include "game.h"

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(Assets);

Game::Game(): player(spritesheet, windowSize)
{
    // Load sprite sheet
    auto fs = cmrc::Assets::get_filesystem();
    auto sprite_file = fs.open("Assets/sprites.png");

    if (!spritesheet.loadFromMemory(sprite_file.begin(), sprite_file.size()))
        throw std::runtime_error("ERROR: Could not load sprites");

    // Initialize window
    window = new sf::RenderWindow(sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Space Invaderz"));
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);
    ImGui::SFML::Init(*window);
    ImGui::GetIO().FontGlobalScale = 1.2;

    // Initialize aliens
    for(int i = 0; i < 5; i++) {
        // Go through each alien type
        float y = 50*i;
        int alien_type;
        if(i == 0)
            alien_type = 0;
        else if (i == 1 || i == 2)
            alien_type = 1;
        else
            alien_type = 2;

        for(int j = 0; j < 11; j++) {
            // Go through 11 aliens on a single row
            float x = 60*j;
            aliens.push_back(Alien(spritesheet, {x, y}, alien_type));
        }
    }

    // Initialize shields
    shields.push_back(Shield(spritesheet, {-530, windowSize.y - 150}));
    shields.push_back(Shield(spritesheet, {-530 + 1*250, windowSize.y - 150}));
    shields.push_back(Shield(spritesheet, {-530 + 2*250, windowSize.y - 150}));
    shields.push_back(Shield(spritesheet, {-530 + 3*250, windowSize.y - 150}));

}

Game::~Game()
{
    ImGui::SFML::Shutdown();
    delete window;
}


int Game::Exec()
{
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyReleased:
                KeyUpEvent(event.key.code);
                break;
            case sf::Event::KeyPressed:
                KeyDownEvent(event.key.code);
                break;
            }
        }

        ImGui::SFML::Update(*window, deltaClock.restart());
        DrawGUI();

        window->clear();
        Draw(*window);
        ImGui::SFML::Render(*window);
        window->display();
    }

    return EXIT_SUCCESS;
}

void Game::Draw(sf::RenderWindow &window)
{
    // Update the gameobjects, perhaps this should happen in a seperate update function
    if(alien_timer.getElapsedTime() > alien_update_interval){
        // Check if all of the aliens can make their next move
        bool canMove = true;
        for(auto alien : aliens) {
            canMove = alien.CanMakeMove(window);
            if(!canMove)
                break;
        }

        // This just moves the aliens down, if we cannot go any further to one side.
        // If we can move then we just call the move function
        for(auto &alien : aliens)
            if(!canMove)
                alien.NextRow();
            else
                alien.Move();

        // Remove hit aliens
        aliens.erase(std::remove_if(aliens.begin(), aliens.end(), [&](const Alien &alien){
            return alien.hit;
        }), aliens.end());        

        // TODO: Possibly check if the aliens have reached the bottom, in which case we have lost

        alien_timer.restart();
    }

    // Shoot bullet from random alien, on the bullet timer
    if(alien_bullet_timer.getElapsedTime() > alien_bullet_interval && aliens.size() != 0) {
        int alien_index = random(0, aliens.size());
        sf::Vector2f bullet_pos = {
            aliens.at(alien_index).getPosition().x + aliens.at(alien_index).getSize().x*0.5f,
            aliens.at(alien_index).getPosition().y + aliens.at(alien_index).getSize().y*0.5f
        };

        bullets.push_back(Bullet(bullet_pos, true));

        alien_bullet_timer.restart();
    }

    // Check if any of the bullets intersects any of the aliens or shields
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet &bullet){        
        bool removed = false;
        for(auto& alien : aliens) {
            if(bullet.getBounds().intersects(alien.getBounds()) && !alien.hit && !bullet.is_alien_bullet) {
                alien.IsHit();
                removed = true;
            }
        }

        for(auto& shield : shields)
            if(shield.CheckHit(bullet.getBounds()) && !removed)
                removed = true;

        return removed;
    }), bullets.end());

    // Check if any of the bullets intersects with the player
    for(const auto& bullet : bullets) {
        if(bullet.getBounds().intersects(player.getBounds()) && bullet.is_alien_bullet)
            Game_Over();
    }


    // Call the draw functions for all the gameobjects
    player.Draw(window, ImGui::GetIO().DeltaTime);

    for(auto& bullet : bullets)
        bullet.Draw(window, ImGui::GetIO().DeltaTime);

    for(auto alien : aliens)
        alien.Draw(window, ImGui::GetIO().DeltaTime);

    for(auto& shield : shields)
        shield.Draw(window, ImGui::GetIO().DeltaTime);
}

void Game::DrawGUI()
{
    ImGui::Begin("Stats");
    ImGui::Text("FPS: %f", 1/ImGui::GetIO().DeltaTime);
    if(aliens.size() == 0)
        ImGui::Text("Game Over");
    ImGui::End();
}

void Game::KeyUpEvent(sf::Keyboard::Key key)
{
    player.OnKeyUp(key);
}

void Game::KeyDownEvent(sf::Keyboard::Key key)
{
    player.OnKeyDown(key);

    if(key == sf::Keyboard::Key::Space)
        bullets.push_back(Bullet({player.getPosition().x + player.getSize().x*0.5f, player.getPosition().y}));
}

void Game::Game_Over()
{
    window->close();
}
