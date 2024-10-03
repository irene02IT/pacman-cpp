#ifndef INC_2023_PROJECT_IRENE02IT_SCORE_H
#define INC_2023_PROJECT_IRENE02IT_SCORE_H


#include <fstream>
#include "../Observer/Subject.h"

// Score class is responsible for keeping track of the current score, pacman lives, top scores and level reached.
// It is also responsible for updating the file with the top scores.
// It is a subject class and it has its view. So it act like the other entities notifying the observers
// when the score changes (in this case, the ScoreView).
class Score: public Subject{
private:
    int currentScore;
    int pacman_lives;
    std::string topScores[5]; // memory for the 5 top scores
    int level_reached=1; // level reached by the player in the game
public:
    Score();
    virtual ~Score();
    void add(int x);
    [[nodiscard]] int getCurrentScore() const;
    [[nodiscard]] const std::string *getTopScores() const;
    [[nodiscard]] int getLevelReached() const;
    [[nodiscard]] int get_pacman_lives() const;
    void decrease_pacman_lives();
    void setScore(int x);
    void notify(const std::string& message);
    void loadScoresFromFile();
    void checkNewRecord();
    void updateFile();
    void increaseLevel();
};


#endif //INC_2023_PROJECT_IRENE02IT_SCORE_H
