#include <SFML/Graphics.hpp>
#include "Printer.h"
#include "GMath.h"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), L"Новый проект", Style::Default);
    window.setVerticalSyncEnabled(true);
    Level level;
    level.init("LevelInfo/TestLevel.txt");
    
    //реализация камеры
    View camera;
    Vector2f default_size = { 1280.f, 720.f };
    camera.setSize(default_size);
    

    Printer printer(&window, &level);
    
    Vector2i CD = { 0,0 };

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            CD.y = -1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            CD.y = 1;
        }
        else {
            CD.y = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            CD.x = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            CD.x = -1;
        }
        else {
            CD.x = 0;
        }

        level.input(Normalised((Vector2f)CD));
        level.logic();
        camera.setCenter(level.player.body.position);
        if (Length(level.player.body.velocity) != 0) {
            camera.setSize(default_size * (1 + Length(level.player.body.velocity) / 50));
        }
        else if (Length(level.player.body.velocity) == 0) {
            camera.setSize(default_size);
        }
        window.setView(camera);
        printer.draw();
        sleep(milliseconds(10));
    }
    return 0;
}