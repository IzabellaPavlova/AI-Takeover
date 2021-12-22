#pragma once
#include "Map.h"
#include "Hero.h"
#include "Finish.h"
#include "Camera.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/lexical_cast.hpp>

class Level : public sf::Drawable, public sf::Transformable
{
public:
    Level(sf::RenderWindow &w,
          const size_t num_of_level,
          const float tile_size,
          const float v_platform,
          const float v_hero,
          const float a_hero);

    Level(const Level &) = delete;

    Level(Level &&) noexcept = delete;

    Level &operator=(const Level &) = delete;

    Level &operator=(Level &&) noexcept = delete;

    ~Level();

    void handleEvents(const sf::Event &event);

    void handleInput();

    void update(sf::Time);

    bool isFinished() const;

    bool isDead() const;

    Map &getMap();
    Hero &getHero();
    Finish &getFinish();

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
    void readLevelFile(const size_t);
    void readScoreFile(const size_t num_of_level);

    void changeScore();

    int m_best_score;
    float m_best_game_time;

    sf::RenderWindow &m_window;
    Map m_map;
    Hero m_hero;
    Finish m_finish;
    Camera<Hero> m_camera;

    size_t m_level_num;
};