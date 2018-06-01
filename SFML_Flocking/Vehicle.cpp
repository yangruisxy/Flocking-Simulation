#include "Vehicle.h"
#include "HelperFunction.h"
#include <random>
#include <iostream>

Vehicle::Vehicle(sf::Vector2f pos) : m_Feelers(3)
{
	radius = 6.0f;
	triangle = sf::CircleShape(radius, 3);
	triangle.setScale(sf::Vector2f(0.8f, 1.0f));
	m_Position = pos;
	m_Velocity = sf::Vector2f((std::rand() % 200 - 100) * 0.01, (std::rand() % 200 - 100) * 0.01);
	m_Acceleration = sf::Vector2f(0, 0);
	m_MaxSpeed = 1.0f;
	m_MaxForce = 0.1f;
}

Vehicle::~Vehicle()
{
	m_MaxSpeed = 0.0f;
	m_MaxForce = 0.0f;
}

sf::Vector2f Vehicle::seek(sf::Vector2f &target)
{
	sf::Vector2f des = target - m_Position;
	des = normalize(des);
	des *= m_MaxSpeed;
	sf::Vector2f steer = des - m_Velocity;
	steer = limit(steer, m_MaxForce);
	//applyForce(steer);
	return steer;
}

sf::Vector2f Vehicle::flee(sf::Vector2f &target)
{
	const double PanicDistanceSq = 100.0 * 100.0;
	sf::Vector2f des = m_Position - target;
	if (magnitudeSq(des) > PanicDistanceSq)
	{
		return sf::Vector2f(0, 0);
	}
	else
	{
		des = normalize(des);
		des *= m_MaxSpeed;
		sf::Vector2f steer = des - m_Velocity;
		steer = limit(steer, m_MaxForce);
		applyForce(steer);
		return steer;
	}
}

sf::Vector2f Vehicle::arrive(sf::Vector2f &target)
{
	sf::Vector2f des = target - m_Position;
	float d = magnitude(des);
	des = normalize(des);
	if (d < 100.0)
	{
		float m = map(d, sf::Vector2f(0, 0), sf::Vector2f(100.f, m_MaxSpeed));
		des *= m;
	}
	else
	{
		des *= m_MaxSpeed;
	}
	sf::Vector2f steer = des - m_Velocity;
	steer = limit(steer, m_MaxForce);
	return steer;
}

sf::Vector2f Vehicle::WallAvoidance()
{
	sf::Vector2f des = sf::Vector2f(0, 0);
	if (m_Position.x < 100 + 4 * radius)
	{
		des = sf::Vector2f(m_MaxSpeed, m_Velocity.y);
	}
	else if (m_Position.x > gameWidth - 100 - 4 * radius)
	{
		des = sf::Vector2f(-m_MaxSpeed, m_Velocity.y);
	}

	if (m_Position.y < 50 + 4 * radius)
	{
		des = sf::Vector2f(m_Velocity.x, m_MaxSpeed);
	}
	else if (m_Position.y > gameHeight - 50 -  4 *radius)
	{
		des = sf::Vector2f(m_Velocity.x, -m_MaxSpeed);
	}
	
	if (des != sf::Vector2f(0, 0))
	{
		des = normalize(des);
		des *= m_MaxSpeed;
		sf::Vector2f steer = des - m_Velocity;
		steer = limit(steer, m_MaxForce);
		steer *= 2.0f;
		applyForce(steer);
		return steer;
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}

void Vehicle::run(sf::RenderWindow & window, std::vector<Vehicle> &flocks, float sep, float ali, float coh)
{
	flock(flocks, sep, ali, coh);
	WallAvoidance();
	update();
	draw(window);
}

sf::Vector2f Vehicle::seperate(std::vector<Vehicle> &flocks)
{
	float desiredseperation = 25.0f;
	sf::Vector2f sum = sf::Vector2f(0, 0);
	int count = 0;
	for (auto& boid : flocks)
	{
		sf::Vector2f diff = m_Position - boid.m_Position;
		float d = magnitude(diff);
		if ((d > 0) && (d < desiredseperation))
		{
			diff = normalize(diff);
			diff /= d;
			sum += diff;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		sum = normalize(sum);
		sum *= m_MaxSpeed;
		sf::Vector2f steer = sum - m_Velocity;
		steer = limit(steer, m_MaxForce);
		return steer;
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}

sf::Vector2f Vehicle::align(std::vector<Vehicle>& flocks)
{
	float neighbordist = 50.0f;
	sf::Vector2f sum = sf::Vector2f(0, 0);
	int count = 0;
	for (auto& boid : flocks)
	{
		sf::Vector2f diff = m_Position - boid.m_Position;
		float d = magnitude(diff);
		if ((d > 0) && (d < neighbordist))
		{
			sum += boid.m_Velocity;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		sum = normalize(sum);
		sum *= m_MaxSpeed;
		sf::Vector2f steer = sum - m_Velocity;
		steer = limit(steer, m_MaxForce);
		return steer;
	}
	else
	{
		return sf::Vector2f(0, 0);
	}

}

sf::Vector2f Vehicle::cohesion(std::vector<Vehicle>& flocks)
{
	float neighbordist = 50.0f;
	sf::Vector2f sum = sf::Vector2f(0, 0);
	int count = 0;
	for (auto &boid : flocks)
	{
		sf::Vector2f diff = m_Position - boid.m_Position;
		float d = magnitude(diff);
		if ((d > 0) && (d < neighbordist))
		{
			sum += boid.m_Position;
			count++;
		}
	}
	if (count > 0)
	{
		sum /= (float)count;
		return seek(sum);
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}


void Vehicle::flock(std::vector<Vehicle> &flocks, float s, float a, float c)
{
	sf::Vector2f sep = seperate(flocks);
	sf::Vector2f ali = align(flocks);
	sf::Vector2f coh = cohesion(flocks);

	sep *= s;
	ali *= a;
	coh *= c;

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Vehicle::applyForce(sf::Vector2f &force)
{
	m_Acceleration += force;
}

void Vehicle::borders()
{
	if (m_Position.x < -radius) m_Position.x = gameWidth + radius;
	if (m_Position.y < -radius) m_Position.y = gameHeight + radius;
	if (m_Position.x > gameWidth + radius) m_Position.x = -radius;
	if (m_Position.y > gameHeight + radius) m_Position.y = -radius;
}

void Vehicle::update()
{
	m_Velocity += m_Acceleration;
	m_Velocity = limit(m_Velocity, m_MaxSpeed);
	m_Position += m_Velocity;
	m_Acceleration *= 0.0f;
	borders();
}

void Vehicle::draw(sf::RenderWindow &window)
{
	triangle.setPosition(m_Position);
	float angle = atan2(m_Velocity.y, m_Velocity.x) * 180 / 3.14159625 + 90;
	triangle.setRotation(angle);
	window.draw(triangle);
}
