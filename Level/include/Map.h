#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <fstream>

typedef sf::Vector2<float> vector2f;

class Map : public sf::Drawable, public sf::Transformable
{
public:
    Map(const float, const float);

    Map(const Map &) = delete;

    Map(Map &&) noexcept = delete;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&) noexcept = delete;

    ~Map(){};

    void readMap(const size_t);

    void readLevelFile(const std::string &);

    void readTile(int, int, char);

    void addTile(int, int, int);

    void addPlatform(int, int);

    void update(sf::Time);

    sf::Vector2i getSize();

    std::vector<sf::Vertex> &getVertexArray();

    bool isPlatformMoving(int);

    vector2f getPlatformPosition(int);

    float getPlatformVel(int);

    vector2f getHeroPosition();

    vector2f getFinishPosition();

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

    sf::Vector2i m_map_size;
    std::vector<sf::Vertex> m_vertices;

    const float m_tileSize, m_platform_vel;
    std::vector<float> m_platform_vel_arr;
    std::vector<std::pair<float, float>> m_borders;
    bool m_right_border;

    int m_platform_count;
    std::vector<int> m_platform_idx;

    vector2f m_finish_pos;
    vector2f m_hero_pos;

    sf::Texture m_texture;
};