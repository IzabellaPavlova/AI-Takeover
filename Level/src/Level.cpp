#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>

Level::Level(sf::RenderWindow &w,
             const size_t num_of_level,
             const float tile_size,
             const float v_platform,
             const float v_hero,
             const float a_hero) : m_window(w),
                                   m_map(tile_size,
                                         v_platform),
                                   m_hero(tile_size,
                                          v_hero,
                                          a_hero),
                                   m_finish(tile_size),
                                   m_camera(w, m_hero)
{
    readLevelFile(num_of_level);
    m_camera.setMaxSize(m_map.getSize().x * tile_size);
}

Level::~Level()
{
}

void Level::handleEvents(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::Right ||
            event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::Down)
            m_hero.keyReleased(event.key.code);
        break;

    default:
        break;
    }
}

void Level::handleInput()
{
    m_hero.handleInput();
}

void Level::update(sf::Time dt)
{
    m_map.update(dt);
    m_hero.update(dt);
    m_camera.update();
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_map);
    target.draw(m_finish);
    target.draw(m_hero);
}

void Level::readLevelFile(const size_t num_of_level)
{
    m_map.readMap(num_of_level);

    m_hero.setMap(&m_map);
    m_hero.setInitialPosition(m_map.getHeroPosition());

    m_finish.setPosition(m_map.getFinishPosition());
}

Map &Level::getMap()
{
    return m_map;
}

Hero &Level::getHero()
{
    return m_hero;
}

Finish &Level::getFinish()
{
    return m_finish;
}

bool Level::isFinished()
{
    return m_hero.isFinished();
}

bool Level::isDead()
{
    return m_hero.isDead();
}