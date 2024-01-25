#pragma once

#include "Gra.cpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


using namespace sf;

/*
	User Interface windows classes such as main menu 
	and stats window with the saved highscore (futurably)
*/

//MENU CLASS

class Menu
{
private:

	//Window Pointer

	RenderWindow* window;
	String window_name;
	Event event;


	Vector2f r_position;
	Vector2i mouse_position;

	//Resources

	Text title;
	Text text_car;

	//buttons textures & sprites

	Texture bg;
	Sprite background_image;

	Texture pl; //play
	Texture exx; //exit
	Texture st; //stats

	Sprite play_image; 
	Sprite exit_image; 
	Sprite stats_image;

	//cars textures & sprites

	Texture f1, fer, mi;
	Texture f12, mi2, fer2;
	
	Sprite f1_image;
	Sprite miami_image;
	Sprite ferrari_image;
	
	Font font;

	int car_type;

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
	
	//text function

	void upload_text()
	{
		this->text_car.setFont(this->font);
		this->text_car.setString("CHOOSE YOUR CAR:");
		this->text_car.setCharacterSize(25.f);

		this->title.setFont(this->font);
		this->title.setString("PIXEL RACE");
		this->title.setCharacterSize(80.f);
	}

	//TEXTURES AND SPRITES

	//load functions

	void load_buttons_textures()
	{
		this->pl.loadFromFile("Bg/play.png");
		this->exx.loadFromFile("Bg/exit.png");
		this->st.loadFromFile("Bg/stats.png");
		this->bg.loadFromFile("Bg/bg.png");
	}

	void upload_buttons_images()
	{
		this->play_image.setTexture(this->pl);
		this->exit_image.setTexture(this->exx);
		this->stats_image.setTexture(this->st);
		this->background_image.setTexture(this->bg);


	}

	void load_cars_textures()
	{
		this->fer.loadFromFile("Bg/ch_ferrari.png");
		this->fer2.loadFromFile("Bg/chsn_ferrari.png");
		this->f1.loadFromFile("Bg/ch_f1.png");
		this->f12.loadFromFile("Bg/chsn_f1.png");
		this->mi.loadFromFile("Bg/ch_miami.png");
		this->mi2.loadFromFile("Bg/chsn_miami.png");
	}

	void upload_cars_images()
	{ 
		switch (this->car_type)
		{
			case 1:
			{
				this->ferrari_image.setTexture(this->fer2);
				this->f1_image.setTexture(this->f1);
				this->miami_image.setTexture(this->mi);
				
				break;
			}
			case 2:
			{
				this->ferrari_image.setTexture(this->fer);
				this->f1_image.setTexture(this->f12);
				this->miami_image.setTexture(this->mi);
				
				break;
			}
			case 3:
			{
				this->ferrari_image.setTexture(this->fer);
				this->f1_image.setTexture(this->f1);
				this->miami_image.setTexture(this->mi2);
			
				break;
			}
		}
	}

	//Render parts

	void render_static()
	{
		this->window->draw(this->background_image);
		this->window->draw(this->title);
		this->window->draw(this->text_car);
		this->window->draw(this->play_image);
		this->window->draw(this->stats_image);
		this->window->draw(this->exit_image);
	}

	void render_dynamic()
	{
		this->window->draw(this->ferrari_image);
		this->window->draw(this->f1_image);
		this->window->draw(this->miami_image);
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
		
		//textures
		this->load_buttons_textures();
		this->load_cars_textures();
		this->upload_buttons_images();
		this->upload_cars_images();
		
		//text
		this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf");
		this->upload_text();

		//menu's objects position
		this->r_position = Vector2f(100.f, 150.f);
		
		this->title.setPosition(r_position.x, r_position.y-50.f);

		this->text_car.setPosition(r_position.x + 300.f, r_position.y + 50.f);

		this->play_image.setPosition(r_position.x, r_position.y + 100.f);
		this->exit_image.setPosition(r_position.x, r_position.y + 300.f);
		this->stats_image.setPosition(r_position.x, r_position.y + 200.f);

		this->play_image.scale(0.2f, 0.2f);
		this->exit_image.scale(0.2f, 0.2f);
		this->stats_image.scale(0.2f, 0.2f);

		//cars images
		this->ferrari_image.setPosition(r_position.x + 360.f, r_position.y + 100.f);
		this->f1_image.setPosition(r_position.x + 360.f, r_position.y + 200.f);
		this->miami_image.setPosition(r_position.x + 360.f, r_position.y + 300.f);


		this->ferrari_image.scale(0.25f, 0.25f);
		this->f1_image.scale(0.25f, 0.25f);
		this->miami_image.scale(0.25f, 0.25f);

		//Default car choose

		car_type = 1;
	}
	~Menu()
	{
		
	}


