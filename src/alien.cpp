#include "alien.h"

Alien::Alien(sf::Texture &texture, sf::Vector2f pos, int alien_type)
{
    sprite.setTexture(texture);
    switch (alien_type) {
    case 0:
        frame_0 = sf::IntRect(7, 35, 29, 29);
        frame_1 = sf::IntRect(65, 35, 30, 29);
        break;
    case 1:
        frame_0 = sf::IntRect(127, 35, 40, 29);
        frame_1 = sf::IntRect(187, 35, 40, 29);
        break;
    case 2:
        frame_0 = sf::IntRect(259, 35, 44, 30);
        frame_1 = sf::IntRect(317, 35, 44, 30);
        break;
    }

    sprite.setTextureRect(frame_0);
    sprite.setPosition(pos.x, pos.y);
    sprite.setScale(1.1f, 1.1f);
}

void Alien::Draw(sf::RenderWindow &window, float deltaTime)
{
    // Apply textures
    if(current_frame == 0)
        sprite.setTextureRect(frame_0);
    else if (current_frame == 1)
        sprite.setTextureRect(frame_1);

    if (hit)
        sprite.setTextureRect(exploding);
    window.draw(sprite);
}

bool Alien::CanMakeMove(const sf::RenderWindow &window)
{
    if(dir == 1) {
        // Check right side
        if(sprite.getGlobalBounds().left+sprite.getGlobalBounds().width+moveSize > window.getSize().x)
            return false;
    }
    else if (dir == -1) {
        // Check left side
        if(sprite.getGlobalBounds().left-moveSize < 0)
            return false;
    }
    return true;
}

void Alien::NextRow()
{
    sprite.move(0, rowSize);
    dir = -dir;
    current_frame = !current_frame;
}

void Alien::Move()
{
    sprite.move(dir*moveSize, 0);
    current_frame = !current_frame;
}

void Alien::IsHit()
{
    sprite.move(-2, 0);
    hit = true;
}

sf::Vector2f Alien::getPosition() const
{
    return sprite.getPosition();
}

sf::Vector2f Alien::getSize() const
{
    return {sprite.getLocalBounds().width, sprite.getLocalBounds().height};
}

sf::FloatRect Alien::getBounds() const
{
    return sprite.getGlobalBounds();
}
