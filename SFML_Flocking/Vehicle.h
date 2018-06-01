#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include "Wall.h"

class Vehicle 
{
private:
	sf::CircleShape triangle;
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;
	float m_MaxSpeed;
	float m_MaxForce;
	float radius;
	const int gameWidth = 1280;
	const int gameHeight = 720;
	std::vector<sf::Vector2f> m_Feelers;
public:
	Vehicle(sf::Vector2f pos);
	~Vehicle();
	sf::Vector2f seek(sf::Vector2f &target);
	sf::Vector2f flee(sf::Vector2f &target);
	sf::Vector2f arrive(sf::Vector2f &target);
	sf::Vector2f seperate(std::vector<Vehicle> &flocks);
	sf::Vector2f align(std::vector<Vehicle> &flocks);
	sf::Vector2f cohesion(std::vector<Vehicle> &flocks);
	void flock(std::vector<Vehicle> &flocks, float sep, float ali, float coh);
	sf::Vector2f WallAvoidance();
	void run(sf::RenderWindow& window, std::vector<Vehicle> &flocks,float sep, float ali, float coh);
	void applyForce(sf::Vector2f& force);
	void update();
	void draw(sf::RenderWindow& window);
	void CreateFeelers();
private:
	void borders();
};


