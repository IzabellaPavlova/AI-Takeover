#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(const std::string &str,
           const sf::Font &font,
           const sf::Texture &texture,
           const unsigned int characterSize = 30U);

    ~Button();

    sf::Vector2f getSize() const;
    void setPosition(const sf::Vector2f &pos, const float windowWidth);
    void setWidth(const float width);
    bool isPressed(sf::Vector2f mousePos) const;

private:
    sf::Vector2f getTextSize() const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Sprite m_sprite;
    sf::Text m_text;
};