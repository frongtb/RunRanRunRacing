#include "pauseMenu.h"

pauseMenu::pauseMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts/Cascadia.ttf"))
		std::cout << "game failed to load font menu " << "\n";

	pausemenu[0].setFont(font);
	pausemenu[0].setFillColor(sf::Color::Red);
	pausemenu[0].setString("Continue");
	pausemenu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 1));

	pausemenu[1].setFont(font);
	pausemenu[1].setFillColor(sf::Color::Yellow);
	pausemenu[1].setString("Restart");
	pausemenu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 2));

	pausemenu[2].setFont(font);
	pausemenu[2].setFillColor(sf::Color::Yellow);
	pausemenu[2].setString("Back to Menu");
	pausemenu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 3));

	selectedItemIndex = 0;


}

pauseMenu::~pauseMenu()
{

}

void pauseMenu::draw(sf::RenderWindow& app)
{
	for (int i = 0; i < MAX_NUM_OF_ITEM; i++)
	{
		app.draw(pausemenu[i]);
	}
}

void pauseMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Yellow);
		selectedItemIndex--;
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void pauseMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUM_OF_ITEM)
	{
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Yellow);
		selectedItemIndex++;
		pausemenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
