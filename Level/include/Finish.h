#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

typedef sf::Vector2<float> vector2f;

class Finish : public sf::Drawable, public sf::Transformable
{
public:
    Finish(const float);

    Finish(const Finish &) = delete;

    Finish(Finish &&) noexcept = delete;

    Finish &operator=(const Finish &) = delete;

    Finish &operator=(Finish &&) noexcept = delete;

    ~Finish();

    void setPosition(vector2f pos);

    sf::Vector2f getPosition();

    void update(sf::Time);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite);
    }

    const float m_tileSize;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};