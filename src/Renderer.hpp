#ifndef __KF_RENDERER_H
#define __KF_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "algorithm/GrahamScan.hpp"
#include "algorithm/Point.hpp"

namespace kf {

class Renderer {
private:
    /**
     * Amount of points that will be rendered in the canvas.
     *
     * @see Renderer::points
     */
    const unsigned pointsSize;

    /**
     * Check whether the application is running still or
     * flagged to stop.
     */
    bool isRunning = false;

    /**
     * SFML main font.
     */
    sf::Font font;

    /**
     * SFML Window that would render the frames.
     */
    sf::RenderWindow window;

    /**
     * Randomly distributed points.
     */
    std::vector<Point> points;

    /**
     * Algorithm backend.
     */
    GrahamScan* algorithm;

    /**
     * Setup all the things before start to rendering the canvas.
     */
    void setup();

    /**
     * Call the program main loop to trigger the Renderer:render().
     */
    void tick();

    /**
     * The main function to draw all objects into the canvas.
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

    /**
     * Polling windows event in separated function,
     * but it's still in the same main thread.
     */
    void handleEvent();

public:
    /**
     * Renderer flow:
     * 1. Renderer::setup()
     * 2. Loop Renderer::render();
     */
    explicit Renderer(const unsigned pointsSize = 5);

    /**
     * Copy constructor is not allowed for this class.
     */
    Renderer(const Renderer&) = delete;

    /**
     * Delete most of garbage.
     */
    ~Renderer();
};

};    // namespace kf

#endif