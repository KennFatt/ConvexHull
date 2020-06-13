#include "Renderer.hpp"

#include <cstdlib>    // rand(), srand
#include <ctime>    // time()
#include <iostream>
#include <string>

#include "algorithm/Utils.hpp"

using namespace kf;

Renderer::Renderer(unsigned _size)
    : pointsSize(_size) {
    /** Setup the rendering environment */
    setup();

    /** Set running flag */
    isRunning = true;

    while (window.isOpen()) {
        /** Event handling */
        handleEvent();

        if (!isRunning) {
            window.close();
        }

        /** Render the screen */
        window.clear(sf::Color(0x12, 0x12, 0x12));
        render();
        window.display();
    }
}

void Renderer::setup() {
    /** SFML window setup */
    sf::ContextSettings settings;

    /** Anti-aliasnig x8 */
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(512, 512),
                  "Convex Hull - Graham Scan algorithm",
                  sf::Style::Titlebar | sf::Style::Close, settings);

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    /** Load font */
    if (!font.loadFromFile("res/montserrat.ttf")) {
        std::cout << "Could not find the font file!" << std::endl;
    }

    /** Generate random seed */
    srand(time(NULL));

    /**
     * Initialize the points.
     *
     * TODO: Move it inside algorithm things.
     */
    Utils::randomizePoints(points, pointsSize, window.getSize());

    /** Instantiate the algorithm */
    std::cout << "Before: {" << points[0].x << ", " << points[0].y << "}"
              << std::endl;
    algorithm = new GrahamScan(points);
    std::cout << "After: {" << points[0].x << ", " << points[0].y << "}"
              << std::endl;
}

void Renderer::render() {
    /** Draw all points and point's index first */
    for (unsigned i = 0; i < points.size(); ++i) {
        Point& p = points[i];

        /** Circle */
        sf::CircleShape c(4.0f);
        c.setPosition((float) p.x, (float) p.y);
        const sf::Color& circleColor =
           i == 0 ? sf::Color(0x00, 0xFF, 0x00) : sf::Color(0xFF, 0x00, 0x00);
        c.setFillColor(circleColor);
        window.draw(c);

        /** Index */
        sf::Text t(std::to_string(i), font, 16);
        t.setPosition((float) p.x, (float) p.y + 7.5f);
        window.draw(t);

        /** Lines */
        if (i != 0) {
            sf::Vertex lines[] = {
               sf::Vertex(sf::Vector2f((float) algorithm->getStartPoint().x,
                                       (float) algorithm->getStartPoint().y)),
               sf::Vertex(c.getPosition())};
            window.draw(lines, 2, sf::Lines);
        }
    }
}

void Renderer::handleEvent() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::EventType::Closed: onClose(); break;

            case sf::Event::EventType::KeyPressed:
                onKeyPressed(ev.key.code);
                break;

                // case sf::Event::EventType::MouseMoved: {
                //     std::cout << "Mouse @{" << ev.mouseMove.x << ", "
                //               << ev.mouseMove.y << "}" << std::endl;
                // }; break;
        }
    }
}

void Renderer::onClose() {
    isRunning = false;
    delete algorithm;
}

void Renderer::onKeyPressed(sf::Keyboard::Key pressedKey) {
    switch (pressedKey) {
        case sf::Keyboard::Key::Escape: onClose(); break;
        case sf::Keyboard::Key::R: {
            std::cout << "Updating points..." << std::endl;
            Utils::randomizePoints(points, pointsSize, window.getSize());
            algorithm->updateStartPoint();
        }; break;
        default: {
            std::cout << "KeyPressed: " << pressedKey << std::endl;
        }; break;
    }
}