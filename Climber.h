#pragma once
#include <SFML/Graphics.hpp>
#include "Plattform.h"

enum PLAYER_ANIMATION_STATES{IDLE = 0, MOVINGLEFT, MOVINGRIGHT, JUMPING, FALLING};

class Climber :public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	// Animation
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	bool animationSwitch;

	// Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	
	bool jumping;

	float windowWidth;
	float windowHeight;
	float speed;

	void initVariables();
	void initAnimation();
	void initPhysics();

public:
	Climber(float speed, float windWidth, float windHeight);
	~Climber();

	// Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;  
	const sf::Vector2f getPosition() const;

	// Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	// Functions
	void resetAnimationTimer();
	void move(float windowWidth, float windowHeight);
	void movePhys(const float dirX, const float dirY);

	void updateAnimation();
	void updatePhysics();

	void update();
	bool detectCollision(Plattform& rectShape);
	void collision(Plattform& rectshape, sf::FloatRect nextPos);
	bool onTopOf(Plattform& platta) const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};