#include "VehicleSystem.h"
VehicleSystem::VehicleSystem(sf::Vector2f& pos)
{
	for (int i = 0; i < 200; ++i)
	{
		Vehicle boid(pos);
		flocks.push_back(boid);
	}

	sepParm = 1.5f;
	aliParm = 1.0f;
	cohParm = 0.8f;
}

void VehicleSystem::run(sf::RenderWindow& window)
{
	for (auto& boid : flocks)
	{
		boid.run(window, flocks, sepParm, aliParm, cohParm);
	}
}

void VehicleSystem::addBoid(const Vehicle& boid)
{
	flocks.push_back(boid);
}

void VehicleSystem::removeBoid()
{
	flocks.pop_back();
}

void VehicleSystem::turnoffSep()
{
	sepParm = 0.0f;
}

void VehicleSystem::turnonSep()
{
	sepParm = 1.5f;
}

void VehicleSystem::turnoffAli()
{
	aliParm = 0.0f;
}

void VehicleSystem::turnonAli()
{
	aliParm = 1.0f;
}

void VehicleSystem::turnoffCoh()
{
	cohParm = 0.0f;
}

void VehicleSystem::turnonCoh()
{
	cohParm = 0.8f;
}