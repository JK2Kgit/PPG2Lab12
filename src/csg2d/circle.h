//
// Created by kuba on 20.05.24.
//

#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

namespace CSG2D {
    class Circle : public Shape {
    private:
        float radius_;

    public:
        Circle(const float radius, const sf::Vector2f &position)
            : Shape(position, 0.0), radius_(radius) {
        }

        [[nodiscard]] bool isIn(const sf::Vector2f &test_position) const override;
    };
}

#endif //CIRCLE_H
