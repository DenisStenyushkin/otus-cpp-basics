#pragma once

#include "sparkle.hpp"
#include <vector>

class Effects {
public:
    Effects(double timePerTick);
    void update(std::vector<Sparkle>& sparkles, size_t ticks) const;

private:
    double timePerTick;
};
