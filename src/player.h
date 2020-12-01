#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player(sf::Texture &spritesheet, sf::Vector2f windowSize);
    void Draw(sf::RenderWindow &window, float deltaTime);
    void OnKeyDown(sf::Keyboard::Key key);
    void OnKeyUp(sf::Keyboard::Key key);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    int dir = 0; // 1: right, 0: still, -1: left
    float speed = 200.f;
};

#endif // PLAYER_H
