#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Button.h"

class Gui : public sf::Drawable, public sf::Transformable
{
public:
    Gui(const sf::RenderWindow &w);

    ~Gui();

    void addButton(const std::string &str, const unsigned int charSize = 30U);

    void updatePositions();

    int getPressedButton();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::vector<Button> m_buttons;
    sf::Font m_font;
    sf::Texture m_texture;
    const sf::RenderWindow &m_window;
    const float m_spacing = 50.f;
};