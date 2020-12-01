#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <random>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "utility.h"
#include "player.h"
#include "bullet.h"
#include "alien.h"
#include "shield.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    ~Game();

    int Exec();
    void Draw(sf::RenderWindow &window);
    void DrawGUI();
    void KeyUpEvent(sf::Keyboard::Key key);
    void KeyDownEvent(sf::Keyboard::Key key);

    void Game_Over();
private:
    sf::Vector2f windowSize = {640*1.4, 480*1.1+80};
    sf::RenderWindow *window = nullptr;
    sf::Clock deltaClock;
    sf::Texture spritesheet;


    sf::Clock alien_timer;
    sf::Clock alien_bullet_timer;
    sf::Time alien_bullet_interval = sf::milliseconds(400);
    sf::Time alien_update_interval = sf::milliseconds(1000);

    // Gameobjects
    Player player;
    std::vector<Bullet> bullets = {};
    std::vector<Alien> aliens = {};
    std::vector<Shield> shields = {};
};

#endif // GAME_H
