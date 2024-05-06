#include "rng.h"

namespace rng
{
    int getRandomValue(int maxValue)
    {
        std::srand(std::time(nullptr));
        return std::rand() % maxValue;
    }
}
