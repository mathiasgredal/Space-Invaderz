#include "shield.h"

Segment::Segment(sf::Texture &spritesheet, sf::Vector2f pos, sf::IntRect segment) {
    image.create(segment.width, segment.height);
    image.createMaskFromColor(sf::Color::Black); // This is needed for transparency
    image.copy(spritesheet.copyToImage(), 0, 0, segment, true);


    if (!texture.create(image.getSize().x, image.getSize().y))
        throw std::runtime_error("Error create image segment");
    texture.update(image);

    sprite.setTexture(texture);
    sprite.setPosition(segment.left + pos.x, segment.top + pos.y);
}

sf::IntRect calcSegmentRect(int x, int y, sf::IntRect whole, int rows, int cols) {
    int segment_width = whole.width/cols;
    int segment_height = whole.height/rows;

    return sf::IntRect({
                           whole.left+segment_width*x,
                           whole.top+segment_height*y,
                       }, {
                           segment_width,
                           segment_height
                       });
}

Shield::Shield(sf::Texture &spritesheet, sf::Vector2f position)
{
    for(int x = 0; x < cols; x++) {
        for(int y = 0; y < rows; y++) {
            segments.push_back(Segment(spritesheet, position, calcSegmentRect(x, y, wholebase, rows, cols)));
        }
    }
}

void Shield::Draw(sf::RenderWindow &window, float deltaTime)
{
    for(auto& segment : segments) {
        segment.sprite.setTexture(segment.texture); // Why is this needed
        window.draw(segment.sprite);
    }
}

bool Shield::CheckHit(sf::FloatRect bullet)
{
    for(auto& segment : segments) {
        if(segment.sprite.getGlobalBounds().intersects(bullet)) {
            // On hit we need to remove som random pixels from the segment
            for(unsigned int x = 0; x < segment.image.getSize().x; x++) {
                for(unsigned int y = 0; y < segment.image.getSize().y; y++)
                if(random(0, 2) == 1)
                    segment.image.setPixel(x, y, sf::Color::Transparent);
            }
            segment.texture.update(segment.image);
            segment.damage--;
            return true;
        }
    }

    segments.erase(std::remove_if(segments.begin(), segments.end(), [&](const Segment &segment){
        return segment.damage == 0;
    }), segments.end());

    return false;
}
