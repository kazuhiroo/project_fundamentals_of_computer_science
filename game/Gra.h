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


class Menu
{
protected:

	//Window Pointer

	RenderWindow* window;
	String window_name;
	Event event;


	Vector2f title_position;
	Vector2i mouse_position;

	//Resources

	Text title;

	Texture pl; 
	Texture exx; 
	Texture st;

	Sprite play_image; 
	Sprite exit_image; 
	Sprite stats_image;

	Font font;


	//Bools


	

	//Functions

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
	void upload_text()
	{
		this->title.setFont(this->font);
		this->title.setString("PIXEL RACE");
		this->title.setCharacterSize(80.f);
	}

	//textures n sprites

	void load_textures()
	{
		this->pl.loadFromFile("Bg/play.png");
		this->exx.loadFromFile("Bg/exit.png");
		this->st.loadFromFile("Bg/stats.png");
	}
	void upload_images()
	{
		this->play_image.setTexture(this->pl);
		this->exit_image.setTexture(this->exx);
		this->stats_image.setTexture(this->st);

		this->play_image.scale(0.2f, 0.2f);
		this->exit_image.scale(0.2f, 0.2f);
		this->stats_image.scale(0.2f, 0.2f);

	}

public:
	Menu(String w_name = "Menu")
	{
		//Creating a new window object on pointer

		window_name = w_name;
		this->window = new RenderWindow(VideoMode(800, 600), window_name);
		this->window->setFramerateLimit(144);
		this->window->setVerticalSyncEnabled(false);

		//Upload resources

		this->load_textures();
		this->upload_images();
		this->game_font();
		this->upload_text();


		this->title_position = Vector2f(320.f, 150.f);

		this->title.setPosition(title_position.x-220.f, title_position.y-50.f);
		this->play_image.setPosition(title_position.x, title_position.y+100.f);
		this->exit_image.setPosition(Vector2f(title_position.x, title_position.y + 300.f));
		this->stats_image.setPosition(Vector2f(title_position.x, title_position.y+200.f));

		//std::cout << this->play_image.getPosition().x << " "<< this->play_image.getPosition().y;

	}
	~Menu()
	{
		
	}
	//


	bool esc = false;
	bool play = false;
	bool stats = false;


	//Functions


	bool get_working_m()
	{
		return this->window->isOpen();
	}

	bool get_esc()
	{
		return esc;
	}

	bool Play()
	{
		return play;
	}

	bool Statistics()
	{
		return stats;
	}

	Vector2i get_mouse_position()
	{	
		this->mouse_position = Mouse::getPosition(*this->window);
		//std::cout << mouse_position.x << " "<< mouse_position.y << std::endl;
		return this->mouse_position;
	}


	void choose_option()
	{
		
		if (this->play_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->play = true;
			}
		}
		if (this->stats_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->stats = true;
			}
		}
		if (this->exit_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->esc = true;
			}
		}
	}




	void update_menu()
	{
		if (!this->get_esc())
		{
			this->pollEvents();
			this->get_working_m();
			this->get_mouse_position();
			this->choose_option();
			this->Play();
			this->Statistics();
		}
	}

	void render_menu()
	{
		this->window->clear();

		this->window->draw(this->title);

		this->window->draw(this->play_image);
		this->window->draw(this->stats_image);
		this->window->draw(this->exit_image);

		this->window->display();
	}
};



class Stats 
{
private:
	
	RenderWindow* window;
	Event event;
	
	Text title_s;
	Text stats_text;
	Texture gob;
	Sprite go_back_image;


	Vector2i mouse_position;

	Font font;

	bool esc_s = false;


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

	void upload_text()
	{
		this->title_s.setFont(this->font);
		this->title_s.setString("STATS");
		this->title_s.setCharacterSize(80.f);


		this->stats_text.setFont(this->font);
		this->stats_text.setString("STATS");
		this->stats_text.setCharacterSize(50.f);

	}

	//textures n sprites