	int get_car_type()
	{
		return this->car_type;
	}


	//menu bools

	bool esc = false;
	bool play = false;
	bool stats = false;

	//Functions

	//bool - buttons functions

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

	//play-stats-exit interaction

	void choose_menu_option()
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

	//choosing a car

	void choose_car_option()
	{
		if (this->ferrari_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				car_type = 1;
				
			}
		}
		if (this->f1_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				car_type = 2;
				
			}
		}
		if (this->miami_image.getGlobalBounds().contains(Vector2f(mouse_position)))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				car_type = 3;
				
			}
		}
	}

	//Menu loop

	void update_menu()
	{
		this->pollEvents();
		this->upload_cars_images();
		this->get_working_m();
		this->get_mouse_position();
		this->choose_car_option();
		this->choose_menu_option();
		this->Play();
		this->Statistics();
	}

	void render_menu()
	{
		this->window->clear();

		this->render_static();
		this->render_dynamic();
	

		this->window->display();
	}
};


//STATS CLASS

class Stats 
{
private:

	//Window

	RenderWindow* window;
	Event event;
	
	//getting data from txt

	std::ifstream s1_txt, s2_txt, s3_txt;

	std::string score1, score2, score3;
	std::string nick1, nick2, nick3;

	//Text, background and buttons
	Texture bg,gob,fr,f1,mi;

	Text title_s;
	Text stats_text_fer, stats_text_f1, stats_text_m;
	Text nick_text_fer, nick_text_f1, nick_text_m;

	Sprite ferrari_image, f1_image, miami_image, background_image, go_back_image;

	Font font;
	//Interaction with mouse

	Vector2i mouse_position;

	//Bool exit

	bool esc_s = false;


	//FUNCTIONS
	
	//TEXT

	//title

	void show_title()
	{
		this->title_s.setFont(this->font);
		this->title_s.setString("STATS");
		this->title_s.setCharacterSize(50.f);

		this->title_s.setPosition(Vector2f(300.f, 50.f));
	}

	//getting stats

	void get_stats_from_file()
	{
		std::string line;
		int line_nr = 1;

		s1_txt.open("stats_ferrari.txt", std::ios::in);
		s2_txt.open("stats_f1.txt", std::ios::in);
		s3_txt.open("stats_miami.txt", std::ios::in);

		while (getline(s1_txt, line))
		{
			switch (line_nr)
			{
			case 1:
				this->score1 = line;
				break;
			case 2:
				this->nick1 = line;
				break;
			}

			line_nr++;
		}
		s1_txt.close();
		line_nr = 1;

		while (getline(s2_txt, line))
		{
			switch (line_nr)
			{
			case 1:
				this->score2 = line;
				break;
			case 2:
				this->nick2 = line;
				break;
			}

			line_nr++;
		}
		s2_txt.close();
		line_nr = 1;


		while (getline(s3_txt, line))
		{
			switch (line_nr)
			{
			case 1:
				this->score3 = line;
				break;
			case 2:
				this->nick3 = line;
				break;
			}

			line_nr++;
		}
		s3_txt.close();
	}

	void show_nicks()
	{
		std::string n1 = "NICK: " + this->nick1;
		std::string n2 = "NICK: " + this->nick2;
		std::string n3 = "NICK: " + this->nick3;

		this->nick_text_fer.setString(n1);
		this->nick_text_fer.setPosition(Vector2f(50.f, 450.f));

		this->nick_text_f1.setString(n2);
		this->nick_text_f1.setPosition(Vector2f(300.f, 450.f));

		this->nick_text_m.setString(n3);
		this->nick_text_m.setPosition(Vector2f(550.f, 450.f));
	}


