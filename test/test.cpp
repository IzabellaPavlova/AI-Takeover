#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "Background.h"
#include "Constants.h"
#include "Gui.h"
#include "Button.h"
#include "Game.h"
#include "SceneManager.h"
#include "Level.h"

TEST(TEST_GAME, TEST_BACKGROUND)
{
    testing::internal::CaptureStderr();
    Background b("background_image");
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ(output, "Failed to load image \"background_image\". "
                      "Reason: Unable to open file\nFailed to load "
                      "background texture from file 'background_image'\n");
}

TEST(TEST_GAME, TEST_BUTTON)
{
    Button button1("Button text", sf::Font(), sf::Texture());
    ASSERT_FALSE(button1.isPressed(sf::Vector2f(9999.f, 9999.f)));

    sf::Font font;
    if (!font.loadFromFile("../../Files/arial.ttf"))
        FAIL();

    sf::Texture texture;
    if (!texture.loadFromFile("../../Files/ButtonTexture.png"))
        FAIL();

    Button button2("Button text", font, texture);
    ASSERT_TRUE(button2.getSize().x > 0 && button2.getSize().y > 0);

    button2.setPosition(sf::Vector2f(0.f, 0.f), 800.f);
    ASSERT_FALSE(button2.isPressed(sf::Vector2f(-500.f, -500.f)));
    ASSERT_TRUE(button2.isPressed(sf::Vector2f(0.f, 0.f)));
}

TEST(TEST_GAME, TEST_CONSTANTS)
{
    std::string f_name = "config_file_1.txt";
    std::ofstream myfile;
    myfile.open(f_name);
    myfile << "SCREEN_INITIAL_WIDTH=1200\n"
              "SCREEN_INITIAL_HEIGHT=800\n"
              "TILE_SIZE=50\n"
              "HERO_VELOCITY=375\n"
              "HERO_ACCELERATION=1250\n"
              "PLATFORM_VELOCITY=125";
    myfile.close();

    Constants c;
    ASSERT_FALSE(c.read_file("Some file name"));
    ASSERT_TRUE(c.read_file(f_name));
    ASSERT_EQ(c.at("SCREEN_INITIAL_WIDTH"), 1200.f);
    ASSERT_EQ(c.at("SCREEN_INITIAL_HEIGHT"), 800.f);
    ASSERT_EQ(c.at("TILE_SIZE"), 50.f);
    ASSERT_EQ(c.at("HERO_VELOCITY"), 375.f);
    ASSERT_EQ(c.at("HERO_ACCELERATION"), 1250.f);
    ASSERT_EQ(c.at("PLATFORM_VELOCITY"), 125.f);

    EXPECT_ANY_THROW(c.at("some_string_not_in_congig_file"));

    std::string f_name_2 = "config_file_11.txt";
    std::ofstream myfile_2;
    myfile_2.open(f_name_2);
    myfile_2 << "SCREEN_INITIAL_HEIGHT=krjb\n";
    myfile_2.close();

    Constants c_2;
    testing::internal::CaptureStderr();

    ASSERT_FALSE(c_2.read_file(f_name_2));

    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ(output, "bad lexical cast: source type value could not be interpreted as target "
                      "(File : 'config_file_11.txt' ; line : 'SCREEN_INITIAL_HEIGHT=krjb)'\n");
}

TEST(TEST_GAME, TEST_GAME)
{
    std::string f_name = "config_file_2.txt";
    std::ofstream myfile;
    myfile.open(f_name);
    myfile << "TILE_SIZE=50\n"
              "HERO_VELOCITY=375\n"
              "HERO_ACCELERATION=1250\n"
              "PLATFORM_VELOCITY=125";
    myfile.close();

    Game game("", f_name);
    testing::internal::CaptureStderr();

    game.run();

    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ(output, "Constant SCREEN_INITIAL_HEIGHT not found in constants\n");
}

TEST(TEST_GAME, TEST_GUI)
{
    EXPECT_ANY_THROW(Gui gui(sf::RenderWindow(), "some_font_file_name", "some_texture_file_name"));

    sf::RenderWindow window(sf::VideoMode(600.f, 800.f), "Window name");
    Gui gui(window, "../../Files/arial.ttf", "../../Files/ButtonTexture.png");
    ASSERT_EQ(gui.getPressedButton(), -1);

    gui.addButton("Some button");
    sf::Mouse::setPosition(sf::Vector2i(window.getSize()) / 2, window);
    ASSERT_EQ(gui.getPressedButton(), 0);
}

TEST(TEST_GAME, TEST_SCENE_MANAGER)
{
    std::string f_name = "config_file_3.txt";
    std::ofstream myfile;
    myfile.open(f_name);
    myfile << "SCREEN_INITIAL_WIDTH=1200\n"
              "SCREEN_INITIAL_HEIGHT=800\n"
              "TILE_SIZE=50\n"
              "HERO_VELOCITY=375\n"
              "HERO_ACCELERATION=1250\n"
              "PLATFORM_VELOCITY=125";
    myfile.close();

    Constants c;
    ASSERT_TRUE(c.read_file(f_name));

    sf::RenderWindow window(sf::VideoMode(600.f, 800.f), "Window name");
    SceneManager scn_manager(window, c, "../../Files/");
    ASSERT_TRUE(scn_manager.successfullyInitialized());
}

TEST(TEST_LEVEL, TEST_MAP) {

    EXPECT_ANY_THROW(Map map(-10,10));
    EXPECT_ANY_THROW(Map map(10,-10));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}