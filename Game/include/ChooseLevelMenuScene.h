#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Background.h"
#include "Gui.h"

class ChooseLevelMenuScene : public Scene
{
public:
    ChooseLevelMenuScene(sf::RenderWindow &, SceneManager &);
    ~ChooseLevelMenuScene();
    ChooseLevelMenuScene(const ChooseLevelMenuScene &) = delete;
    ChooseLevelMenuScene(ChooseLevelMenuScene &&) noexcept = delete;
    ChooseLevelMenuScene &operator=(const ChooseLevelMenuScene &) = delete;
    ChooseLevelMenuScene &operator=(ChooseLevelMenuScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);
    void draw() const;

private:
    void createButtons();

    sf::RenderWindow &m_window;
    SceneManager &m_sceneManager;
    Background m_background;
    Gui m_gui;
};