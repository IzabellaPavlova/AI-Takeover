#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow &w,
                             const size_t num_of_level,
                             Constants &constants) : m_window(w),
                                                     m_level(w,
                                                             num_of_level,
                                                             constants.at("TILE_SIZE"),
                                                             constants.at("PLATFORM_VELOCITY"),
                                                             constants.at("HERO_VELOCITY"),
                                                             constants.at("HERO_ACCELERATION")),
                                                     m_background("../Files/Background_" + std::to_string(num_of_level) + ".png")

{
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::handleEvents(const sf::Event &event)
{
    m_level.handleEvents(event);
}

SceneType GameplayScene::handleInput()
{
    m_level.handleInput();

    if (m_level.isFinished())
        return SceneType::MAIN_MENU;
    else if (m_level.isDead())
        return SceneType::MAIN_MENU;
    return SceneType::GAMEPLAY;
}

SceneType GameplayScene::update(sf::Time dt)
{
    m_background.update(m_window.getView());
    m_level.update(dt);
    if (m_level.isFinished())
        return SceneType::MAIN_MENU;
    else if (m_level.isDead())
        return SceneType::MAIN_MENU;
    return SceneType::GAMEPLAY;
}

void GameplayScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_level);
}