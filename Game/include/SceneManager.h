#pragma once
#include <array>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "SceneType.h"
#include "Constants.h"
#include "SceneSwitcher.h"

class SceneManager : public SceneSwitcher
{
public:
    SceneManager(sf::RenderWindow &, const Constants &, const std::string &file_prefix = "");
    ~SceneManager();
    SceneManager(const SceneManager &) = delete;
    SceneManager(SceneManager &&) noexcept = delete;
    SceneManager &operator=(const SceneManager &) = delete;
    SceneManager &operator=(SceneManager &&) noexcept = delete;

    bool cycle(const sf::Time) noexcept;
    void draw() const noexcept;
    void setLevel(const size_t) noexcept;
    void switchTo(const SceneType) noexcept;
    bool successfullyInitialized() const noexcept;

private:
    void changeScene() noexcept;
    void handleEvents() noexcept;

    std::array<std::unique_ptr<Scene>, 4> m_scenes;
    sf::RenderWindow &m_window;
    Constants m_constants;
    SceneType m_curScene, m_sceneToSwitch;
    size_t m_numOfLevel;
    bool m_initializationSuccess;
    const std::string m_filePrefix;
};