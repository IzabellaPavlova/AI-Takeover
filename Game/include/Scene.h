#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneType.h"

class Scene
{
public:
    Scene(){};
    virtual ~Scene(){};
    Scene(const Scene &) = delete;
    Scene(Scene &&) noexcept = delete;
    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) noexcept = delete;

    virtual void handleEvents(const sf::Event &event) noexcept = 0;
    virtual void handleInput() noexcept = 0;
    virtual void update(const sf::Time) noexcept = 0;
    virtual void draw() const noexcept = 0;
};