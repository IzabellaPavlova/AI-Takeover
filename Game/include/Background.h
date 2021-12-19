#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

enum RelativePosition
{
    LEFT_HALF,
    RIGHT_HALF,
    OUTSIDE,
    START
};

constexpr int NUM_BACKGROUNDS = 2;
constexpr int DOTS_PER_QUAD = 4;

class Background : public sf::Drawable, public sf::Transformable
{
public:
    Background(const std::string &);
    ~Background();
    Background(const Background &) = delete;
    Background(Background &&) noexcept = delete;
    Background &operator=(const Background &) = delete;
    Background &operator=(Background &&) noexcept = delete;

    void update(const sf::View &) noexcept;

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const noexcept;
    void loadTexture(const std::string &) noexcept;
    RelativePosition findPosition(const sf::View &) const noexcept;

    sf::Texture m_texture;
    std::array<sf::Vertex, NUM_BACKGROUNDS * DOTS_PER_QUAD> m_vertices;
    RelativePosition m_previousPosition;
};