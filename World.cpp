#include "World.hpp"
#include "Painter.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include <algorithm>
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

static constexpr int numSparkles = 8;
static constexpr double initialSparkleVelocityAbs = 100.0;
static constexpr int initialSparkleRadius = 10;
static constexpr double sparkleLifespan = 1.0;
static const Color sparkleColor{ 255, 0, 0};

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) : effects{timePerTick} {

    std::ifstream stream(worldFilePath);
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    /**
     * TODO: хорошее место для улучшения.
     * (x, y) и (vx, vy) - составные части объекта, также
     * как и (red, green, blue). Опять же, можно упростить
     * этот код, научившись читать сразу Point, Color...
     */
    Point center;
    Point velocity_vector;
    double radius;
    Color color;

    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор
        // его скорости (vx, vy)
        
        stream >> center >> velocity_vector;
        // Читаем три составляющие цвета шара
        stream >> color;
        // Читаем радиус шара
        stream >> radius;
        // Читаем свойство шара isCollidable, которое
        // указывает, требуется ли обрабатывать пересечение
        // шаров как столкновение. Если true - требуется.
        // В базовой части задания этот параметр
        stream >> std::boolalpha >> isCollidable;

        // TODO: место для доработки.
        // Здесь не хватает самого главного - создания
        // объекта класса Ball со свойствами, прочитанными
        // выше, и его помещения в контейнер balls
        Ball ball{ center, radius, velocity_vector, color,
                   isCollidable };

        // После того как мы каким-то образом
        // сконструируем объект Ball ball;
        // добавьте его в конец контейнера вызовом
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    for (const Sparkle& sparkle : sparkles) {
        sparkle.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    std::vector<Point> collisionPoints = physics.update(balls, ticks);
    
    for (const auto& s : initiateSparkles(collisionPoints, numSparkles, initialSparkleVelocityAbs)) {
        sparkles.push_back(s);
    }
    effects.update(sparkles, ticks);

    sparkles.erase(std::remove_if(
        sparkles.begin(), sparkles.end(),
        [](const Sparkle& s) {
            return s.getLifeSpan() <= 0;
        }), sparkles.end());
}

std::vector<Sparkle> World::initiateSparkles(const std::vector<Point>& collisionPoints,
                                             int numSparkles, double initialVelocityAbs) {
    std::vector<Sparkle> sparkles;

    for (const auto& p : collisionPoints) {
        for (int i=0; i < numSparkles; ++i) {
            Velocity v{ initialVelocityAbs, 360.0 * i / numSparkles };
            sparkles.push_back(Sparkle{ p, initialSparkleRadius, v, sparkleColor,
                                        sparkleLifespan });
        }
    }

    return sparkles;
}
