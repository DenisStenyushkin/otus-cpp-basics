#pragma once
#include "Color.hpp"
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(Point center, double radius, Velocity velocity,
         Color color, bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getIsCollidable() const;
private:
    Point m_center;
    Color m_color;
    double m_radius;
    Velocity m_velocity;
    bool m_isCollidable;
};
