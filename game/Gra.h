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
	Texture bg;
	Sprite background;



	//ZMIENNE
	bool exit = false;
	







	
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
			std::cout << "GAME::RESOURCES::Font uploaded successfully" << std::endl;
		}
		if (this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf" ) == false)
		{
			std::cout << "GAME::RESOURCES::Font uploading unsuccessful" << std::endl;
		}
	}



	//Wczytanie grafiki i t³a
	void game_bg()
	{
		if (this->bg.loadFromFile("Bg/bg.png"))
		{
			std::cout << "GAME::RESOURCES::Backgroud uploaded successfully" << std::endl;
		}
		if (this->bg.loadFromFile("Bg/bg.png") == false)
		{
			std::cout << "GAME::RESOURCES::Backgroud uploading unsuccessful"<< std::endl;
		}
	}
	void create_background()
	{
		
		this->background.setTexture(this->bg);
	}
public:
	//Konstruktor/Destruktor
	Game()
	{
		//Konstruktor tworzy okno przy utworzeniu obiektu
		this->create_window();
		this->game_font();
		this->game_bg();
		this->create_background();
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
		this->window->draw(this->background);
		this->window->display();
	}

};




