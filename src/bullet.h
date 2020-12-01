#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef BULLET_H
#define BULLET_H


class Bullet
{
public:
    Bullet(sf::Vector2f pos, bool alien_bullet = false);
    void Draw(sf::RenderWindow &window, float deltaTime);

    sf::FloatRect getBounds() const;

    bool is_alien_bullet = false;
private:
    sf::RectangleShape shape;
    float speed = -400.f;
};

#endif // BULLET_H
