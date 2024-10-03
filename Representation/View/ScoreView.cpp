#include "ScoreView.h"


void ScoreView::updateView() {
    ViewSetup();
    // override the updateView method from View class because there's no sprite to set up
    Draw();
}

void ScoreView::ViewSetup() {
    m_font.loadFromFile("../" + FONT_PATH);
    for(auto & i : scoreBoard){
        i.setFont(m_font);
        i.setFillColor(sf::Color::White);
        i.setCharacterSize(FONT_SIZE_H2);
    }
    scoreBoard[0].setString(sf::String("Score:"));
    std::string scoreString = std::to_string(s_score->getCurrentScore());
    scoreBoard[1].setString(scoreString);
    std::string livesString = std::to_string(s_score->get_pacman_lives());
    scoreBoard[2].setString(sf::String("#Lives: ")+livesString);

    scoreBoard[0].setPosition(30*SCALE_FACTOR,WINDOW_HEIGHT-130*SCALE_FACTOR);
    scoreBoard[1].setPosition(250*SCALE_FACTOR, WINDOW_HEIGHT-130*SCALE_FACTOR);
    scoreBoard[2].setPosition(500*SCALE_FACTOR,WINDOW_HEIGHT-130*SCALE_FACTOR);
}

void ScoreView::Draw() {
    for(auto & i : scoreBoard){
        Window::getInstance().GetRenderWindow()->draw(i);
    }
}

ScoreView::ScoreView(std::shared_ptr<Score> score) : s_score(std::move(score)){}

bool ScoreView::isScoreObserver() const {
    return true;
}