	void load_textures()
	{
		this->gob.loadFromFile("Bg/back.png");
	}
	void upload_images()
	{
		this->go_back_image.setTexture(this->gob);
		
		this->go_back_image.scale(0.2f, 0.2f);

	}

	

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

public:
	Stats(String w_name = "Stats") 
	{
		this->window = new RenderWindow(VideoMode(800, 600), w_name);
		this->window->setFramerateLimit(144);
		this->window->setVerticalSyncEnabled(false);

		this->game_font();
		this->upload_text();

		this->load_textures();
		this->upload_images();

		this->go_back_image.setPosition(Vector2f(10.f, 20.f));


	}
	~Stats()
	{
		delete this->window;
	}


	void go_back()
	{
		if (this->go_back_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->esc_s = true;
			}
		}
	}

	Vector2i get_mouse_position()
	{
		this->mouse_position = Mouse::getPosition(*this->window);
		//std::cout << mouse_position.x << " "<< mouse_position.y << std::endl;
		return this->mouse_position;
	}




	bool get_working_s()
	{
		return this->window->isOpen();
	}

	bool get_esc_s()
	{
		return esc_s;
	}



	void update_stats()
	{
		if (!this->get_esc_s())
		{
			this->pollEvents();
			this->get_working_s();
			this->get_mouse_position();
			this->go_back();
		}
	}

	void render_stats()
	{
		this->window->clear();

		this->window->draw(this->go_back_image);

		this->window->display();
	}

};








class Character
{
private:
	//Resources

	Texture image1;
	Sprite char_image;
	

	//Vectors

	Vector2f position;
	Vector2f pivot;
	Vector2f endpoint;


	float rotation = 0;

	//Functions

	void load_texture()
	{
		this->image1.loadFromFile("Bg/car.png");
	}

	void upload_texture()
	{
		this->char_image.setTexture(this->image1);
		this->char_image.scale(0.2f, 0.2f);
	}

public:
	Character()
	{
		//Uploading resources

		this->load_texture();
		this->upload_texture();

		//Starting position

		this->position = Vector2f(250.0f, 300.0f);
		this->char_image.setPosition(position);

		//Reset rotation

		this->rotation = 0.f;
		this->char_image.setRotation(rotation);

		//Setting pivot and hitbox

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);

	}

	~Character()
	{}



	//KEYBOARD <- ->
	// ^
	// v
	void movement()
	{

		//ARROW KEYS MOVEMENT
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			position.x += 0.5f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			position.x += -0.5f;
		}




		// TURNING
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			rotation += 0.75f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			rotation -= 0.75f;
		}



		if (rotation >= -95 && rotation <= 95)
		{
			position.y += 2 * std::sin(rotation * 3.14159 / 180);
		}
		else
		{
			position.x += -2.f + std::cos(rotation * 3.14159 / 180);
			position.y += std::sin(rotation * 3.14159 / 180);
		}


		this->char_image.setRotation(rotation);
		this->char_image.setPosition(position);
		

	}


	bool player_on_road()
	{
		if (position.y > 450.5f|| position.y < 150.5f || position.x <= 0.f)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Vector2f get_position()
	{
		return position;
	}

	FloatRect get_bounds()
	{
		return char_image.getGlobalBounds();
	}




	//Rendering the player

	void render(RenderTarget& obiekt)
	{
		this->movement();
		obiekt.draw(this->char_image);
	}
};







class Game 
{
private:

	//Window Pointer

	RenderWindow* window;
	Event event;

	//Player
	Character* gracz;

	//Coins
	Text chance;
	Text points;
	Font font;

	Texture cns;
	Sprite coin;
	std::vector<Sprite> coins;

	unsigned int pts = 0;
	unsigned int chances = 3;

	float space = 150.f;

	//Obstacles

	Texture obs;
	Sprite obstacle;
	std::vector<Sprite> obstacles;


	int num_of_objects = 0;
	int option;

	Time time = Time::Zero;
	Time spawn_time = seconds(1);
	Clock clock;

	//Background

	Texture bg;
	Texture rd;
	Sprite background_image;

	//Road

