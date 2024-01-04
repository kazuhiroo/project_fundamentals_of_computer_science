#pragma once

#include "Gra.cpp"
#include "iostream"

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
	
	//Stworzenie wska�nika zawieraj�cego okno - dynamiczne zarz�dzanie gr�
	RenderWindow* window;
	Event event;
	//Zasoby gry
	Font font;


	
	//PRYWATNE FUNKCJE GRY
	
	//Utworzenie na wska�niku okna gry
	void create_window()
	{
		this->window = new RenderWindow(VideoMode(800, 900), "arcade");
		this->window->setFramerateLimit(144);
	}
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
	//Wczytanie fontu
	void game_font()
	{
		if (this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf"))
		{
			std::cout << "GAME::GAME_FONT::Font uploaded successfully";
		}
	}
	
public:
	//Konstruktor/Destruktor
	Game()
	{
		//Konstruktor tworzy okno przy utworzeniu obiektu
		this->create_window();
		this->game_font();
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


	//Nowe informacje + render w grze
	void update()
	{
		this->pollEvents();
	}

	void render()
	{
		this->window->clear();

		this->window->display();
	}

};

