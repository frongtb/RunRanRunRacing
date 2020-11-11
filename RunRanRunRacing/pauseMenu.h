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
#define MAX_NUM_OF_ITEM 3
class pauseMenu
{
public:
	pauseMenu(float width, float height);
	virtual ~pauseMenu();

	void draw(sf::RenderWindow& app);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text pausemenu[MAX_NUM_OF_ITEM];
};