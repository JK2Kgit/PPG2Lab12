//
// Created by kuba on 20.05.24.
//

#include "complexShape.h"

#include "functions.h"

namespace CSG2D {
    bool ComplexShape::isIn(const sf::Vector2f &test_position) const {
        auto diff = test_position - position_;
        const auto rotated = rotate(diff, -angle_rad_);
        switch (op_) {
            case OPERATION::UNION:
                return s1_->isIn(rotated) || s2_->isIn(rotated);
            case OPERATION::DIFFERENCE:
                return s1_->isIn(rotated) && ! s2_->isIn(rotated);
            case OPERATION::INTERSECTION:
                return s1_->isIn(rotated) && s2_->isIn(rotated);
        }
        return false;
    }
}
