#include "Plane.h"

void Plane::initHeader(unsigned header_character_size)
{
	std::string header = "SCORE BOARD";
	this->header.setFont(*this->font);
	this->header.setString(header);
	this->header.setCharacterSize(header_character_size);
	//this->header.setFillColor(sf::Color(250, 250, 250, 250));
	this->header.setFillColor(sf::Color::Green);
	this->header.setOutlineThickness(1.f);
	this->header.setOutlineColor(sf::Color::Black);
	this->header.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->header.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 10.f
	);
}

void Plane::initContent(unsigned content_character_size)
{
	std::ifstream ifs("images/scores.txt");

	if (ifs.is_open())
	{
		
		std::string playerScore = "";

		std::string content = "";
		int i = 1;
		while (ifs >> playerScore)
		{
			content += ( playerScore + "\n");
			++i;
		}
		
		this->content.setFont(*this->font);
		this->content.setString(content);
		this->content.setCharacterSize(content_character_size);
		this->content.setFillColor(sf::Color::Green);
		this->content.setOutlineColor(sf::Color::Black);
		this->content.setOutlineThickness(1.f);
		this->content.setPosition(625,220
			/*this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->content.getGlobalBounds().width / 1.5f,
			this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->content.getGlobalBounds().height / 2.f + 30.f*/);
		
		
	}

	ifs.close();

}

Plane::Plane(float x, float y, float width, float height, sf::Font* font,
	unsigned header_character_size, unsigned content_character_size)
{
	this->font = font;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color(70, 70, 70, 200));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);

	this->initHeader(header_character_size);
	this->initContent(content_character_size);
}

Plane::~Plane()
{
}

void Plane::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	//target->draw(this->header);
	target->draw(this->content);
}