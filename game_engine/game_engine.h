#pragma once

#include <string>

#include "args.h"


namespace game_engine {
    
    enum class StepOutcome
    {
        Less,
        Greater,
        Equal
    };

    struct GameStatus
    {
        std::string playerName;
        int targetNumber;
        int currentGuess;
        int numGuessesMade{0};
    };

    StepOutcome gameStep(GameStatus& gameStatus);
    int getMaxTargetNumber(const args::Args& args);
    
}
