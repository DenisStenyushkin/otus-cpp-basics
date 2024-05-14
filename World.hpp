#pragma once
#include "Ball.hpp"
#include "Physics.hpp"
#include "sparkle.hpp"
#include "Effects.hpp"
#include <string>
#include <vector>

class Painter;

class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    //Объект движка визуальных эффектов
    Effects effects;
    // Контейнер с шарами
    std::vector<Ball> balls;
    // Контейнер с искрами
    std::vector<Sparkle> sparkles;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;

    // Создает искры в точках столкновения
    std::vector<Sparkle> initiateSparkles(const std::vector<Point>& collisionPoints,
                                          int numSparkles, double initialVelocityAbs);
};
