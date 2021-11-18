#include"Button.hpp"

typedef sf::Vector2<float> vector2f;

bool Button::isActive() {
    return true;
}

Button::Button(std::vector<std::string> num, sf::RenderWindow* window){}

Button::~Button() {}

bool Button::getIsActive() {
    return true;
}

void Button::setActive() {
    return;
}

void Button::setPassive() {
    return;
}

vector2f Button::getPosition() {
    return vector2f (16.5f, 24.f);
}

vector2f Button::getSize() {
    return vector2f (16.5f, 24.f);
}

void draw(sf::RenderWindow* window) {
    return;
}