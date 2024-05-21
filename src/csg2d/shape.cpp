#include "shape.h"
float length(const sf::Vector2f v2f) {
    return std::sqrt(v2f.x * v2f.x + v2f.y * v2f.y);
}