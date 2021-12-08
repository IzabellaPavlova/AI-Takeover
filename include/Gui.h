#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Button.h"

class Gui : public sf::Drawable, public sf::Transformable
{
public:
    Gui(const sf::RenderWindow &w) : m_window(w)
    {
        if (!m_font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Failed to load font from file 'arial.ttf'\n";
        }

        if (!m_texture.loadFromFile("ButtonTexture.png"))
        {
            std::cerr << "Failed to load texture from file 'ButtonTexture.png'\n";
        }
    }

    ~Gui()
    {
    }

    void addButton(const std::string &str, const unsigned int charSize = 30U)
    {
        m_buttons.push_back(Button(str, m_font, m_texture, charSize));
        auto widestButtonIt = std::max_element(m_buttons.begin(),
                                               m_buttons.end(),
                                               [](const Button &lhs, const Button &rhs) -> bool
                                               {
                                                   return lhs.getSize().x < rhs.getSize().x;
                                               });
        float width = widestButtonIt->getSize().x;
        for (Button &btn : m_buttons)
            btn.setWidth(width);
        updatePositions();
    }

    void updatePositions()
    {
        size_t n = m_buttons.size();
        if (n == 0)
            return;

        float bWidth = m_buttons[0].getSize().x;
        float bHeight = m_buttons[0].getSize().y;
        float x_pos = (m_window.getSize().x - bWidth) / 2;
        float h = (m_window.getSize().y - n * bHeight - (n - 1) * m_spacing) / 2;

        for (size_t i = 0; i < n; ++i)
            m_buttons[i].setPosition(sf::Vector2f(x_pos, h + i * (bHeight + m_spacing)),
                                     m_window.getSize().x);
    }

    int getPressedButton()
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        for (int i = 0; i < m_buttons.size(); ++i)
            if (m_buttons[i].isPressed(m_window.mapPixelToCoords(mousePos)))
                return i;

        return -1;
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (const Button &btn : m_buttons)
            target.draw(btn);
    }

    std::vector<Button> m_buttons;
    sf::Font m_font;
    sf::Texture m_texture;
    const sf::RenderWindow &m_window;
    const float m_spacing = 50.f;
};