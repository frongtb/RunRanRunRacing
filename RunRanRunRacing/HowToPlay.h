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

#define MAX_NUM_OF_ITEM 4
class HowToPlay
{
public:
	HowToPlay(float width, float height);
	virtual ~HowToPlay();

	void draw(sf::RenderWindow& app);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text mainmenu[MAX_NUM_OF_ITEM];
	sf::Texture menu;
	sf::Sprite menusp;


};



