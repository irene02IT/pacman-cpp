#ifndef INC_2023_PROJECT_IRENE02IT_SCOREVIEW_H
#define INC_2023_PROJECT_IRENE02IT_SCOREVIEW_H


#include <memory>
#include <utility>
#include <array>
#include "../../Logic/Observer/Observer.h"
#include "../../Logic/Score/Score.h"
#include "../Window/Window.h"

class ScoreView : public Observer{
protected:
    std::shared_ptr<Score> s_score;
    sf::RectangleShape s_rectShape{};
    sf::Font m_font;
    std::array<sf::Text, 4> scoreBoard;
public:
    explicit ScoreView(std::shared_ptr<Score>score);
    bool isScoreObserver() const override;
    void updateView() override;
    void ViewSetup();
    void Draw();
};


#endif //INC_2023_PROJECT_IRENE02IT_SCOREVIEW_H
