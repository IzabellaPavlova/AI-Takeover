#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game(const std::string &file_prefix /* = "" */,
           const std::string &config_file_name /* = ".config" */) : frameTime(sf::seconds(1.f / 60.f)),
                                                                    m_filePrefix(file_prefix),
                                                                    m_configFileName(config_file_name)
{
}

Game::~Game()
{
}

void Game::run() const noexcept
{
    Constants constants;
    if (!constants.read_file(m_filePrefix + m_configFileName))
    {
        std::cerr << "Failed to read constants file '" << m_filePrefix + m_configFileName << "'\n";
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
        return;
    }

    SceneManager sceneManager(window, constants, m_filePrefix);
    if (sceneManager.successfullyInitialized())
        startGameLoop(window, sceneManager);
}

void Game::startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager) const noexcept
{
    sf::Clock clock;
    while (window.isOpen() &&
           loop(window, sceneManager, clock.restart()))
    {
    }
}

bool Game::loop(sf::RenderWindow &window, SceneManager &sceneManager, const sf::Time dt) const noexcept
{
    // true if success
    // false if error

    sf::sleep(frameTime - dt);

    window.clear(sf::Color::Black);
    sceneManager.draw();
    window.display();

    return sceneManager.cycle(dt);
}