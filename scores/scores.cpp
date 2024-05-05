#include <fstream>
#include <string>
#include <unordered_map>

# include "scores.h"


namespace {
    
    bool check_key(std::unordered_map<std::string, int> m, std::string key)
    {
        // Key is not present
        if (m.find(key) == m.end())
            return false;

        return true;
    }

}

namespace scores {

    std::unordered_map<std::string, int> readAllScores()
    {
        std::unordered_map<std::string, int> map;

        std::string playerName;
        int score;

        std::ifstream file{ SCORES_FILE_NAME };
        if (file.is_open()) {
            while (file >> playerName >> score) {
                map[playerName] = score;
            }
        }
        file.close();

        return map;
    }

    void writeScoreIfBetter(const std::string& playerName, int score) {
        std::unordered_map<std::string, int> map{ readAllScores() };

        if (!check_key(map, playerName) || score < map[playerName]) {
            map[playerName] = score;

            std::ofstream file{ SCORES_FILE_NAME };
            for (const auto& [playerName, score] : map) {
                file << playerName << " " << score << "\n";
            }
            file.close();
        }
    }



}
