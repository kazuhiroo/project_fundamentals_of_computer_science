#pragma once


#include "Gra.cpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <cmath>
//#include <Windows.h>

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

	Vector2f position;
	Vector2f pivot;

	
	float rotation = 0;
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
	Character()
	{
		
		this->load_texture();
		this->upload_texture();

		//Pozycja startowa postaci
		this->position = Vector2f(250.0f, 300.0f);
		this->char_image.setPosition(position);

		//Rotacja startowa postaci
		this->rotation = 0.f;
		this->char_image.setRotation(rotation);

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.0f, char_image.getLocalBounds().height / 2.0f);
		this->char_image.setOrigin(pivot);
	}

	~Character()
	{}
	


	//Poruszanie siÍ gracza arrow keys
	//Q obrÛt w prawo
	//E obrÛt w lewo
	void movement()
	{

		//ARROW KEYS MOVEMENT

		
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				position.x += 1.f;


			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				position.x += -1.f;

			}


		

		// TURNING
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				rotation += 0.75f;
			}
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				rotation -= 0.75f;
			}


			
			if (rotation >= -95 && rotation <=95)
			{
					position.y += 2*std::sin(rotation * 3.14159 / 180);
			}
			else
			{
					position.x += -2.f + std::cos(rotation*3.14159 / 180);
					position.y += std::sin(rotation * 3.14159 / 180);
			}
		
		
			this->char_image.setRotation(rotation);
			this->char_image.setPosition(position);
		
	}


	bool player_on_road()
	{
		if (position.y > 450.f || position.y < 150.f || position.x <= 0.f)
		{
			return false;
		}
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

	//Stworzenie wskaünika zawierajπcego okno
	RenderWindow* window;
	Event event;

	//Gracz
	Character* gracz;

	//Obstacles
	RectangleShape obstacle;
	std::vector<RectangleShape> obstacles;

	RectangleShape enemy;
	std::vector<RectangleShape> enemies;


	//Resources
	Font font;
	Texture bg;
	Texture rd;
	Sprite background_image;
	//Sprite road_image;
	Sprite road_image;
	Vector2f road_position;
	RectangleShape road;

	unsigned int points = 0;

	bool exit = false;


	//PRYWATNE FUNKCJE GRY
	
	void create_obstacle()
	{
		this->obstacle.setPosition(Vector2f(800.f, static_cast<float>(rand() % 151 - 150)));

		this->obstacle.setFillColor(Color::White);
		this->obstacle.setOutlineColor(Color::Red);
		this->obstacle.setOutlineThickness(15.f);
		this->obstacle.setSize(Vector2f(30.f, 30.f));


		this->obstacles.push_back(this->obstacle);
	}
	
	void spawn_obstacle()
	{
		//Sleep(4000);
		this->create_obstacle();
	}
	
	void render_obstacles()
	{
		for (auto& e : this->obstacles)
		{
			this->window->draw(e);
		}
	}

	/**/
		//OKNO I METODY ZASOB”W

		//Zdarzenie: okno
		void pollEvents()
		{
			while (this->window->pollEvent(this->event))
			{

				if (this->event.type == Event::Closed)
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
			if (this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf") == false)
			{
				std::cout << "GAME::RESOURCES::Font uploading unsuccessful" << std::endl;
			}
		}


		//Wczytanie grafiki i t≥a

		void game_rd()
		{
			this->rd.loadFromFile("Bg/road.png");
			if (!this->rd.loadFromFile("Bg/road.png"))
			{
				std::cout << "GAME::RESOURCES::Road upload failed \n";
			}
			if (this->rd.loadFromFile("Bg/road.png"))
			{
				std::cout << "GAME::RESOURCES::Road image uploaded succesfully \n";
			}
		}
		void create_road()
		{
			this->road_image.setTexture(this->rd);
			this->road_image.setPosition(Vector2f(0.f, 150.f));
		}
		void game_bg()
		{
			if (this->bg.loadFromFile("Bg/bg.png"))
			{
				std::cout << "GAME::RESOURCES::Background uploaded successfully" << std::endl;
			}
			if (this->bg.loadFromFile("Bg/bg.png") == false)
			{
				std::cout << "GAME::RESOURCES::Background uploading unsuccessful" << std::endl;
			}
		}
		void create_background()
		{
			this->background_image.setTexture(this->bg);
		}


	public:
		//Konstruktor/Destruktor
		Game()
		{
			//Konstruktor tworzy okno przy utworzeniu obiektu
			this->window = new RenderWindow(VideoMode(800, 600), "Game1");
			this->window->setFramerateLimit(144);
			this->window->setVerticalSyncEnabled(false);

			

			//Upload textures
			this->game_font();
			this->game_bg();
			this->create_background();
			this->game_rd();
			this->create_road();

			//Spawn gracza
			this->gracz = new Character;

		}

		~Game()
		{
			//Destruktor okno spod wskaünika
			delete this->window;
			delete this->gracz;
		}


		//Informacja zwrotna o dzia≥aniu okna
		 bool get_working()
		{
			return this->window->isOpen();
		}
		 bool get_exit()
		{
			return this->exit;
		}

		//Nowe informacje + render w grze
		void update()
		{
			this->pollEvents();

			//Objects spawn

			if (this->exit == false)
			{
				//this->obstacle_spawn();
				//this->coin_spawn();
				this->gracz->player_on_road();
				
				
			}

			//Returning the information if the game is still on

			if (!this->gracz->player_on_road())
			{
				this->exit = true;
				std::cout << "GAME OVER!" << std::endl << "POINTS: " << this->points;
			}
		

		}
		
		void render()
		{
			this->window->clear();
			
			this->window->draw(this->background_image);
			
			this->window->draw(this->road_image);

			this->gracz->render(*this->window);

			//this->render_obstacles();

			this->window->display();

		}

	};
