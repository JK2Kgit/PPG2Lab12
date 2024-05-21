//
// Created by kuba on 20.05.24.
//

#include "circle.h"

namespace CSG2D {
    bool Circle::isIn(const sf::Vector2f &test_position) const {
        auto diff = position_ - test_position;
        return length(diff) < radius_;
    }
}

