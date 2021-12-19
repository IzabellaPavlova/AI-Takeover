#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map(const float, const float);

    Map(const Map &) = delete;

    Map(Map &&) noexcept = delete;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&) noexcept = delete;

    ~Map();

    void setScore(const int score);

    void setGameTime(const float time);

    void readMap(const size_t);

    void readLevelFile(const std::string &);

    void readTile(int, int, char);

    void addTile(int, int, int);

    void addPlatform(int, int);

    void addCoin(int, int);

    void update(sf::Time);

    sf::Vector2i getSize();

    std::vector<sf::Vertex> &getVertexArray();

    bool isCoin(int) ;

    bool isCoinReach(int );

    void coinDel(int);

    int getScore() const;

    float getGameTime() const;

    bool isPlatformMoving(int);

    float getPlatformVel(int);

    sf::Vector2f getHeroPosition();

    sf::Vector2f getFinishPosition();

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

    std::map<int,bool> m_coins_idx;

    sf::Vector2f m_finish_pos;
    sf::Vector2f m_hero_pos;

    sf::Texture m_texture;

    int m_score;
    float m_game_time;

    int m_best_score;
    float m_best_game_time;

    sf::Font m_font;
};