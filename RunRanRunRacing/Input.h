#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

const int high = 730;

class Input
{
public:
	Input(Font* font);
	~Input();
	void Draw(RenderWindow& window);
	void Update(float deltaTime);
	void Update(string str);
private:
	RectangleShape box, cursor;
	float totalTime;
	bool state;
	Text text;
	string str;
};
