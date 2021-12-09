#include "PauseScene.h"
#include <iostream>

PauseScene::PauseScene(sf::RenderWindow &w) : m_window(w)
{
    createButtons();
}

PauseScene::~PauseScene()
{
}

void PauseScene::handleEvents(const sf::Event &event) {}

SceneType PauseScene::handleInput()
{
    return SceneType::PAUSE;
}

SceneType PauseScene::update(sf::Time dt)
{
    return SceneType::PAUSE;
}

void PauseScene::draw() const
{
}

void PauseScene::createButtons() {}

std::vector<Button> &PauseScene::getButtons()
{
    return m_buttons;
}