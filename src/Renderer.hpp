#ifndef __KF_RENDERER_H
#define __KF_RENDERER_H

#include <SFML/Graphics.hpp>

namespace kf {

class Renderer {
private:
    bool isRunning = true;

    /**
     * SFML Window that would render the frames.
     */
    sf::RenderWindow window;

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