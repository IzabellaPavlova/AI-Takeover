#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(sf::RenderWindow &w,
                             SceneSwitcher &scn_switcher,
                             const std::string &file_prefix,
                             const std::string &background_file_name,
                             const std::string &font_file_name,
                             const std::string &texture_file_name) : m_window(w),
                                                                     m_background(file_prefix + background_file_name),
                                                                     m_gui(w, file_prefix + font_file_name, file_prefix + texture_file_name),
                                                                     m_sceneSwitcher(scn_switcher)
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

void MainMenuScene::handleEvents(const sf::Event &event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            switch (m_gui.getPressedButton())
            {
            case 0:
                m_sceneSwitcher.switchTo(SceneType::CHOOSE_LEVEL_MENU);
                break;

            case 1:
            {
                m_window.close();
                break;
            }

            default:
                break;
            }
        }
    }
}

void MainMenuScene::handleInput() noexcept
{
}

void MainMenuScene::update(const sf::Time dt) noexcept
{
}

void MainMenuScene::draw() const noexcept
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}