#pragma once

#include "Gra.cpp"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//Klasa tworz¹ca grê

class Game
{
private:
	
	//Stworzenie wskaŸnika zawieraj¹cego okno
	RenderWindow* window;
	Event event;


	//Zdarzenie: zamkniêcie okna X
	void pollEvents()
	{
		while (this->window->pollEvent(this->event))
		{

			if(this->event.type == Event::Closed)
			{
				this->window->close();
			}
		}
	}


	void create_window()
	{
		//Utworzenie na wskaŸniku okna gry
		this->window = new RenderWindow(VideoMode(800, 600), "arcade");
		this->window->setFramerateLimit(144);
	}
	
public:
		
	Game()
	{
		//Konstruktor tworzy okno przy utworzeniu obiektu
		this->create_window();
	}
	~Game()
	{
		//Destruktor okno spod wskaŸnika
		delete this->window;
	}


	//Informacja zwrotna o dzia³aniu okna
	const bool get_working()
	{
		return this->window->isOpen();
	}


	void render()
	{
		this->window->clear();

		this->window->display();
	}


	void update()
	{
		this->pollEvents();
	}

};

