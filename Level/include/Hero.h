#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Map.h"

enum class State
{
    PLAYING,
    DIED,
    FINISHED
};

class Hero : public sf::Drawable, public sf::Transformable
{
    float m_y_koef = 1.5f;

public:
    Hero(const float, const float, const float);

    Hero(const Hero &) = delete;

    Hero(Hero &&) noexcept = delete;

    Hero &operator=(const Hero &) = delete;

    Hero &operator=(Hero &&) noexcept = delete;

    ~Hero();

    sf::Vector2f getPosition();

    void setInitialPosition(sf::Vector2f);

    void setMap(Map *);

    void keyReleased(sf::Keyboard::Key);

    void handleInput();

    void update(sf::Time dt);

    bool isFinished();

    bool isDead();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void changeDirection(sf::Time);

    void move(sf::Vector2f);

    void move_x(float);

    void move_y(float);

    bool isReachFinish();

    sf::Vector2f m_vel;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Vector2f m_texture_size;

    const float m_tileSize, m_hero_vel, m_acceleration, m_halfTileSize;

    float m_changes;
    bool m_is_jump;
    State m_state;

    int m_idx_platform;

    Map *m_map;
    sf::Vector2f m_window_size;
};
