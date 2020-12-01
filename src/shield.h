#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "utility.h"


#ifndef SHIELD_H
#define SHIELD_H

class Segment {
public:
    Segment(sf::Texture &spritesheet, sf::Vector2f pos, sf::IntRect segment);
    int damage = 4;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};

class Shield
{
public:
    Shield(sf::Texture &spritesheet, sf::Vector2f position);
    void Draw(sf::RenderWindow &window, float deltaTime);
    bool CheckHit(sf::FloatRect bullet);

private:
    std::vector<Segment> segments = {};
    sf::IntRect wholebase = sf::IntRect({562, 13}, {80, 58});
    int cols = 4;
    int rows = 3;
};


#endif // SHIELD_H