	Sprite road_image;
	Vector2f road_position;
	RectangleShape road;


	

	//end game bool

	bool exit = false;


	//PRIVATE FUNCTIONS




	//void score_to_file(){}

	//Actions

	void gain_points()
	{
		for (int i = 0; i < coins.size(); i++)
		{
			if (this->coins[i].getGlobalBounds().intersects(this->gracz->get_bounds()))
			{
				this->pts += 1;
				this->chances = 3;
				std::cout << "Points +1" << std::endl;
				this->coins.erase(this->coins.begin() + i);
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
				std::cout << std::endl << "GAME OVER!" << std::endl << "COLLISION!" <<	std::endl << "POINTS: " << this->pts;
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
			this->coin.setPosition(800.f + space, static_cast<float>(rand() % 146 + 155));
			break;
		case 1:
			this->coin.setPosition(800.f + space, static_cast<float>(rand() % 126 + 295));
			break;
		default:
			break;
		}


		this->coin.setTexture(this->cns);
	}

	void move_coins()
	{
		for (int i = 0; i < coins.size(); i++)
		{
			this->coins[i].setPosition(Vector2f(this->coins[i].getPosition().x - 2.f, this->coins[i].getPosition().y));
			if (this->coins[i].getPosition().x <= 0.f)
			{
				this->coins.erase(this->coins.begin() + i);
				this->chances -= 1;
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

		this->obstacle.setTexture(this->obs);
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


	//RESOURCES UPLOADING

	//text

	void game_font()
	{
		this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf");
	}

	void show_points()
	{
		std::stringstream points_string, miss_points_string;

		points_string << "Points: " << this->pts;
		this->points.setString(points_string.str());

		miss_points_string << "Chances: " << this->chances;
		this->chance.setString(miss_points_string.str());

	}

	//textures upload

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
	void upload_background()
	{
		this->background_image.setTexture(this->bg);
		this->background_image.setPosition(Vector2f(0.f, 0.f));
	}
	void upload_obstacles()
	{
		this->obs.loadFromFile("Bg/obstacle.png");
	}
	void upload_coins()
	{
		this->cns.loadFromFile("Bg/coin.png");
	}

public:
	//Constructor/Destructor
	Game(String w_name = "Game")
	{
		//Creating a new window object on window pointer

		this->window = new RenderWindow(VideoMode(800, 600), w_name);
		this->window->setFramerateLimit(144);
		this->window->setVerticalSyncEnabled(false);

		//Upload textures

		this->game_bg();
		this->upload_background();
		this->game_rd();
		this->create_road();
		this->game_font();
		this->upload_obstacles();
		this->upload_coins();

		//Spawn player

		this->gracz = new Character;

		time += clock.restart();

		//Set font

		this->points.setFont(this->font);
		this->points.setPosition(Vector2f(80.f, 40.f));

		this->chance.setFont(this->font);
		this->chance.setPosition(Vector2f(80.f, 80.f));


	}

	~Game()
	{
		delete this->window;
		delete this->gracz;
	}


	//Bool information for game loop

	bool get_exit()
	{
		return this->exit;
	}

	bool get_working()
	{
		return this->window->isOpen();
	}

	//New information and game render

	void update()
	{
		time += clock.restart();

		this->pollEvents();
		this->show_points();

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

		if (this->chances <= 0)
		{
			this->exit = true;
			std::cout << std::endl << "GAME OVER!" << std::endl << "YOU MISSED TOO MANY COINS!"  << std::endl << "POINTS: " << this->pts;
		}

		if (!this->gracz->player_on_road())
		{
			this->exit = true;
			std::cout << std::endl << "GAME OVER!" << std::endl <<"YOU WENT OFF THE ROAD!" << std::endl<< "POINTS: " << this->pts;
		}


	}

	void render()
	{
		this->window->clear();

		this->window->draw(this->background_image);

		this->window->draw(this->road_image);

		this->window->draw(this->points);

		this->window->draw(this->chance);

		this->gracz->render(*this->window);

		this->render_obstacles();

		this->render_coins();

		this->window->display();
	}

};