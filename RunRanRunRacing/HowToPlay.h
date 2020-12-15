#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Main.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<map>
#include<time.h>
#include<iostream>
#include <sstream>
#include <vector>

#define MAX_NUM_OF_ITEM 1
class HowToPlay
{
public:
	HowToPlay(float width, float height);
	virtual ~HowToPlay();

	void draw(sf::RenderWindow& app);

private:
	sf::Texture menu;
	sf::Sprite menusp;


};



