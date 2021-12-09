/* #include <gtest/gtest.h>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Level.h"
#include "MainMenuScene.h"
#include "ChooseLevelMenuScene.h"
#include "PauseScene.h"
#include "SceneManager.h"

TEST(LEVEL, CREATE)
{
    EXPECT_ANY_THROW({
        sf::RenderWindow w;
        Level level(&w, "WrongFile");
    });

    EXPECT_NO_THROW({
        sf::RenderWindow w;
        Level level(&w, "ProperFile");
    });
}

TEST(LEVEL, TEST_ATTRIBUTES)
{
    sf::RenderWindow w;
    Level level(&w, "FileName");
    ASSERT_EQ(level.getMap().getSize(), sf::Vector2i(100, 30));
    ASSERT_EQ(level.getPlatforms().size(), 5);
    ASSERT_EQ(level.getHero().getPosition(), sf::Vector2f(50, 50));
    ASSERT_EQ(level.getFinish().getPosition(), sf::Vector2f(2000, 150));
    ASSERT_EQ(level.getCamera().getCenter(), sf::Vector2f(50, 50));
}

TEST(LEVEL, TEST_PROPER_FILE_READING)
{
    sf::RenderWindow w;
    Level level(&w, "FileName");
    ASSERT_EQ(level.getMap().getSize(), sf::Vector2i(100, 30));
    ASSERT_EQ(level.getPlatforms().size(), 5);
    ASSERT_EQ(level.getHero().getPosition(), sf::Vector2f(50, 50));
    ASSERT_EQ(level.getFinish().getPosition(), sf::Vector2f(2000, 150));
    ASSERT_EQ(level.getCamera().getCenter(), sf::Vector2f(50, 50));
}

TEST(MAIN_MENU_SCENE, TEST_BUTTONS)
{
    sf::RenderWindow w;
    MainMenuScene mainMenu(&w);
    ASSERT_EQ(mainMenu.getButtons().size(), 2);
}

TEST(CHOOSE_LEVEL_MENU, TEST_BUTTONS)
{
    sf::RenderWindow w;
    SceneManager sm(&w);
    ChooseLevelMenuScene chooseLevelMenu(&w, &sm);
    ASSERT_EQ(chooseLevelMenu.getButtons().size(), 2);
}

TEST(PAUSE_SCENE, TEST_BUTTONS)
{
    sf::RenderWindow w;
    PauseScene pause(&w);
    ASSERT_EQ(pause.getButtons().size(), 2);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} */