#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Plane
{
protected:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text header;
	sf::Text content;

	virtual void initHeader(unsigned header_character_size);
	virtual void initContent(unsigned content_character_size);
public:
	Plane(float x, float y, float width, float height,
		sf::Font* font, unsigned header_character_size, unsigned content_character_size);
	virtual ~Plane();

	virtual void render(sf::RenderTarget* target);
};