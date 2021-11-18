#pragma once

#include <iostream>
#include"/home/pavlova_izabella/AI-Takeover/Tail/Tail.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

typedef sf::Vector2<float> vector2f;

class Map{
public:
    Map() = delete;
    Map(int numTilesX, int numTilesY);
    ~Map();
    void getTile(int x, int y);
    void setTile(int x, int y, char type);
private:
    std::vector<std::vector<Tile>>  tiles;
    std::vector<sf::Texture> textures;
    float tileSize;
};