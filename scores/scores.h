#pragma once

#include <fstream>
#include <string>
#include <unordered_map>


namespace scores {
    
    static const std::string SCORES_FILE_NAME = "scores.txt";

    std::unordered_map<std::string, int> readAllScores();
    void writeScoreIfBetter(const std::string& playerName, int score);

}
