//
// Created by kuba on 20.05.24.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

namespace CSG2D {
    class Rectangle: public Shape{
    private:
        float w_;
        float h_;
    public:
        Rectangle(float w, float h, const sf::Vector2f &position, double angle_rad)
            : Shape(position, angle_rad), w_(w), h_(h) {
        }
        bool isIn(const sf::Vector2f &test_position) const override;
    };


}


#endif //RECTANGLE_H
