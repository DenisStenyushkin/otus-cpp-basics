#include "game_engine.h"

namespace game_engine {

    StepOutcome gameStep(GameStatus& gameStatus)
    {
        gameStatus.numGuessesMade += 1;
        if (gameStatus.targetNumber < gameStatus.currentGuess) {
            return StepOutcome::Less;
        }
        else if (gameStatus.targetNumber > gameStatus.currentGuess) {
            return StepOutcome::Greater;
        }
        else {
            return StepOutcome::Equal;
        }
    }

    int getMaxTargetNumber(const args::Args& args) {
        if (args.max != -1) {
            return args.max;
        }
        if (args.level == 1) {
            return 10;
        }
        if (args.level == 2) {
            return 50;
        }
        return 100;
    }

}
