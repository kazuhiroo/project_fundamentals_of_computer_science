#pragma once

#include "Gra.cpp"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//Klasa tworz�ca gr�

class Game
{
private:
	
	//Stworzenie wska�nika zawieraj�cego okno
	RenderWindow* window;
	Event event;


	//Zdarzenie: zamkni�cie okna X
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
		//Utworzenie na wska�niku okna gry
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
		//Destruktor okno spod wska�nika
		delete this->window;
	}


	//Informacja zwrotna o dzia�aniu okna
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

