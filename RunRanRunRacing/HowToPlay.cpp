#include "HowToPlay.h"

HowToPlay::HowToPlay(float width, float height)
{


	if (!menu.loadFromFile("images/bgmenu2.png"))
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

}

