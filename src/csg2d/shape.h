#pragma once
#include "libincludes.h"

namespace CSG2D
{
class Shape
{
public:
	Shape(const sf::Vector2f &position, double angle_rad) : position_(position), angle_rad_(angle_rad) {}

protected:
	sf::Vector2f position_;
	double angle_rad_;

public:
	[[nodiscard]] virtual bool isIn(const sf::Vector2f &test_position) const = 0;
};
}

float length(const sf::Vector2f v2f);