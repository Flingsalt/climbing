#include "Plattform.h"

Plattform::Plattform(float width, float height, sf::Color color, float xPos, float yPos)
	:rectForm(sf::Vector2f(width, height))
{
	
	this->rectForm.setFillColor(color);
	this->rectForm.setPosition(xPos, yPos);

}

Plattform::Plattform(sf::Texture& textureSheet, sf::IntRect textureRect, bool damaging)
	: damaging(damaging = false)
{
	this->sprite.setTexture(textureSheet);
	this->sprite.setTextureRect(textureRect);
}

sf::FloatRect Plattform::getBounds() const
{
	return this->rectForm.getGlobalBounds();
}

void Plattform::update()
{
}

void Plattform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->rectForm);
}
