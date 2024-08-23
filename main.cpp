

#include <iostream>
#include "window_manager.h"

using std::cout;
using std::endl;

int main()
{

    WorldGrid world(1600, 900);

    vector<pixel> line_1 = compute_line({ 798, 450 }, { 798, 899 });
    vector<pixel> line_2 = compute_line({ 796, 450 }, { 799, 899 });
    vector<pixel> line_3 = compute_line({ 804, 450 }, { 801, 899 });
    vector<pixel> line_4 = compute_line({ 802, 450 }, { 802, 899 });
    vector<pixel> line = compute_line({ 800, 450 }, { 800, 899 });

    //world.insert_particle(1599, 899, MaterialID::sand);

    for (int i = 0; i < line.size(); i++)
    {
        world.insert_particle(line[i].x, line[i].y, MaterialID::sand);
        world.insert_particle(line_1[i].x, line[i].y, MaterialID::sand);
        world.insert_particle(line_2[i].x, line[i].y, MaterialID::sand);
        world.insert_particle(line_3[i].x, line[i].y, MaterialID::sand);
        world.insert_particle(line_4[i].x, line[i].y, MaterialID::sand);
    }

    for (int i = 700; i <= 900; i++)
    {
        for (int j = 200; j <= 300; j++)
        {
            world.insert_particle(i, j, MaterialID::rock);
        }
    }

    /*
    world.insert_particle(800, 450, MaterialID::sand);
    world.insert_particle(800, 500, MaterialID::sand);
    world.insert_particle(800, 550, MaterialID::sand);
    world.insert_particle(800, 600, MaterialID::sand);
    world.insert_particle(800, 650, MaterialID::sand);
    world.insert_particle(800, 700, MaterialID::sand);
    world.insert_particle(800, 750, MaterialID::sand);
    world.insert_particle(800, 899, MaterialID::sand);
    */

    sf::RenderWindow window(sf::VideoMode(1600, 900), "PixelSim");
    //window.setFramerateLimit(60);
    
    sf::Clock clock;
    sf::Time t;

    while (window.isOpen())
    {
        sf::Event event;
        t = clock.getElapsedTime();
        clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();   
       world.update(t.asSeconds());
       

        draw(world, window);
        window.display();       
    }


    return 0;
}