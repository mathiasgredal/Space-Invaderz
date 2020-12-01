#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef ALIEN_H
#define ALIEN_H


class Alien
{
public:
    Alien(sf::Texture &spritesheet, sf::Vector2f position, int alien_type);
    void Draw(sf::RenderWindow &window, float deltaTime);
    bool CanMakeMove(const sf::RenderWindow &window);
    void NextRow();
    void Move();
    void IsHit();

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::FloatRect getBounds() const;


    sf::Sprite sprite;
    bool hit = false;
private:
    int dir = 1; // 1: right, -1: left
    float moveSize = 30;
    float rowSize = 50;
    int current_frame = 0;
    sf::IntRect frame_0;
    sf::IntRect frame_1;
    sf::IntRect exploding = sf::IntRect(555, 107, 48, 29);
};

#endif // ALIEN_H
