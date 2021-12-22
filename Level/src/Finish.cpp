#include "Finish.h"

Finish::Finish(const float tile_size) : m_tileSize(tile_size)
{
    if (tile_size <= 0)
        throw (std::invalid_argument("Failed const TILE_SIZE"));

    if (!m_texture.loadFromFile("../Files/finish.png"))
    {
        std::cout << "Failed to read file finish.png\n";
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(m_tileSize / m_texture.getSize().x, m_tileSize / m_texture.getSize().y);

}

Finish::~Finish() {}

void Finish::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

vector2f Finish::getPosition()
{
    return m_sprite.getPosition();
}

void Finish::update(sf::Time dt) {}