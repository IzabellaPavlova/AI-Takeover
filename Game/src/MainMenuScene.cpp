#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(sf::RenderWindow &w) : m_window(w),
                                                    m_background("../Files/MainMenuBackground.png"),
                                                    m_gui(w)
{
    sf::View view = m_window.getView();
    view.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
    m_window.setView(view);
    m_gui.addButton("Play");
    m_gui.addButton("Exit");
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::handleEvents(const sf::Event &event)
{
}

SceneType MainMenuScene::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        switch (m_gui.getPressedButton())
        {
        case 0:
            return SceneType::CHOOSE_LEVEL_MENU;
            break;

        case 1:
        {
            m_window.close();
            return SceneType::GAMEPLAY;
            break;
        }

        default:
            break;
        }
    }
    return SceneType::MAIN_MENU;
}

SceneType MainMenuScene::update(sf::Time dt)
{
    return SceneType::MAIN_MENU;
}

void MainMenuScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}