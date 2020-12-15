#include "Input.h"

Input::Input(Font* font)
{
	text.setFont(*font);
	text.setCharacterSize(40);
	text.setFillColor(Color(200, 200, 200, 255));
	text.setPosition(1200, high - 25);
	text.setOutlineThickness(3.0f);
	text.setOutlineColor(Color::Black);

	box.setSize(Vector2f(400, 100));
	box.setOrigin(box.getSize() / 2.0f);
	box.setPosition(Vector2f(1375, high));
	cursor.setSize(Vector2f(5, 64));
	cursor.setOrigin(cursor.getSize() / 2.0f);
	cursor.setPosition(Vector2f(1200, high));
	cursor.setFillColor(Color(200, 200, 200, 255));
	cursor.setOutlineThickness(3.0f);
	cursor.setOutlineColor(Color::Black);

	state = false;
	totalTime = 0.0f;
}

Input::~Input()
{
}

void Input::Draw(RenderWindow& window)
{
	//window.draw(box);
	window.draw(text);
	if (state == true) window.draw(cursor);
}

void Input::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= 0.5) {
		totalTime = 0;
		state = !state;
	}


}

void Input::Update(string str)
{
	this->str = str;
	text.setString(str);
	cursor.setPosition(Vector2f((float)(1208 + (str.size() * 23)), (float)high));
}