#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Button.h"
#include "SceneType.h"
#include <vector>

class PauseScene : public Scene
{
public:
    PauseScene(sf::RenderWindow &);
    ~PauseScene();
    PauseScene(const PauseScene &) = delete;
    PauseScene(PauseScene &&) noexcept = delete;
    PauseScene &operator=(const PauseScene &) = delete;
    PauseScene &operator=(PauseScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);
    std::vector<Button> &getButtons();
    void draw() const;

private:
    void createButtons();

    sf::RenderWindow &m_window;
    std::vector<Button> m_buttons;
};