#pragma once
#include "Ball.hpp"
#include <vector>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    std::vector<Point> update(std::vector<Ball>& balls, size_t ticks) const;

  private:
    std::vector<Point> collideBalls(std::vector<Ball>& balls) const;
    std::vector<Point> collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
