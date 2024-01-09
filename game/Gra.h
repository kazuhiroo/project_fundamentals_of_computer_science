#pragma once


#include "Gra.cpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <cmath>


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
	Vector2f hitbox1;


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

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);

		this->hitbox1 = Vector2f(-char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height/2.f);
		

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
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			rotation += 0.75f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			rotation -= 0.75f;
		}



		if (rotation >= -95 && rotation <= 95)
		{
			position.y += 2 * std::sin(rotation * 3.14159 / 180);
			hitbox1.y += 2 * std::sin(rotation * 3.14159 / 180);
		}
		else
		{
			position.x += -2.f + std::cos(rotation * 3.14159 / 180);
			position.y += std::sin(rotation * 3.14159 / 180);
			hitbox1.y += 2 * std::sin(rotation * 3.14159 / 180);
			hitbox1.x += -2.f + std::cos(rotation * 3.14159 / 180);
		}


		this->char_image.setRotation(rotation);
		this->char_image.setPosition(position);
		this->get_hitbox();
	}

	
	bool player_on_road()
	{
		if (hitbox1.y > 240.5f ||  hitbox1.y < -45.5f || position.x <= 0.f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Vector2f get_hitbox()
	{
		return hitbox1;
	}

	Vector2f get_position()
	{
		return position;
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

	//Points
	CircleShape coin;
	std::vector<CircleShape> coins;

	float space = 100.f;

	//Obstacles
	RectangleShape obstacle;
	std::vector<RectangleShape> obstacles;
	
	
	int num_of_objects = 0;
	int option;

	Time time = Time::Zero;
	Time spawn_time = seconds(1);
	Clock clock;
	//Resources
	Font font;
	Texture bg;
	Texture rd;
	Sprite background_image;
	//Sprite road_image;
	Sprite road_image;
	Vector2f road_position;
	RectangleShape road;


	unsigned int pts = 0;
	
	//end game bool

	bool exit = false;


	//PRIVATE FUNCTIONS

	void gain_points()
	{
		//std::cout << "gain coin method" << std::endl;
		bool deleted = false;

		for (int i = 0; i < coins.size() && deleted == false; i++)
		{	
			if (this->coins[i].getGlobalBounds().contains(this->gracz->get_position()))
			{
				this->pts += 10;
				std::cout << "Points +10" << std::endl;
				this->coins.erase(this->coins.begin() + i);
				deleted = true;
			}
			
		}
	}
	
	void collision()
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (this->obstacles[i].getGlobalBounds().contains(this->gracz->get_position()))
			{
				this->exit = true;
			}
		}
	}





	//Coins+obstacles functions

	void set_objects()
	{
		option = rand() % 2;
		this->set_coins();
		this->set_obstacles();
	}

	void creating_objects()
	{
		if (time >= spawn_time)
		{
			this->set_objects();
			time = Time::Zero;
			this->obstacles.push_back(this->obstacle);
			this->coins.push_back(this->coin);
			num_of_objects++;
		}
	}

	//Coins functions

	void set_coins()
	{
		switch (option)
		{
		case 0:
			this->coin.setPosition(800.f+space, static_cast<float>(rand() % 146 + 155));
			break;
		case 1:
			this->coin.setPosition(800.f+space, static_cast<float>(rand() % 126 + 295));
			break;
		default:
			break;
		}


		this->coin.setRadius(10.f);
		this->coin.setFillColor(Color::Yellow);
		this->coin.setOutlineColor(Color::White);
		this->coin.setOutlineThickness(5.f);
	}

	void move_coins()
	{
		for (int i = 0; i < coins.size(); i++)
		{
			this->coins[i].setPosition(Vector2f(this->coins[i].getPosition().x - 2.f, this->coins[i].getPosition().y));
			if (this->coins[i].getPosition().x <= 0.f)
			{
				this->coins.erase(this->coins.begin() + i);
			}
		}
	}

	void render_coins()
	{
		for (auto& coins_objects : this->coins)
		{
			this->window->draw(coins_objects);
		}
	}

	//Obstacles functions

	void set_obstacles()
	{

		switch (option)
		{
		case 0:
			this->obstacle.setPosition(800.f, static_cast<float>(rand() % 141 + 160));
			break;
		case 1: 
			this->obstacle.setPosition(800.f, static_cast<float>(rand() % 96 + 245));
			break; 
		default: 
			break;
		}

		this->obstacle.setSize(Vector2f(25.f, 25.f));
		this->obstacle.setFillColor(Color::White);
		this->obstacle.setOutlineColor(Color::Red);
		this->obstacle.setOutlineThickness(10.f);
		
	}

	void move_obstacles()
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			this->obstacles[i].setPosition(Vector2f(this->obstacles[i].getPosition().x - 2.f, this->obstacles[i].getPosition().y));

			if (this->obstacles[i].getPosition().x <= 0.f)
			{
				this->obstacles.erase(this->obstacles.begin() + i);
			}
		}
	}

	void render_obstacles()
	{
		for (auto& obstacles_objects : this->obstacles)
		{
			this->window->draw(obstacles_objects);
		}
	}


	
	
		//Window functions

		//window closing event
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


		//font upload
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


		//background and road upload

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
		//Constructor/Destructor
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
			time += clock.restart();

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
			 time += clock.restart();

			 this->pollEvents();

			 //Objects spawn

			 if (this->exit == false)
			 {
				 this->creating_objects();
				 this->gracz->player_on_road();
				 this->move_obstacles();
				 this->move_coins();
				 this->gain_points();
				 this->collision();

			 }

			 //Returning the information if the game is still on

			 if (!this->gracz->player_on_road())
			 {
				 this->exit = true;
				 std::cout << std::endl << "GAME OVER!" << std::endl << "POINTS: " << this->pts;
			 }


		 }
		
		void render()
		{
			this->window->clear();
			
			this->window->draw(this->background_image);
			
			this->window->draw(this->road_image);

			this->gracz->render(*this->window);

			this->render_obstacles();

			this->render_coins();

			this->window->display();

		}

	};







