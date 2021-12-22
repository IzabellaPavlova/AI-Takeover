#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

template <typename T>
class Camera
{
public:
    Camera(sf::RenderWindow &w, T &t) : m_window(w),
                                        m_target(t)
    {
    }
    ~Camera() {}

    Camera(const Camera &) = delete;
    Camera(Camera &&) noexcept = delete;
    Camera &operator=(const Camera &) = delete;
    Camera &operator=(Camera &&) noexcept = delete;

    void update()
    {
        sf::View view = m_window.getView();
        float x_pos = m_target.getPosition().x;
        float del_x = x_pos - view.getCenter().x;
        float halfWindowSize = (float)m_window.getSize().x / 2;
        float padding = 0.2 * halfWindowSize;
        if (std::abs(del_x) <= padding)
            return;

        x_pos += del_x < 0 ? padding : -padding;
        x_pos = std::max(x_pos, halfWindowSize);
        x_pos = std::min(x_pos, max_size - halfWindowSize);

        view.setCenter(x_pos, (float)m_window.getSize().y / 2);
        m_window.setView(view);
    }

    void setMaxSize(float ms)
    {
        max_size = ms;
    }

private:
    sf::RenderWindow &m_window;
    T &m_target;
    float max_size;
};