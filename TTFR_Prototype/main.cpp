#include <SFML/Graphics.hpp>
#include "Printer.h"
#include "GameMath.h"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), L"Новый проект", Style::Default);
    window.setVerticalSyncEnabled(true);
    Level level;
    level.init("LevelInfo/TestLevel.txt");
    GameMath math;


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
        printer.draw();
        sleep(milliseconds(10));
    }
    return 0;
}