#pragma once

#include "Color.hpp"
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Sparkle
{
public:
    inline Sparkle(const Point& center, double radius,
            const Velocity& velocity, const Color& color,
            double lifespan): m_center{center}, m_radius{radius},
                              m_velocity{velocity}, m_color{color},
                              m_lifespan{lifespan}, m_original_lifespan{lifespan} 
    { }
    
    inline Point getCenter() const {
        return m_center;
    }
    inline void setCenter(const Point& center) {
        m_center = center;
    }

    inline double getRadius() const {
        return m_radius;
    }
    inline void setRadius(double radius) {
        m_radius = radius;
    }

    inline Velocity getVelocity() const {
        return m_velocity;
    }

    inline double getLifeSpan() const {
        return m_lifespan;
    }
    inline void setLifespan(double lifespan) {
        m_lifespan = lifespan;
    }

    inline void draw(Painter& painter) const {
        if (m_lifespan > 0) {
            double radius = m_radius * m_lifespan / m_original_lifespan;
            painter.draw(m_center, radius, m_color);
        }
    }
private:
    Point m_center;
    double m_radius;
    Velocity m_velocity;
    Color m_color;
    double m_lifespan;
    double m_original_lifespan;
};
