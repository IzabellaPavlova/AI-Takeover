#include "Background.h"
#include <iostream>

Background::Background(const std::string &f_name) : m_previousPosition(RelativePosition::START)
{
    loadTexture(f_name);
}

Background::~Background()
{
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
}

void Background::update(const sf::View &windowView)
{
    RelativePosition curPos = findPosition(windowView);
    if (curPos == m_previousPosition)
    {
        if (curPos != RelativePosition::OUTSIDE)
            return;
    }

    if (curPos == RelativePosition::OUTSIDE)
    {
        std::swap(m_vertices[0], m_vertices[4]);
        std::swap(m_vertices[1], m_vertices[5]);
        std::swap(m_vertices[2], m_vertices[6]);
        std::swap(m_vertices[3], m_vertices[7]);
    }
    else
    {
        float del_x = m_texture.getSize().x;
        if (curPos == RelativePosition::LEFT_HALF)
            del_x *= -1;
        for (int i = 4; i < 8; ++i)
            m_vertices[i].position = m_vertices[i - 4].position + sf::Vector2f(del_x, 0.f);
    }
    m_previousPosition = curPos;
}

void Background::loadTexture(const std::string &f_name)
{
    if (!m_texture.loadFromFile(f_name))
    {
        std::cout << "Failed to load background texture from file '" << f_name << "'\n";
    }

    float texture_size_x = (float)m_texture.getSize().x;
    float texture_size_y = (float)m_texture.getSize().y;

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(texture_size_x, 0.f);
    m_vertices[2].position = sf::Vector2f(texture_size_x, texture_size_y);
    m_vertices[3].position = sf::Vector2f(0.f, texture_size_y);

    for (int i = 0; i < 4; ++i)
        m_vertices[i].texCoords = m_vertices[i].position;

    for (int i = 4; i < 8; ++i)
    {
        m_vertices[i].position = m_vertices[i - 4].position - sf::Vector2f(texture_size_x, 0.f);
        m_vertices[i].texCoords = m_vertices[i - 4].texCoords;
    }
}

RelativePosition Background::findPosition(const sf::View &windowView)
{
    float camera_pos = windowView.getCenter().x;
    if (camera_pos < m_vertices[0].position.x || camera_pos > m_vertices[1].position.x)
        return RelativePosition::OUTSIDE;
    else if (camera_pos < m_vertices[0].position.x + m_texture.getSize().x / 2)
        return RelativePosition::LEFT_HALF;
    else
        return RelativePosition::RIGHT_HALF;
}