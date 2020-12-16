#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/Cascadia.ttf"))
	{
		std::cout << "game failed to load font menu " << "\n";
	}
	sf::Vector2f posMid = sf::Vector2f(width / 2 - this->playerText.getGlobalBounds().width / 2, height / 2 - this->playerText.getGlobalBounds().height / 2);

	this->leaderboard = new Plane(width / 2 - 200.f, height / 2 - 200.f, 400.f, 400.f, &this->font, 48, 48);


	this->enter.setString("Press Enter to Start");
	this->enter.setFont(this->font);
	this->enter.setCharacterSize(48);
	this->enter.setOutlineColor(sf::Color::Black);
	this->enter.setOutlineThickness(1.f);
	this->enter.setFillColor(sf::Color::Green);
	this->enter.setPosition(width / 2 - this->enter.getGlobalBounds().width / 2 - 40.f, height / 2 - 100.f);

	this->windowSize = sf::Vector2f(width, height);

	this->playerText.setCharacterSize(48);
	this->playerText.setOutlineColor(sf::Color::Black);
	this->playerText.setOutlineThickness(1.f);
	this->playerText.setFillColor(sf::Color::White);
	this->playerText.setFont(this->font);
	this->playerText.setPosition(posMid.x - 180.f + 2.f - 50.f + 5.f, posMid.y);

	this->textBox.setSize(sf::Vector2f(360.f + 20.f, playerText.getGlobalBounds().height + 50.f));
	this->textBox.setOutlineThickness(2.f);
	this->textBox.setOutlineColor(sf::Color::Black);
	//	this->textCursor.setFillColor(sf::Color::Black);

	this->textBox.setPosition(sf::Vector2f(posMid.x - 180.f - 50.f - 10.f + 5.f, posMid.y + 10.f));
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
