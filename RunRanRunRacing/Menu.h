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

#include"Plane.h"

#define MAX_NUM_OF_ITEM 4
class Menu
{
public:
	Menu(float width,float height);
	~Menu();

	Plane* leaderboard;
	sf::Text enter;
	sf::RectangleShape textBox;
	sf::RectangleShape textPlane;
	sf::RectangleShape textCursor;

	sf::Vector2f windowSize;
	sf::Text playerText;
	void draw(sf::RenderWindow& app);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text mainmenu[MAX_NUM_OF_ITEM];
	sf::Texture menu;
	sf::Sprite menusp;


};

