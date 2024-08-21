

#include <iostream>
#include "window_manager.h"

using std::cout;
using std::endl;

int main()
{

    WorldGrid world(1600, 900);

    world.insert_particle(800, 450, MaterialID::sand);
    world.insert_particle(800, 500, MaterialID::sand);
    world.insert_particle(800, 550, MaterialID::sand);
    world.insert_particle(800, 600, MaterialID::sand);
    world.insert_particle(800, 650, MaterialID::sand);
    world.insert_particle(800, 700, MaterialID::sand);
    world.insert_particle(800, 750, MaterialID::sand);
    world.insert_particle(800, 899, MaterialID::sand);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "PixelSim");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        world.update();
        draw(world, window);
        window.display();
    }


    return 0;
}