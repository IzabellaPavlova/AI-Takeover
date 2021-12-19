#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow &w,
                                           SceneManager &sm,
                                           const std::string &file_prefix,
                                           const std::string &background_file_name,
                                           const std::string &font_file_name,
                                           const std::string &button_file_name) : m_window(w),
                                                                                  m_sceneManager(sm),
                                                                                  m_background(file_prefix + background_file_name),
                                                                                  m_gui(w, file_prefix + font_file_name, file_prefix + button_file_name)
{
    m_gui.addButton("Level 1");
    m_gui.addButton("Level 2");
    m_gui.addButton("Back to Main Menu");
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
}

void ChooseLevelMenuScene::handleEvents(const sf::Event &event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            switch (m_gui.getPressedButton())
            {
            case 0:
                m_sceneManager.setLevel(1);
                m_sceneManager.switchTo(SceneType::GAMEPLAY);
                break;

            case 1:
                m_sceneManager.setLevel(2);
                m_sceneManager.switchTo(SceneType::GAMEPLAY);
                break;

            case 2:
                m_sceneManager.switchTo(SceneType::MAIN_MENU);
                break;

            default:
                break;
            }
        }
    }
}

void ChooseLevelMenuScene::handleInput() noexcept
{
}

void ChooseLevelMenuScene::update(const sf::Time dt) noexcept
{
}

void ChooseLevelMenuScene::draw() const noexcept
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}