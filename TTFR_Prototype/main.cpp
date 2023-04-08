#include <SFML/Graphics.hpp>
#include "Printer.h"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1280, 720), L"Новый проект", Style::Default);
    window.setVerticalSyncEnabled(true);
    Level level;
    level.init("LevelInfo/TestLevel.txt");

    Printer printer(&window, &level);
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        

        printer.draw();
        sleep(milliseconds(11));
    }
    return 0;
}