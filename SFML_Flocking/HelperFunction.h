#pragma once
#include <SFML/System.hpp>
#include <cmath>

float magnitude(sf::Vector2f &vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float magnitudeSq(sf::Vector2f &vector)
{
	return vector.x * vector.x + vector.y + vector.y;
}

sf::Vector2f normalize(sf::Vector2f &vector2)
{
	return vector2 / magnitude(vector2);
}

sf::Vector2f limit(sf::Vector2f &vector2, float max)
{
	float d = magnitude(vector2);
	if (d > max)
	{
		float angle = atan2(vector2.y, vector2.x);
		sf::Vector2f finalVector2;
		finalVector2.x = cos(angle) * max;
		finalVector2.y = sin(angle) * max;
		return finalVector2;
	}
	else
	{
		return vector2;
	}
}

float map(float val, sf::Vector2f min, sf::Vector2f max)
{
	return min.y + ((max.y - min.y) * (val - min.x)) / (max.x - min.x);
}

float dot(sf::Vector2f &left, sf::Vector2f &right)
{
	return left.x * right.x + left.y + right.y;
}

sf::Vector2f heading(sf::Vector2f &vector)
{
	float angle = atan2(vector.y, vector.x);
	sf::Vector2f heading = sf::Vector2f(cos(angle), sin(angle));
	return heading;
}

float angleBetween(sf::Vector2f& left, sf::Vector2f& right)
{
	float d = dot(left, right);
	float theta = (float)acos(d / magnitude(left) * magnitude(right));
	return theta;
}

sf::Vector2f getNormalPoint(sf::Vector2f& p, sf::Vector2f& a, sf::Vector2f& b)
{
	sf::Vector2f ap = p - a;
	sf::Vector2f ab = b - a;

	ab = normalize(ab);
	ab *= dot(ap, ab);

	sf::Vector2f normalPoint = a + ab;
	return normalPoint;
}