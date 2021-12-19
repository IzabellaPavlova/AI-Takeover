#pragma once
#include "Scene.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <string>
#include "Constants.h"
#include "Background.h"
#include "SceneSwitcher.h"

class GameplayScene : public Scene
{
public:
    GameplayScene(sf::RenderWindow &,
                  const size_t,
                  Constants &,
                  SceneSwitcher &,
                  const std::string &file_prefix = "",
                  const std::string &background_name = "Background_");
    ~GameplayScene();
    GameplayScene(const GameplayScene &) = delete;
    GameplayScene(GameplayScene &&) noexcept = delete;
    GameplayScene &operator=(const GameplayScene &) = delete;
    GameplayScene &operator=(GameplayScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event) noexcept;
    void handleInput() noexcept;
    void update(const sf::Time) noexcept;
    void draw() const noexcept;
    void resetView() const noexcept;

private:
    void checkLevel() const noexcept;

    sf::RenderWindow &m_window;
    Level m_level;
    Background m_background;
    SceneSwitcher &m_sceneSwitcher;
    sf::View m_view;
};