	void show_stats()
	{
		std::string s1 = "HIGHSCORE: " + this->score1;
		std::string s2 = "HIGHSCORE: " + this->score2;
		std::string s3 = "HIGHSCORE: " + this->score3;

		this->stats_text_fer.setString(s1);
		this->stats_text_fer.setPosition(Vector2f(50.f, 400.f));

		this->stats_text_f1.setString(s2);
		this->stats_text_f1.setPosition(Vector2f(300.f, 400.f));

		this->stats_text_m.setString(s3);
		this->stats_text_m.setPosition(Vector2f(550.f, 400.f));
	}

	void set_font_size()
	{
		this->stats_text_fer.setFont(this->font);
		this->stats_text_f1.setFont(this->font);
		this->stats_text_m.setFont(this->font);
		
		this->nick_text_fer.setFont(this->font);
		this->nick_text_f1.setFont(this->font);
		this->nick_text_m.setFont(this->font);

		this->stats_text_fer.setCharacterSize(20.f);
		this->stats_text_f1.setCharacterSize(20.f);
		this->stats_text_m.setCharacterSize(20.f);

		this->nick_text_fer.setCharacterSize(20.f);
		this->nick_text_f1.setCharacterSize(20.f);
		this->nick_text_m.setCharacterSize(20.f);
	}

	void render_stat_text()
	{
		this->window->draw(this->stats_text_fer);
		this->window->draw(this->stats_text_f1);
		this->window->draw(this->stats_text_m);
	}

	void render_nick_text()
	{
		this->window->draw(this->nick_text_fer);
		this->window->draw(this->nick_text_f1);
		this->window->draw(this->nick_text_m);
	}

	//textures n sprites

	void load_textures()
	{
		this->gob.loadFromFile("Bg/back.png");
		this->bg.loadFromFile("Bg/bg.png");
		this->fr.loadFromFile("Bg/ferrari.png");
		this->f1.loadFromFile("Bg/F1.png");
		this->mi.loadFromFile("Bg/miami.png");
	}

	void create_images()
	{
		this->go_back_image.setTexture(this->gob);
		this->background_image.setTexture(this->bg);
		this->ferrari_image.setTexture(this->fr);
		this->f1_image.setTexture(this->f1);
		this->miami_image.setTexture(this->mi);
		
		this->ferrari_image.setRotation(-90.f);
		this->f1_image.setRotation(-90.f);
		this->miami_image.setRotation(-90.f);

		this->go_back_image.scale(0.2f, 0.2f);
		this->ferrari_image.scale(0.5f, 0.5f);
		this->f1_image.scale(0.5f, 0.5f);
		this->miami_image.scale(0.5f, 0.5f);
	}

	void render_images()
	{
		this->window->draw(this->background_image);
		this->window->draw(this->title_s);
		this->window->draw(this->go_back_image);
		this->window->draw(this->ferrari_image);
		this->window->draw(this->f1_image);
		this->window->draw(this->miami_image);
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

		//text

		this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf");
		this->show_title();
		
		this->get_stats_from_file();
		
		this->set_font_size();
		this->show_stats();
		this->show_nicks();

		//textures

		this->load_textures();
		this->create_images();

		this->go_back_image.setPosition(Vector2f(10.f, 20.f));
		this->ferrari_image.setPosition(Vector2f(100.f, 350.f));
		this->f1_image.setPosition(Vector2f(350.f, 350.f));
		this->miami_image.setPosition(Vector2f(580.f, 350.f));

	}
	~Stats()
	{
		delete this->window;
	}

	//go back button

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

	//Mouse position

	Vector2i get_mouse_position()
	{
		this->mouse_position = Mouse::getPosition(*this->window);
		return this->mouse_position;
	}

	

	//Bool function

	bool get_working_s()
	{
		return this->window->isOpen();
	}

	bool get_esc_s()
	{
		return esc_s;
	}

