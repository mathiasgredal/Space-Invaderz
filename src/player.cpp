#include "player.h"

Player::Player(sf::Texture &texture, sf::Vector2f windowSize)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(493, 40, 48, 30));
    sprite.setPosition(windowSize.x*0.5, windowSize.y-55);
}

void Player::Draw(sf::RenderWindow &window, float deltaTime)
{
    // Apply movement
    sprite.move(static_cast<float>(dir)*speed*deltaTime, 0);
    window.draw(sprite);
}

void Player::OnKeyDown(sf::Keyboard::Key key)
{
    if(key == sf::Keyboard::Key::Right)
        dir = 1;
    else if (key == sf::Keyboard::Key::Left)
        dir = -1;

}

void Player::OnKeyUp(sf::Keyboard::Key key)
{    
    if(key == sf::Keyboard::Key::Right && dir == 1)
        dir = 0;
    else if (key == sf::Keyboard::Key::Left && dir == -1)
        dir = 0;
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

sf::Vector2f Player::getSize() const
{
    return {sprite.getLocalBounds().width, sprite.getLocalBounds().height};
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}
