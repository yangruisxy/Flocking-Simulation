#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>

class Wall2d
{
public:
	Wall2d(const sf::Vector2f& point1, const sf::Vector2f& point2) :
		color(sf::Color::Red)
	{
		vertices[0] = point1;
		vertices[0].color = color;
		vertices[1] = point2;
		vertices[1].color = color;
	}

	void draw(sf::RenderWindow& window);

	sf::Vector2f From() const {};
	sf::Vector2f To() const {};
private:
	sf::Vertex vertices[2];
	sf::Color color;
};