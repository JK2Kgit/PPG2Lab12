//
// Created by kuba on 20.05.24.
//

#include "rectangle.h"

#include "functions.h"

namespace CSG2D {
    bool Rectangle::isIn(const sf::Vector2f &test_position) const {
        const auto diff = test_position - this->position_;
        const auto rotated = rotate(diff, -this->angle_rad_);
        return fabs(rotated.y) < this->h_/2 && fabs(rotated.x) < this->w_/2;
    }
}
