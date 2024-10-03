#ifndef INC_2023_PROJECT_IRENE02IT_COINVIEW_H
#define INC_2023_PROJECT_IRENE02IT_COINVIEW_H

#include "../../Logic/Entities/Collectables/Coin.h"
#include "View.h"
class CoinView : public View {
public:
  explicit CoinView(const std::shared_ptr<class Coin>& model)
      : View(model) {}
  void SpriteSetup() override;
};

#endif // INC_2023_PROJECT_IRENE02IT_COINVIEW_H
