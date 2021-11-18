#include"Tail.hpp"

typedef sf::Vector2<float> vector2f;

bool Tile::isEmpty() {
    return true;
}

Tile::Tile(const sf::Texture& texture) {}

Tile::~Tile() {}

vector2f Tile::getPosition() {
    return vector2f (16.5f, 24.f);
}

void Tile::draw(sf::RenderWindow* window) {
    return;
}