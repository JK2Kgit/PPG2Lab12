#pragma once
#include "shape.h"

inline float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) { return v1.x*v2.x + v1.y*v2.y; }
inline float lengthSq(const sf::Vector2f& v) { return dot(v, v); }
inline float length(const sf::Vector2f& v) { return std::sqrt(lengthSq(v)); }
inline float degToRad(float deg) { return deg/180.f*std::numbers::pi; }
inline float radToDeg(float rad) { return rad/std::numbers::pi*180.f; }
inline std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v)
{
	stream << "[" << v.x << ", " << v.y << "]";
	return stream;
}

sf::Vector2f rotate(const sf::Vector2f &v, float angle_rad);
void updateTexture(sf::Texture &t, const CSG2D::Shape &s, const sf::Color &foreground_color, const sf::Color &background_color);
std::shared_ptr<CSG2D::Shape> createCSG2DScene();
