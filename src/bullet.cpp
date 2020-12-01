#include "bullet.h"

Bullet::Bullet(sf::Vector2f pos, bool alien_bullet)
{
    shape = sf::RectangleShape({2, 20});
    shape.setPosition(pos);

    is_alien_bullet = alien_bullet;
    if(is_alien_bullet) {
        shape.setFillColor(sf::Color::Red);
        speed = -speed;
    }
    else
        shape.setFillColor(sf::Color::White);
}

void Bullet::Draw(sf::RenderWindow &window, float deltaTime)
{
    shape.move(0, speed*deltaTime);
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}
