#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/Cascadia.ttf"))
	{
		std::cout << "game failed to load font menu " << "\n";
	}
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::Red);
	mainmenu[0].setString("Play");
	mainmenu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 1));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(sf::Color::Yellow);
	mainmenu[1].setString("How to Play?");
	mainmenu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 2));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(sf::Color::Yellow);
	mainmenu[2].setString("Score Board");
	mainmenu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 3));

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(sf::Color::Yellow);
	mainmenu[3].setString("Exit");
	mainmenu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEM + 1) * 4));

	selectedItemIndex = 0;

	if (!menu.loadFromFile("images/bgmenu1.png"))
	{
		std::cout << "game failed to load font bgmenu " << "\n";
	}
	menusp.setTexture(menu);
	//menusp.setScale(sf::Vector2f(1.5f, 1.5f));
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& app)
{
	app.draw(menusp);
	for (int i = 0; i < MAX_NUM_OF_ITEM; i++)
	{
		app.draw(mainmenu[i]);
		
	}
	
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		mainmenu[selectedItemIndex].setFillColor(sf::Color::Yellow);
		selectedItemIndex--;
		mainmenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUM_OF_ITEM)
	{
		mainmenu[selectedItemIndex].setFillColor(sf::Color::Yellow);
		selectedItemIndex++;
		mainmenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
