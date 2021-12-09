#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
    Constants constants;
    if (!constants.read_file("../Files/.config"))
    {
        std::cerr << "Failed to read constants file\n";
        return;
    }

    sf::RenderWindow window;
    try
    {
        window.create(sf::VideoMode(constants.at("SCREEN_INITIAL_WIDTH"),
                                    constants.at("SCREEN_INITIAL_HEIGHT")),
                      "AI_Takeover",
                      sf::Style::Default);
    }
    catch (const std::out_of_range &)
    {
        std::cerr << "SCREEN_INITIAL_WIDTH or SCREEN_INITIAL_HEIGHT not found if constants\n";
        return;
    }
    SceneManager sceneManager(window, constants);
    startGameLoop(window, sceneManager);
}

void Game::startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager)
{
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.0f / 60.0f);
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::sleep(frameTime - dt);
        
        sceneManager.cycle(dt);

        window.clear(sf::Color::Black);
        sceneManager.draw();
        window.display();
    }
}