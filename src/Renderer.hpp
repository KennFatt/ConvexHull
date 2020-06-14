#ifndef __KF_RENDERER_H
#define __KF_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "algorithm/GrahamScan.hpp"
#include "algorithm/Point.hpp"

namespace kf {

class Renderer {
public:
    /**
     * Rendering flags to show specific object into the canvas.
     */
    typedef enum : unsigned {
        RENDER_DEFAULT  = 0b0000,
        RENDER_INDEXES  = 0b0001,
        RENDER_COORDS   = 0b0010,
        RENDER_LINES    = 0b0100,
        RENDER_CONVEX   = 0b1000,
    } RenderFlags;
    unsigned enabledRenderFlags = RenderFlags::RENDER_DEFAULT;

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

    /**
     * Check whether flags is enabled or not.
     */
    bool isFlagEnabled(RenderFlags);

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