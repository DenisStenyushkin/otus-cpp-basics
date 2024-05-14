#include "Effects.hpp"
#include "sparkle.hpp"
#include <vector>

Effects::Effects(double timePerTick) : timePerTick{timePerTick} {}

void Effects::update(std::vector<Sparkle>& sparkles, size_t ticks) const {
    for (size_t t = 0; t < ticks; ++t) {
        for (auto& s : sparkles) {
            Point newCenter = s.getCenter() + s.getVelocity().vector() * timePerTick;
            s.setCenter(newCenter);

            s.setLifespan(s.getLifeSpan() - timePerTick);
        }
    }
}
