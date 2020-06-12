#include "Renderer.hpp"

#include <cstdlib>    // rand(), srand
#include <ctime>    // time()
#include <iostream>

#include "algorithm/Utils.hpp"

using namespace kf;

Renderer::Renderer() {
    /** Setup the rendering environment */
    setup();

    /** Set running flag */
    isRunning = true;

    while (window.isOpen()) {
        /** Event handling */
        sf::Event ev;
        while (window.pollEvent(ev)) {
            switch (ev.type) {
                case sf::Event::EventType::Closed: {
                    onClose();
                }; break;

                case sf::Event::EventType::KeyPressed: {
                    onKeyPressed(ev.key.code);
                }; break;
            }
        }

        if (!isRunning) {
            window.close();
        }

        /** Render the screen */
        window.clear(sf::Color(0xFA, 0xFA, 0xFA));
        render();
        window.display();
    }
}

void Renderer::setup() {
    /** SFML window setup */
    window.create(sf::VideoMode(512, 512),
                  "Convex Hull - Graham Scan algorithm",
                  sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    /** Generate random seed */
    srand(time(NULL));

    /** Initialize the points */
    Utils::randomizePoints(points, 16, window.getSize());
}

void Renderer::render() {
    for (auto& p : points) {
        sf::CircleShape c(4.0f);
        c.setFillColor(sf::Color(0xFF, 0x00, 0x00));
        c.setPosition((float) p.x, (float) p.y);
        window.draw(c);
    }
}

void Renderer::onClose() {
    isRunning = false;
}

void Renderer::onKeyPressed(sf::Keyboard::Key pressedKey) {
    switch (pressedKey) {
        case sf::Keyboard::Key::Escape: onClose(); break;
        case sf::Keyboard::Key::R: {
            Utils::randomizePoints(points, 16, window.getSize());
        }; break;
        default: {
            std::cout << "KeyPressed: " << pressedKey << std::endl;
        }; break;
    }
}