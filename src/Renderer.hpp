#ifndef __KF_RENDERER_H
#define __KF_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "algorithm/Point.hpp"

namespace kf {

class Renderer {
private:
    /**
     * Check whether the application is running still or
     * flagged to stop.
     */
    bool isRunning = true;

    /**
     * SFML Window that would render the frames.
     */
    sf::RenderWindow window;

    /**
     * Randomly distributed points.
     */
    std::vector<Point> points;

    /**
     * Setup all the things before start to rendering the canvas.
     */
    void setup();

    /**
     * Start
     */
    void render();

    /**
     * Handle SFML event when window is closed.
     */
    void onClose();

    /**
     * Handle SFML event when key pressed.
     */
    void onKeyPressed(sf::Keyboard::Key);

public:
    /**
     * Renderer flow:
     * 1. Renderer::setup()
     * 2. Loop Renderer::render();
     */
    Renderer();

    /**
     * Copy constructor is not allowed for this class.
     */
    Renderer(const Renderer&) = delete;
};

};    // namespace kf

#endif