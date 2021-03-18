#include "CGame.h"
#include "Climber.h"
#include "Plattform.h"
#include <iostream>


CGame::CGame()
	:window(sf::VideoMode(WIDTH, HEIGHT), "Title"),
	testPlatta(800.0f, 30.0f, sf::Color::Green, 50, 550),
	hoppPlattaOne(250.0f, 30.0f, sf::Color::Green, 30, 300),
	hoppPlattaTwo(250.0f, 30.0f, sf::Color::Green, 620, 300),
	player(3.0f, WIDTH, HEIGHT)
{
	
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
}

CGame::~CGame()
{
	
}

void CGame::updateCollision()
{
	// collision bottom of screen
	if (this->player.getPosition().y 
		+ this->player.getGlobalBounds().height > this->window.getSize().y)
	{
		this->player.resetVelocityY();
		this->player.setPosition(this->player.getPosition().x,
		this->window.getSize().y - this->player.getGlobalBounds().height);
		
	}

	player.collision(hoppPlattaOne, player.getGlobalBounds());
}

void CGame::run()
{
	while (window.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void CGame::handleEvents()
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed)
		{
			
			window.close();
		}
	}
}

void CGame::update()
{


	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		player.update();
		
		

		updateCollision();
	}
	
}

void CGame::render()
{
	window.clear();
	window.draw(testPlatta);
	window.draw(hoppPlattaOne);
	window.draw(hoppPlattaTwo);
	window.draw(player);
	window.display();
}

