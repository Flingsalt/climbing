#pragma once
#include <SFML/Graphics.hpp>
#include "Climber.h"
#include "Plattform.h"

class CGame
{
public:
	static const int HEIGHT = 600;
	static const int WIDTH = 900;

private:
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	
	sf::Font font;
	sf::Text text;
	sf::CircleShape circle;
	sf::RenderWindow window;

	void handleEvents();
	void update();
	void render();

public:
	CGame();
	~CGame();

	// Functions
	void updateCollision();

	// Skapa object av subklasser
	Plattform testPlatta;
	Plattform hoppPlattaOne;
	Plattform hoppPlattaTwo;

	Climber player;

	void run();
	
};