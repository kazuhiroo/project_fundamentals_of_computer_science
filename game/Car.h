#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


class Car
{
private:
	Texture car_im;
	Sprite car;


	void car_image()
	{
		this->car_im.loadFromFile("Bg/car.png");
	}


	void create_car_im()
	{
		this->car.setTexture(this->car_im);
	}
public:
	Car()
	{
		this->car_image();
		this->create_car_im();
	};

	~Car()
	{

	};


	//funkcje

	void update()
	{

	}

	void render(RenderTarget& target)
	{
		target.draw(this->car);
	}
};

