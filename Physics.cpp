#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

std::vector<Point> Physics::update(std::vector<Ball>& balls, const size_t ticks) const {
    std::vector<Point> collisionPoints;
    
    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        for (const auto& p : collideWithBox(balls)) {
            collisionPoints.push_back(p);
        }
        for (const auto& p : collideBalls(balls)) {
            collisionPoints.push_back(p);
        }
    }

    return collisionPoints;
}

std::vector<Point> Physics::collideBalls(std::vector<Ball>& balls) const {
    std::vector<Point> collisionPoints;

    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->getIsCollidable()) continue;

        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!b->getIsCollidable()) continue;

            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                Point A = a->getCenter();
                Point B = b->getCenter();
                double rA = a->getRadius();
                double rB = b->getRadius();
                Point collisionPoint{ A + (B - A) * rA / (rA + rB) };
                collisionPoints.push_back( collisionPoint );
                
                processCollision(*a, *b, distanceBetweenCenters2);
            }
        }
    }

    return collisionPoints;
}

std::vector<Point> Physics::collideWithBox(std::vector<Ball>& balls) const {
    std::vector<Point> collisionPoints;

    for (Ball& ball : balls) {
        if (!ball.getIsCollidable()) continue;

        const Point p = ball.getCenter();
        const double r = ball.getRadius();

        auto outLo = [](double v, double lo) {
            return v < lo;
        };
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);

            collisionPoints.push_back( Point{ outLo(p.x, topLeft.x + r) ? topLeft.x : bottomRight.x,
                                              p.y} );
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);

            collisionPoints.push_back( Point{ p.x,
                                              outLo(p.y, topLeft.y + r) ? topLeft.y : bottomRight.y} );
        }
    }

    return collisionPoints;
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
