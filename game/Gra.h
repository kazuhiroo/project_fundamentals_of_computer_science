#pragma once

#include "Gra.cpp"
#include <iostream>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>



using namespace sf;


class Character
{
private:
	//Zasoby
	Texture image;
	Sprite char_image;

	//Zmienne

	unsigned int hp;

	Vector2f position;
	Event r;



	//Funkcje

	void load_texture()
	{
		this->image.loadFromFile("Bg/car.png");
	}
	void upload_texture()
	{
		this->char_image.setTexture(this->image);
		this->char_image.scale(0.2f, 0.2f);
	}

public:
	Character(unsigned int health = 100)
	{
		hp = health;

		this->load_texture();
		this->upload_texture();


		this->position = Vector2f(350.0f, 300.0f);
		this->char_image.setPosition(position);
	}

	~Character()
	{}



	//Poruszanie siê gracza arrow keys
	void movement()
	{
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			position.x += 2.f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			position.x += -2.f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			position.y += 2.f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			position.y += -2.f;
		}

		this->char_image.setPosition(position);
	}

	//Renderowanie postaci gracza w grze
	void render(RenderTarget& obiekt)
	{
		this->movement();
		obiekt.draw(this->char_image);
	}


};






class Game
{
private:
	
	//Stworzenie wskaŸnika zawieraj¹cego okno - dynamiczne zarz¹dzanie gr¹
	RenderWindow* window;
	Event event;
	
	//Gracz
	Character* gracz;

	//Zasoby gry
	Font font;
	Texture bg;
	Sprite background;

	//ZMIENNE
	bool exit = false;
	
	
	//PRYWATNE FUNKCJE GRY

	





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
		this->window = new RenderWindow(VideoMode(800, 600), "Game1");
		this->window->setFramerateLimit(144);


		this->game_font();
		this->game_bg();
		this->create_background();


		//Spawn gracza
		this->gracz = new Character;


	
	}

	~Game()
	{
		//Destruktor okno spod wskaŸnika
		delete this->window;
		delete this->gracz;
	}


	//Informacja zwrotna o dzia³aniu okna
	const bool get_working()
	{
		return this->window->isOpen();
	}
	const bool get_exit()
	{
		return this->exit;
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

		this->gracz->render(*this->window);



		this->window->display();

		
	
	}

};