	//Window loop

	void update_stats()
	{
		this->pollEvents();
		this->get_working_s();
		this->get_mouse_position();
		this->go_back();
	}

	void render_stats()
	{
		this->window->clear();
		
		this->render_images();
		this->render_stat_text();
		this->render_nick_text();
		this->window->display();
	}

};


/*
	Main Car class with a
	Polymorphy classes of the Car class
	- Ferrari - easy
	- F1 - medium
	- Hotline Miami - easter egg - elite
*/


//MAIN CAR CLASS
class Car
{
protected:

	//Resources

	Texture image1;
	Sprite char_image;
	
	//Vectors

	Vector2f position;
	Vector2f pivot;
	Vector2f endpoint;

	float cns_speed = 0.f;
	float speed = 0.f;
	float obj_speed = 0.f;
	float rotation_speed = 0.f;
	float turn_speed = 0.f;
	float space = 0.f;

	float rotation = 0;

public:
	Car()
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

		//Setting pivot for the sprite

		this->pivot = Vector2f(char_image.getLocalBounds().width / 2.5f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);

	}

	~Car()
	{}


	/*	
				   ^
		KEYBOARD <   >
				   v
	*/
				  	
	void movement()
	{

		//ARROW KEYS MOVEMENT (optional)
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			position.x += 0.3f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			position.x += -0.3f;
		}




		// TURNING
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			rotation += this->rotation_speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			rotation -= this->rotation_speed;
		}


		//UP AND DOWN MOVEMENT
		if (rotation >= -95 && rotation <= 95)
		{
			position.y += this->turn_speed * std::sin(rotation * 3.14159 / 180);
		}
		else
		{
			position.x += -1.5f + std::cos(rotation * 3.14159 / 180);
			position.y += std::sin(rotation * 3.14159 / 180);
		}


		this->char_image.setRotation(rotation);
		this->char_image.setPosition(position);
		

	}

	//player's data

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

	float get_speed()
	{
		return this->speed;
	}

	float get_obj_speed()
	{
		return this->obj_speed;
	}

	float get_cns_speed()
	{
		return this->cns_speed;
	}

	float get_space()
	{
		return this->space;
	}

	//Rendering the player

	void render(RenderTarget& obiekt)
	{
		this->movement();
		obiekt.draw(this->char_image);
	}

	//Loading resources

	virtual void load_texture() 
	{
		this->image1.loadFromFile("Bg/F1.png");
	};
	
	virtual void upload_texture()
	{
		this->char_image.setTexture(this->image1);
	}
};


//FORMULA ONE CLASS 
class F1 :public Car
{

public:
	F1(float t_speed = 2.f, float r_speed = 0.75f, float sp = 1.f, float o_speed = 2.f, float c_speed = 2.5f)
	{
		cns_speed = c_speed;
		speed = sp;
		obj_speed = o_speed;
		turn_speed = t_speed;
		rotation_speed = r_speed;

		this->load_texture();
		this->upload_texture();

		//Setting pivot and hitbox

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);
	};
	~F1() {};

	void load_texture()
	{
		this->image1.loadFromFile("Bg/F1.png");
	}

	void upload_texture()
	{
		this->char_image.setTexture(this->image1);
		this->char_image.scale(0.2f, 0.2f);
	}
};

//FERRARI CLASS 
class Ferrari :public Car
{

public:
	Ferrari(float t_speed = 2.f, float r_speed = 0.75f, float sp = 2.f, float o_speed = 2.f, float c_speed = 2.2f, float spc = 150.f)
	{
		cns_speed = c_speed;
		speed = sp;
		obj_speed = o_speed;
		turn_speed = t_speed;
		rotation_speed = r_speed;
		space = spc;

		this->load_texture();
		this->upload_texture();

		//Setting pivot and hitbox

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);
	};
	~Ferrari() {};

	void load_texture()
	{
		this->image1.loadFromFile("Bg/ferrari.png");
	}

	void upload_texture()
	{
		this->char_image.setTexture(this->image1);
		this->char_image.scale(0.2f, 0.2f);
	}
};

