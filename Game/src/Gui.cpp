#include "Gui.h"

Gui::Gui(const sf::RenderWindow &w, const std::string &font_file_name, const std::string &texture_file_name) : m_window(w)
{
    if (!m_font.loadFromFile(font_file_name))
        throw std::invalid_argument("Failed to load font from file '" + font_file_name + "'\n");

    if (!m_texture.loadFromFile(texture_file_name))
        throw std::invalid_argument("Failed to load texture from file '" + texture_file_name + "'\n");
}

Gui::~Gui() {}

void Gui::addButton(const std::string &str, const unsigned int charSize /* = 30U */) noexcept
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

void Gui::updatePositions() noexcept
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

int Gui::getPressedButton() const noexcept
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    for (size_t i = 0; i < m_buttons.size(); ++i)
        if (m_buttons[i].isPressed(m_window.mapPixelToCoords(mousePos)))
            return i;

    return -1;
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const noexcept
{
    for (const Button &btn : m_buttons)
        target.draw(btn);
}