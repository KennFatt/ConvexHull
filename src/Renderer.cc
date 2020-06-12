#include "Renderer.hpp"

#include <iostream>

using namespace kf;

Renderer::Renderer() {
    setup();

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
        window.clear();
        render();
        window.display();
    }
}

void Renderer::setup() {
    window.create(sf::VideoMode(512, 512),
                  "Convex Hull - Graham Scan algorithm",
                  sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
}

void Renderer::render() {}

void Renderer::onClose() {
    isRunning = false;
}

void Renderer::onKeyPressed(sf::Keyboard::Key pressedKey) {
    switch (pressedKey) {
        default: {
            std::cout << "KeyPressed: " << pressedKey << std::endl;
        }; break;
    }
}