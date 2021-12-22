#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow &w,
                             const size_t num_of_level,
                             Constants &constants,
                             SceneSwitcher &scn_switcher,
                             const std::string &file_prefix,
                             const std::string &background_name) : m_window(w),
                                                                   m_level(w,
                                                                           num_of_level,
                                                                           constants.at("TILE_SIZE"),
                                                                           constants.at("PLATFORM_VELOCITY"),
                                                                           constants.at("HERO_VELOCITY"),
                                                                           constants.at("HERO_ACCELERATION")),
                                                                   m_background(file_prefix + background_name + std::to_string(num_of_level) + ".png"),
                                                                   m_sceneSwitcher(scn_switcher),
                                                                   m_view(m_window.getView())

{
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::handleEvents(const sf::Event &event) noexcept
{
    m_level.handleEvents(event);
}

void GameplayScene::handleInput() noexcept
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        m_view = m_window.getView();
        m_sceneSwitcher.switchTo(SceneType::PAUSE);
    }
    m_level.handleInput();
}

void GameplayScene::update(const sf::Time dt) noexcept
{
    m_background.update(m_window.getView());
    m_level.update(dt);
    checkLevel();
}

void GameplayScene::draw() const noexcept
{
    m_window.draw(m_background);
    m_window.draw(m_level);
}

void GameplayScene::checkLevel() const noexcept
{
    if (m_level.isFinished())
        m_sceneSwitcher.switchTo(SceneType::MAIN_MENU);
    else if (m_level.isDead())
        m_sceneSwitcher.switchTo(SceneType::MAIN_MENU);
}

void GameplayScene::resetView() const noexcept
{
    m_window.setView(m_view);
}