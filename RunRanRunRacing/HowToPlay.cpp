#include "HowToPlay.h"

HowToPlay::HowToPlay(float width, float height)
{
	if (!font.loadFromFile("Fonts/Cascadia.ttf"))
	{
		std::cout << "game failed to load font menu " << "\n";
	}
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::Red);
	mainmenu[0].setString("Back");
	mainmenu[0].setPosition(sf::Vector2f(width / 2, height / 1));



	selectedItemIndex = 0;

	if (!menu.loadFromFile("images/bgmenu1.png"))
	{
		std::cout << "game failed to load font bgmenu " << "\n";
	}
	menusp.setTexture(menu);
	//menusp.setScale(sf::Vector2f(1.5f, 1.5f));
}

HowToPlay::~HowToPlay()
{

}

void HowToPlay::draw(sf::RenderWindow& app)
{
	app.draw(menusp);
	for (int i = 0; i < MAX_NUM_OF_ITEM; i++)
	{
		app.draw(mainmenu[i]);

	}

}