//HOTLINE MIAMI CLASS
class Miami :public Car
{
public:
	Miami(float t_speed = 2.5f, float r_speed = 0.55f, float sp = 1.f, float o_speed = 3.5f, float c_speed = 3.7f, float spc = 200.f)
	{
		cns_speed = c_speed;
		speed = sp;
		obj_speed = o_speed;
		turn_speed = t_speed;
		rotation_speed = r_speed;
		space = spc;

		this->load_texture();
		this->upload_texture();

		//Setting pivot and hitbox

		this->pivot = Vector2f(char_image.getLocalBounds().width / 3.f, char_image.getLocalBounds().height / 2.f);
		this->char_image.setOrigin(pivot);
	};
	~Miami() {};

	void load_texture()
	{
		this->image1.loadFromFile("Bg/miami.png");
	}

	void upload_texture()
	{
		this->char_image.setTexture(this->image1);
		this->char_image.scale(0.25f, 0.25f);
	}
};



/*
	Game class
	- rendering game window and other objects
	- sets the flow of the game 
	- creating a new object opens a new game run
*/


class Game
{
private:

	//Window Pointer
	
	RenderWindow* window;
	Event event;

	//Player

	Car* gracz;

	//Points

	int pts = 0;

	//Coins

	Text end_points;
	Text game_over;
	Text chance;
	Text points;

	Font font;

	Texture cns;
	Sprite coin;
	std::vector<Sprite> coins;

	unsigned int chances = 3;

	//Obstacles

	Texture obs;
	Sprite obstacle;
	std::vector<Sprite> obstacles;

	float game_obj_speed;
	float game_cns_speed;

	int num_of_objects = 0;
	int option;
	int c_chosen = 1;
	
	Time time = Time::Zero;
	Time spawn_time;
	Clock clock;

	Clock game_clock;
	Time game_time = Time::Zero;
	Time progress_time = seconds(6.f);

	//Background

	Texture bg;
	Texture rd;
	Sprite background_image;

	//Road

	Sprite road_image;
	Vector2f road_position;
	RectangleShape road;

	//end game bool

	bool esc_g = false;

	//PRIVATE FUNCTIONS

	//Actions

	void gain_points()
	{
		for (int i = 0; i < coins.size(); i++)
		{
			if (this->coins[i].getGlobalBounds().intersects(this->gracz->get_bounds()))
			{
				this->pts += 1;
				if (this->chances < 3)
				{
					this->chances += 1;
				}
				std::cout << "Points +1" << std::endl;
				this->coins.erase(this->coins.begin() + i);
			}

		}
	}

