#pragma once
#include <array>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "SceneType.h"
#include "Constants.h"

class SceneManager
{
public:
    SceneManager(sf::RenderWindow &, const Constants &);
    ~SceneManager();
    SceneManager(const SceneManager &) = delete;
    SceneManager(SceneManager &&) noexcept = delete;
    SceneManager &operator=(const SceneManager &) = delete;
    SceneManager &operator=(SceneManager &&) noexcept = delete;

    void cycle(sf::Time);
    void draw() const;
    void setLevel(const size_t);

private:
    void switchTo(SceneType scene_to_switch);
    void handleEvents();

    std::array<std::unique_ptr<Scene>, 4> m_scenes;
    sf::RenderWindow &m_window;
    Constants m_constants;
    SceneType m_curScene;
    size_t m_numOfLevel;
};