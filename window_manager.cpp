


#include "window_manager.h"


void draw(const WorldGrid& world, sf::RenderWindow& window)
{
    sf::Image image;
    image.create(1600, 900);

    for (int i = 0; i < 1600; i++)
    {
        for (int j = 0; j < 900; j++)
        {
            image.setPixel(i, 899 - j, world.get_px_col(i ,j));
           // image.setPixel(i, 899 - j, { static_cast<float>(i) / 1600 * 255, 0, static_cast<float>(j) / 1600 * 255 });
        }
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    window.draw(sprite);
}