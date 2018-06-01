#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include "Wall.h"
#include "VehicleSystem.h"
#include "path.h"

#define WINDOW_LENGTH 1280
#define WINDOW_WIDTH 720


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), "Flocking Application");
	sf::Vector2f spawnPoint = sf::Vector2f(WINDOW_LENGTH / 2, WINDOW_WIDTH / 2);
	VehicleSystem flocks(spawnPoint);
	std::vector<Wall2d> walls;

	Wall2d wall1(sf::Vector2f(100, 50), sf::Vector2f(1180, 50));
	Wall2d wall2(sf::Vector2f(100, 670), sf::Vector2f(1180, 670));
	Wall2d wall3(sf::Vector2f(100, 50), sf::Vector2f(100, 670));
	Wall2d wall4(sf::Vector2f(1180, 50), sf::Vector2f(1180, 670));
	walls.push_back(wall1);
	walls.push_back(wall2);
	walls.push_back(wall3);
	walls.push_back(wall4);
	float x = 10.0;
	float y = 10.0;
	float angle = atan2(y, x) * 180 / 3.14159265 + 90;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePosf((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
					Vehicle boid(mousePosf);
					flocks.addBoid(boid);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					flocks.removeBoid();
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::S)
				{
					flocks.turnoffSep();
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					flocks.turnonSep();
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					flocks.turnoffAli();
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					flocks.turnonAli();
				}
				else if (event.key.code == sf::Keyboard::C)
				{
					flocks.turnoffCoh();
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					flocks.turnonCoh();
				}
			}
		}
		sf::Vector2f mousePosf = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
		//boid.flee(mousePosf);
		window.clear();
		for (auto& wall : walls)
		{
			wall.draw(window);
		}
		flocks.run(window);
		window.display();
	}

}