	bool collision()
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (this->obstacles[i].getGlobalBounds().contains(this->gracz->get_position()))
			{

				return true;

			}
			else
			{
				return false;
			}
		}
	}

	//Coins+obstacles and game functions

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

	void progress()
	{
		if (this->game_time >= this->progress_time)
		{
			game_time = Time::Zero;
			this->game_obj_speed += 0.15f;
			this->game_cns_speed += 0.15f;
		}
	}

	//Coins functions

	void set_coins()
	{
		switch (option)
		{
		case 0:
			this->coin.setPosition(800.f + this->gracz->get_space(), static_cast<float>(rand() % 146 + 155));
			break;
		case 1:
			this->coin.setPosition(800.f + this->gracz->get_space(), static_cast<float>(rand() % 126 + 295));
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
			this->coins[i].setPosition(Vector2f(this->coins[i].getPosition().x - this->game_cns_speed, this->coins[i].getPosition().y));
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
			this->obstacles[i].setPosition(Vector2f(this->obstacles[i].getPosition().x - this->game_obj_speed, this->obstacles[i].getPosition().y));

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


	//RESOURCES SETTING & UPLOADING

	//text

	void show_points()
	{
		std::stringstream points_string, miss_points_string;

		points_string << "Points: " << this->pts;
		this->points.setString(points_string.str());

		miss_points_string << "Chances: " << this->chances;
		this->chance.setString(miss_points_string.str());

	}

	void show_game_over()
	{
		std::stringstream go, end_pts;

		go << "GAME OVER";
		end_pts << "YOUR SCORE: " << this->pts;

		this->game_over.setString(go.str());
		this->end_points.setString(end_pts.str());
	}

	//textures upload
	
	void load_textures()
	{
		this->rd.loadFromFile("Bg/road.png");
		this->bg.loadFromFile("Bg/bg.png");
		this->obs.loadFromFile("Bg/obstacle.png");
		this->cns.loadFromFile("Bg/coin.png");
	}
	
	void create_background()
	{
		this->background_image.setTexture(this->bg);
		this->background_image.setPosition(Vector2f(0.f, 0.f));
	}
	
	void create_road()
	{
		this->road_image.setTexture(this->rd);
		this->road_image.setPosition(Vector2f(0.f, 150.f));
	}

	
public:

	//Constructor/Destructor

	Game(int c_chosen)
	{
		//Spawn chosen player

		switch (c_chosen)
		{
		case 1:
			this->gracz = new Ferrari;
			break;
		case 2:
			this->gracz = new F1;
			break;
		case 3:
			this->gracz = new Miami;
			break;
		}
		
		

		//Clock reset and game-start settings

		time += clock.restart();

		game_time += clock.restart();

		this->game_obj_speed = this->gracz->get_obj_speed();
		this->game_cns_speed = this->gracz->get_cns_speed();

		spawn_time = seconds(this->gracz->get_speed());

		//Creating a new window object on window pointer

		std::cout << std::endl << "GAME_INFO: GAME STARTED"<< std::endl ;
		this->window = new RenderWindow(VideoMode(800, 600), "Game");
		this->window->setFramerateLimit(144);
		this->window->setVerticalSyncEnabled(false);

		//Upload textures

		this->load_textures();
		this->create_background();
		this->create_road();
		

		//Set font
		this->font.loadFromFile("Fonts/PixelEmulator-xq08.ttf");

		this->points.setFont(this->font);
		this->points.setPosition(Vector2f(80.f, 40.f));

		this->chance.setFont(this->font);
		this->chance.setPosition(Vector2f(80.f, 80.f));

		this->game_over.setFont(this->font);
		this->game_over.setPosition(Vector2f(230.f, 200.f));
		this->game_over.setCharacterSize(50);

		this->end_points.setFont(this->font);
		this->end_points.setPosition(Vector2f(240.f, 270.f));
		this->end_points.setCharacterSize(30);

	}

	~Game()
	{
		delete this->window;
		delete this->gracz;
	}

	//Return

	int get_points()
	{
		return this->pts;
	}

	//Bool information for game loop

	bool get_esc_g()
	{
		return this->esc_g;
	}

	bool get_working()
	{
		return this->window->isOpen();
	}

	//New information and game render

	void update()
	{
		time += clock.restart();
		game_time += game_clock.restart();
		
		this->pollEvents();
		this->show_points();
		this->progress();

		//Objects spawn

		if (this->esc_g == false)
		{
			this->creating_objects();
			this->gracz->player_on_road();
			this->move_obstacles();
			this->move_coins();
			this->gain_points();
			this->collision();
		}

		//possible endgame

		if (this->collision())
		{
			this->show_game_over();
			this->window->draw(this->game_over);
			this->window->draw(this->end_points);
			this->window->display();

			sleep(seconds(2.5));

			this->esc_g = true;
			std::cout << std::endl << "GAME OVER!" << std::endl << "COLLISION!" << std::endl << "POINTS: " << this->pts;
		}

		if (this->chances <= 0)
		{
			this->show_game_over();
			this->window->draw(this->game_over);
			this->window->draw(this->end_points);
			this->window->display();

			sleep(seconds(2.5));

			this->esc_g = true;
			std::cout << std::endl << "GAME OVER!" << std::endl << "YOU MISSED TOO MANY COINS!"  << std::endl << "POINTS: " << this->pts;
		}

		if (!this->gracz->player_on_road())
		{
			this->show_game_over();
			this->window->draw(this->game_over);	
			this->window->draw(this->end_points);
			this->window->display();


			sleep(seconds(2.5));

			this->esc_g = true;
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