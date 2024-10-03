#include "Score.h"

Score::Score() :currentScore(0),pacman_lives(3){
    std::cout<<"creating score"<<std::endl;
    loadScoresFromFile();
};
Score::~Score() {
    std::cout<<"destroying score"<<std::endl;
}
// the function to update the view of the score
void Score::notify(const std::string &message) {
    if(message == "update view"){
        // search observer of score
        for (const auto& observer : observers) {
            if(observer->isScoreObserver())
                observer->updateView();
        }
    }
}

void Score::loadScoresFromFile() {
    const std::string& filename = "../" + TOP_SCORES_PATH;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        int i = 0;
        while (std::getline(file, line) && i < 5) {
            if (!line.empty()) {
                topScores[i] = line;
            } else {
                topScores[i] = "0"; // Initialize with default value if line is empty
            }
            i++;
        }
        // Initialize remaining scores with default values if file has less than 5 scores
        for (; i < 5; i++) {
            topScores[i] = "0";
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
        // Initialize all scores with default values if file cannot be opened
        for (auto & topScore : topScores) {
            topScore = "0";
        }
    }
}

// the function checks if the current score is higher than the top scores.
// If it is, it updates the top scores and the file with the new top scores.
// It is called when the game is over (GameoverState and VictoryState).
void Score::checkNewRecord() {
    for (int i = 0; i < 5; i++) {
        int topscoreint = 0;
        try {
            topscoreint = std::stoi(topScores[i]); // conversion from string to int with stoi
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid argument: " << e.what() << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cout << "Out of range: " << e.what() << std::endl;
            continue;
        }

        if (currentScore > topscoreint) {
            // Shift the lower scores down
            for (int j = 4; j > i; j--) {
                topScores[j] = topScores[j - 1];
            }
            // Insert the new high score
            topScores[i] = std::to_string(currentScore);
            updateFile();
            break;
        }
    }
}

void Score::updateFile() {
    const std::string& filename = "../" + TOP_SCORES_PATH;
    std::ofstream file(filename, std::ofstream::trunc); // Open the file in write mode with truncation

    if (file.is_open()) {
        for (const auto& topScore : topScores) {
            file << topScore << std::endl; // Write each score on a new line
        }
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

const std::string *Score::getTopScores() const {
    return topScores;
}

int Score::get_pacman_lives() const {
    return pacman_lives;
}

void Score::decrease_pacman_lives() {
    pacman_lives--;
}

void Score::setScore(int x) {
    currentScore = x;
}

void Score::increaseLevel() {
    level_reached++;
}

int Score::getLevelReached() const {
    return level_reached;
}

void Score::add(int x) {
    currentScore+=x;
}

int Score::getCurrentScore() const {
    return currentScore;
}






