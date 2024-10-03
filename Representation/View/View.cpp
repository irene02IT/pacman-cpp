#include "View.h"

View::View(std::shared_ptr<EntityModel> model)
        : v_model(std::move(model)){}

void View::updateView(){
    reinitializeSprite();// reinitialize the sprite to avoid the previous sprite to be drawn
    SpriteSetup(); // setup the sprite with the correct texture (the only function that is different for each entity)
    Draw(); // draw the sprite
}

// call the draw function of the window
void View::Draw(){
    Window::getInstance().GetRenderWindow()->draw(sprite);
}

void View::reinitializeSprite() {
    sprite = sf::Sprite();
}
