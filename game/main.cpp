#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
    Window window(sf::VideoMode(800, 600), "GRA");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;

        while (window.pollEvent(event))
        {
            switch(event.type)
            case Event::Closed:
            {
                window.close();
                break;
            }
            //case... for the future cases
        }
    }


    return 0;
}
