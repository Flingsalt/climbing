#pragma once
#include <SFML/Graphics.hpp>

class Plattform: public sf::Drawable
{
private:
	sf::RectangleShape rectForm;

	sf::Sprite sprite;
	sf::Texture texture;
	
	// Variabler
	bool damaging;

public:
	Plattform(float width, float height, sf::Color color, float xPos = -100.0f, float yPos = -100.0f);
	Plattform(sf::Texture& textureSheet, sf::IntRect textureRect, bool damaging = false);

	sf::FloatRect getBounds() const;
	void update();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};