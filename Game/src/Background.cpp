#include "Background.h"
#include <iostream>

Background::Background(const std::string &f_name) : m_previousPosition(RelativePosition::START)
{
    loadTexture(f_name);
}

Background::~Background()
{
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const noexcept
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
}

void Background::update(const sf::View &windowView) noexcept
{
    RelativePosition curPos = findPosition(windowView);
    if (curPos == m_previousPosition)
    {
        if (curPos != RelativePosition::OUTSIDE)
            return;
    }

    if (curPos == RelativePosition::OUTSIDE)
    {
        for (int i = 0; i < DOTS_PER_QUAD; ++i)
            std::swap(m_vertices[i], m_vertices[i + DOTS_PER_QUAD]);
    }
    else
    {
        float del_x = m_texture.getSize().x;
        if (curPos == RelativePosition::LEFT_HALF)
            del_x *= -1;
        for (int i = DOTS_PER_QUAD; i < DOTS_PER_QUAD * NUM_BACKGROUNDS; ++i)
            m_vertices[i].position = m_vertices[i - DOTS_PER_QUAD].position + sf::Vector2f(del_x, 0.f);
    }
    m_previousPosition = curPos;
}

void Background::loadTexture(const std::string &f_name) noexcept
{
    if (!m_texture.loadFromFile(f_name))
        std::cerr << "Failed to load background texture from file '" << f_name << "'\n";

    float texture_size_x = (float)m_texture.getSize().x;
    float texture_size_y = (float)m_texture.getSize().y;

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(texture_size_x, 0.f);
    m_vertices[2].position = sf::Vector2f(texture_size_x, texture_size_y);
    m_vertices[3].position = sf::Vector2f(0.f, texture_size_y);

    for (int i = 0; i < DOTS_PER_QUAD; ++i)
        m_vertices[i].texCoords = m_vertices[i].position;

    for (int i = DOTS_PER_QUAD; i < DOTS_PER_QUAD * NUM_BACKGROUNDS; ++i)
    {
        m_vertices[i].position = m_vertices[i - DOTS_PER_QUAD].position - sf::Vector2f(texture_size_x, 0.f);
        m_vertices[i].texCoords = m_vertices[i - DOTS_PER_QUAD].texCoords;
    }
}

RelativePosition Background::findPosition(const sf::View &windowView) const noexcept
{
    float camera_pos = windowView.getCenter().x;
    if (camera_pos < m_vertices[0].position.x || camera_pos > m_vertices[1].position.x)
        return RelativePosition::OUTSIDE;
    else if (camera_pos < m_vertices[0].position.x + m_texture.getSize().x / 2)
        return RelativePosition::LEFT_HALF;
    else
        return RelativePosition::RIGHT_HALF;
}