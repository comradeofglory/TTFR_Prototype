#include <SFML/Graphics.hpp>
#include "Printer.h"
#include "GameMath.h"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), L"����� ������", Style::Default);
    window.setVerticalSyncEnabled(true);
    Level level;
    level.init("LevelInfo/TestLevel.txt");
    GameMath math;
    
    //���������� ������
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

        level.input(math.Normalised((Vector2f)CD));
        level.logic();
        camera.setCenter(level.player.center);
        if (math.Length(level.player.velocity) != 0 && camera.getSize() == default_size) {
            camera.zoom(1 + (math.Length(level.player.velocity) / 100));
        }
        else if (math.Length(level.player.velocity) == 0) {
            camera.setSize(default_size);
        }
        window.setView(camera);
        printer.draw();
        sleep(milliseconds(10));
    }
    return 0;
}