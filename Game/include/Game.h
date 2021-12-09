#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Game
{
public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game(Game &&) noexcept = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) noexcept = delete;

    void run();

private:
    void startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager);
};