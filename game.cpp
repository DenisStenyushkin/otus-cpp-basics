#include <iostream>
#include <string>
#include <unordered_map>

#include "args.h"
#include "game_engine.h"
#include "rng.h"
#include "scores.h"


int main(int argc, char** argv) {
    args::Args args = args::getArguments(argc, argv);
    if (!args.valid.is_valid) {
        std::cout << "Error: " << args.valid.reason << "\n";
        return -1;
    }

    std::unordered_map<std::string, int> scores = scores::readAllScores();
    if (args.table) {
        std::cout << "High scores table:\n";
        for (const auto& [playerName, score] : scores) {
            std::cout << playerName << "\t" << score << "\n";
        }

        return 0;
    }

    game_engine::GameStatus status;
    int maxTargetNumber = game_engine::getMaxTargetNumber(args);
    status.targetNumber = rng::getRandomValue(maxTargetNumber);
    std::cout << "Enter your name: ";
    std::cin >> status.playerName;

    std::cout << "Guess number between 0 and " << maxTargetNumber << "\n";
    do {

        std::cout << "Enter your guess: ";
        std::cin >> status.currentGuess;
        if (std::cin.fail()) {
            std::cout << "Please enter numeric values only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        game_engine::StepOutcome stepOutcome = game_engine::gameStep(status);
        if (stepOutcome == game_engine::StepOutcome::Less) {
            std::cout << "Target number is less than your guess.\n";
        }
        else if (stepOutcome == game_engine::StepOutcome::Greater) {
            std::cout << "Target number is greater than your guess.\n";
        }
        else {
            std::cout << "Congratulations! You win!\n";
            break;
        }

    } while (true);

    scores::writeScoreIfBetter(status.playerName, status.numGuessesMade);

    return 0;
}
