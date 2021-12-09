#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow &w,
                                           SceneManager &sm) : m_window(w),
                                                               m_sceneManager(sm),
                                                               m_background("../Files/MainMenuBackground.png"),
                                                               m_gui(w)
{
    m_gui.addButton("Level 1");
    m_gui.addButton("Level 2");
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
}

void ChooseLevelMenuScene::handleEvents(const sf::Event &event)
{
}

SceneType ChooseLevelMenuScene::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        switch (m_gui.getPressedButton())
        {
        case 0:
        {
            m_sceneManager.setLevel(1);
            return SceneType::GAMEPLAY;
            break;
        }

        case 1:
        {
            m_sceneManager.setLevel(2);
            return SceneType::GAMEPLAY;
            break;
        }

        default:
            break;
        }
    }
    return SceneType::CHOOSE_LEVEL_MENU;
}

SceneType ChooseLevelMenuScene::update(sf::Time dt)
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

void ChooseLevelMenuScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}