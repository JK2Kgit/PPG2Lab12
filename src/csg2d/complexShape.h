//
// Created by kuba on 20.05.24.
//

#ifndef COMPLEXSHAPE_H
#define COMPLEXSHAPE_H
#include <utility>

#include "operation.h"
#include "shape.h"


namespace CSG2D {
    class ComplexShape: public Shape {
    private:
        std::shared_ptr<Shape> s1_;
        std::shared_ptr<Shape> s2_;
        OPERATION op_;
    public:
        ComplexShape(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, OPERATION op, const sf::Vector2f &position, double angle_rad)
            : Shape(position, angle_rad), s1_(std::move(s1)), s2_(std::move(s2)), op_(op) {
        }

        bool isIn(const sf::Vector2f &test_position) const override;
    };
}



#endif //COMPLEXSHAPE_H
