#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<float> vector2f;

class Button{
public:
    Button() = delete;
    Button(std::vector<std::string> num, sf::RenderWindow* window);
    ~Button();
    bool getIsActive();
    void setActive();
    void setPassive();
    vector2f getPosition();
    vector2f getSize();
    void draw(sf::RenderWindow* window);
private:
    bool isActive();
    std::vector<std::string> num;
    sf::Text text;
    sf::Font font;
    sf::Sprite button;
};