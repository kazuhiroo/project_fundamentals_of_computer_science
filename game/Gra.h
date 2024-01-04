#pragma once

#include "Gra.cpp"
#include "iostream"

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
	
	//Stworzenie wskaŸnika zawieraj¹cego okno - dynamiczne zarz¹dzanie gr¹
	RenderWindow* window;
	Event event;
	//Zasoby gry
	Font font;


	
	//PRYWATNE FUNKCJE GRY
	
	//Utworzenie na wskaŸniku okna gry
	void create_window()
	{
		this->window = new RenderWindow(VideoMode(800, 900), "arcade");
		this->window->setFramerateLimit(144);
	}
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
		//Destruktor okno spod wskaŸnika
		delete this->window;
	}


	//Informacja zwrotna o dzia³aniu okna
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

