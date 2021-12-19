#pragma once
#include "SceneType.h"

class SceneSwitcher
{
public:
    SceneSwitcher(){};
    virtual ~SceneSwitcher(){};
    SceneSwitcher(const SceneSwitcher &) = delete;
    SceneSwitcher(SceneSwitcher &&) noexcept = delete;
    SceneSwitcher &operator=(const SceneSwitcher &) = delete;
    SceneSwitcher &operator=(SceneSwitcher &&) noexcept = delete;

    virtual void switchTo(const SceneType) noexcept = 0;
};