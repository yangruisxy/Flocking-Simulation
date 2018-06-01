#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
class Line
{
public:
	Line(const sf::Vector2f& point1, const sf::Vector2f & point2);

	void draw(sf::RenderWindow& windwo) const;
private:
	sf::Vertex vertices[4];
	sf::Color color;
	float thickniess;
};