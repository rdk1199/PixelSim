


#include "window_manager.h"


void draw(const WorldGrid& world, sf::RenderWindow& window)
{
    sf::Image image;
    image.create(world.width(), world.height());

    for (int i = 0; i < world.width(); i++)
    {
        for (int j = 0; j < world.height(); j++)
        {
            image.setPixel(i, world.height() -1 - j, world.get_px_col(i ,j));
           // image.setPixel(i, 899 - j, { static_cast<float>(i) / 1600 * 255, 0, static_cast<float>(j) / 1600 * 255 });
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    window.draw(sprite);
}