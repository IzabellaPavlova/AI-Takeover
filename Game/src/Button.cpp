#include "Button.h"

Button::Button(const std::string &str,
               const sf::Font &font,
               const sf::Texture &texture,
               const unsigned int characterSize /* = 30U */) : m_sprite(texture),
                                                               m_text(str, font, characterSize)
{
    m_sprite.setScale(2 * m_text.getLocalBounds().width / texture.getSize().x,
                      2 * (float)characterSize / texture.getSize().y);
}

Button::~Button()
{
}

sf::Vector2f Button::getSize() const
{
    return sf::Vector2f(m_sprite.getGlobalBounds().width,
                        m_sprite.getGlobalBounds().height);
}

void Button::setPosition(const sf::Vector2f &pos, const float windowWidth)
{
    m_sprite.setPosition(pos);
    m_text.setPosition((windowWidth - m_text.getGlobalBounds().width) / 2, pos.y + m_text.getGlobalBounds().height / 2);
}

void Button::setWidth(const float width)
{
    m_sprite.scale(width / m_sprite.getGlobalBounds().width, 1.f);
}

bool Button::isPressed(sf::Vector2f mousePos) const
{
    return m_sprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

sf::Vector2f Button::getTextSize() const
{
    return sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
    target.draw(m_text);
}