#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vehicle.h"
class VehicleSystem
{
private:
	sf::Vector2f initPos;
	float sepParm;
	float aliParm;
	float cohParm;
	std::vector<Vehicle> flocks;
public:
	void run(sf::RenderWindow& window);
	VehicleSystem(sf::Vector2f& pos);
	void addBoid(const Vehicle& boid);
	void removeBoid();
	void turnoffSep();
	void turnonSep();
	void turnoffAli();
	void turnonAli();
	void turnoffCoh();
	void turnonCoh();
};