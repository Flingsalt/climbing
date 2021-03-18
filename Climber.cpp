#include "Climber.h"
#include <iostream>

void Climber::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Climber::initPhysics()
{
	this->velocityMax = 10.0f;
	this->velocityMin = 1.0f;
	this->acceleration = 3.30f;
	this->drag = 0.93f;
	this->gravity = 1.0f;                                                                                                                                                                                                                                                                                                                     
}

Climber::Climber(float speed, float windWidth, float windHeight)
	:speed(speed), windowWidth(windWidth), windowHeight(windHeight)
{
	this->texture.loadFromFile("../Images/player.png");
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, this->texture.getSize().x/4, this->texture.getSize().y/4);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2, 2);

	this->initVariables();
	this->initAnimation();
	this->initPhysics();

	this->jumping = false;

	this->sprite.setPosition(30, 50);
	this->speed = 7.0f;
}

Climber::~Climber()
{

}

const bool& Climber::getAnimSwitch()
{
	bool animSwitch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return animSwitch;
}

const sf::FloatRect Climber::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Climber::getPosition() const
{
	return this->sprite.getPosition();
}

void Climber::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Climber::resetVelocityY()
{
	this->velocity.y = 0.0f;
}

void Climber::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Climber::move(float windowWidth, float windowHeight)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float xAxis = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);

		static float lastPosX = this->sprite.getPosition().x;
		if (this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > windowWidth - this->sprite.getGlobalBounds().width)
		{
			
			this->sprite.setPosition(lastPosX, this->sprite.getPosition().y);
		}
		this->movePhys(this->speed * xAxis, this->velocity.y);
		lastPosX = this->sprite.getPosition().x;
		this->animState = (velocity.x > 0) ? PLAYER_ANIMATION_STATES::MOVINGRIGHT : PLAYER_ANIMATION_STATES::MOVINGLEFT;

	}
	
	 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->sprite.getPosition().y > windowHeight - this->sprite.getGlobalBounds().height - 2) 
	{
		this->velocity.y = -21;
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;	
		jumping = true;
	}
	else
	{
		// this->animState = PLAYER_ANIMATION_STATES::IDLE;
	}	

	
}

void Climber::movePhys(const float dirX, const float dirY)
{
	// Acceleration
	this->velocity.x += dirX * this->acceleration;
	
	// Acceleration limit
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.0f) ? -1.0f : 1.0f);
	}
}


void Climber::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 0.0f;
			this->currentFrame.left += this->texture.getSize().x /4;
			if (this->currentFrame.left >= this->texture.getSize().x)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if(this->animState == PLAYER_ANIMATION_STATES::MOVINGRIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			// Kontrollera med cout currentFrame och timern
			this->currentFrame.top = this->texture.getSize().y / 2;
			this->currentFrame.left += this->texture.getSize().x /4;
			if (this->currentFrame.left >= this->texture.getSize().x)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVINGLEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			// Kontrollera med cout currentFrame och timern
			this->currentFrame.top = this->texture.getSize().y / 4;
			this->currentFrame.left = this->texture.getSize().x / 4;
			if (this->currentFrame.left >= this->texture.getSize().x)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		
	}
	else
	{
		this->animationTimer.restart();
	}
}

void Climber::updatePhysics()
{
	// Gravity
	this->velocity.y += 1.0f * this->gravity;

	// Deceleration
	this->velocity.x *= this->drag;

	// Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.0f;
	}
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.0f;
	}

	

	// Observationer
	// updatephysics använd i någon av move if-satserna ger en boost i hastighet
	// Kan användas när en annan knapp är intryckt. Möjlig Dash?
}

void Climber::initVariables()
{
	this->animState = IDLE;

}

void Climber::update()
{
	
	this->updateAnimation();
	this->updatePhysics();
	this->move(windowWidth, windowHeight);
	this->sprite.move(velocity);
}

bool Climber::detectCollision(Plattform& rectShape)
{
	bool didIntersect = false;
	if (this->sprite.getGlobalBounds().intersects(rectShape.getBounds()))
	{
		collision(rectShape, this->sprite.getGlobalBounds());
		didIntersect = true;
	}

	return didIntersect;
}

void Climber::collision(Plattform& rectshape, sf::FloatRect nextPos)
{
	
	

		nextPos = this->sprite.getGlobalBounds();
		nextPos.left += velocity.x;
		nextPos.top += velocity.y;
		if (rectshape.getBounds().intersects(nextPos))
		{
			// Bottom collision
			if ((this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height) > rectshape.getBounds().top &&
				this->sprite.getGlobalBounds().intersects(rectshape.getBounds()))
			{
				velocity.y = 0.0f;
				this->sprite.setPosition(this->sprite.getGlobalBounds().left, rectshape.getBounds().top
					- this->sprite.getGlobalBounds().height);
				

			}
			// Top collision
			if ((this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().width) > rectshape.getBounds().height + rectshape.getBounds().width &&
				this->sprite.getGlobalBounds().intersects(rectshape.getBounds()))
			{
				velocity.y = 0.0f;
				this->sprite.setPosition(this->sprite.getGlobalBounds().left, rectshape.getBounds().width
					+ rectshape.getBounds().top);

			}

			// Right collision
			if ((this->sprite.getGlobalBounds().width + this->sprite.getGlobalBounds().height) > rectshape.getBounds().height &&
				this->sprite.getGlobalBounds().intersects(rectshape.getBounds()))
			{
				velocity.x = 0.0f;
				this->sprite.setPosition(rectshape.getBounds().left - this->sprite.getGlobalBounds().width,
					this->sprite.getGlobalBounds().top);

			}
			// Left collision
			if ((this->sprite.getGlobalBounds().height) > rectshape.getBounds().left &&
				this->sprite.getGlobalBounds().intersects(rectshape.getBounds()))
			{
				velocity.x = 0.0f;
				this->sprite.setPosition(rectshape.getBounds().left + rectshape.getBounds().width,
					this->sprite.getGlobalBounds().top);

			}
		}

	

	
}

bool Climber::onTopOf(Plattform& platta) const
{
	bool didHit = false;
	// Sprite on top
	if ((this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height) > platta.getBounds().top && 
		this->sprite.getGlobalBounds().intersects(platta.getBounds()))
	{		
		didHit = true;
	}
	
	
	//Sprite from below
	if ((this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().width) > platta.getBounds().height + platta.getBounds().width &&
		this->sprite.getGlobalBounds().intersects(platta.getBounds()))
	{
		std::cout << "Below!";
		didHit = true;
	}
	return didHit;
}

void Climber::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}


