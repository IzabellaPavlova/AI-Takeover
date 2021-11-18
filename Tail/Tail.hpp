#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<float> vector2f;

class Tile{
public:
    Tile() = delete;
    Tile(const sf::Texture& texture);
    ~Tile();
    vector2f getPosition();
    void draw(sf::RenderWindow* window);
private:
    sf::Sprite tile;
    bool isEmpty();
};