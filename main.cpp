

#include <iostream>
#include "window_manager.h"

using std::cout;
using std::endl;

int main()
{

    int width = 800;
    int height = 600;

    WorldGrid world(width, height);

    vector<pixel> line_1 = compute_line({ 398, 300 }, { 398, 599 });
    vector<pixel> line_2 = compute_line({ 396, 300}, { 399, 599 });
    vector<pixel> line_3 = compute_line({ 404, 300}, { 401, 599 });
    vector<pixel> line_4 = compute_line({ 402, 300}, { 402, 599 });
    vector<pixel> line = compute_line({ 400, 300}, { 400, 599 });

    //world.insert_particle(1599, 899, MaterialID::sand);

    for (int i = 0; i < line.size(); i++)
    {
        world.insert_particle(line[i].x, line[i].y, MaterialID::water);
        world.insert_particle(line_1[i].x, line[i].y, MaterialID::water);
        world.insert_particle(line_2[i].x, line[i].y, MaterialID::water);
        world.insert_particle(line_3[i].x, line[i].y, MaterialID::water);
        world.insert_particle(line_4[i].x, line[i].y, MaterialID::water);
    }

    for (int i = 350; i <= 450; i++)
    {
        for (int j = 100; j <= 150; j++)
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

    sf::RenderWindow window(sf::VideoMode(width, height), "PixelSim");
    //window.setFramerateLimit(60);
    
    sf::Clock clock;
    sf::Time t;
    
    sf::Clock global_clock;
    unsigned long long int frames = 0;

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

        frames++;
    }


    sf::Time run_time = global_clock.getElapsedTime();

    float avg_fps = static_cast<float>(frames) / run_time.asSeconds();

    cout << "Average FPS: " << avg_fps << endl;
    

    return 0;
}