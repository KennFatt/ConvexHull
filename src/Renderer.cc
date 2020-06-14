#include "Renderer.hpp"

#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <iostream>
#include <string>       // to_string()

#include "algorithm/Utils.hpp"

using namespace kf;

// --------------------- PUBLIC ---------------------

Renderer::Renderer(const unsigned _size)
    : pointsSize(_size)
{
    /** Setup the rendering environment */
    setup();

    /** Set running flag */
    isRunning = true;

    /** Start main loop */
    tick();
}

Renderer::~Renderer()
{
    delete algorithm;
}

// --------------------- PRIVATE ---------------------

void Renderer::setup()
{
    /** SFML window setup */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(
        sf::VideoMode(640, 480),
        "Convex Hull - Graham Scan algorithm",
        sf::Style::Titlebar | sf::Style::Close,
        settings
    );
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    /** Load font */
    if (!font.loadFromFile("res/montserrat.ttf")) {
        std::cout << "Could not find the font file!" << std::endl;
    }

    /** Generate random seed */
    srand(time(NULL));

    /** Instantiate the algorithm */
    algorithm = new GrahamScan(points, pointsSize, window.getSize().x, window.getSize().y);
}

void Renderer::tick()
{
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

void Renderer::render()
{
    /** Draw all points */
    for (unsigned i = 0; i < points.size(); ++i) {
        Point& p = points[i];

        /** Circle */
        sf::CircleShape c(4.0f);
        c.setPosition(sf::Vector2f(p.x, p.y));
        const sf::Color& circleColor = i == 0
           ? sf::Color(0x00, 0xFF, 0x00)
           : sf::Color(0xFF, 0x00, 0x00);
        c.setFillColor(circleColor);
        window.draw(c);

        /** Index indicator for each vertices */
        sf::Text t;
        if (isFlagEnabled(RenderFlags::RENDER_INDEXES)) {
            t.setString(t.getString() + std::to_string(i));
        }
    
        if (isFlagEnabled(RenderFlags::RENDER_COORDS)) {
            t.setString(t.getString() + std::to_string(i) + " (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")");
        }
        t.setFont(font);
        t.setCharacterSize(16);
        t.setPosition(sf::Vector2f(p.x, p.y + 8));
        window.draw(t);

        /** Lines from start point to each vertices */
        if (isFlagEnabled(RenderFlags::RENDER_LINES)) {
            if (i != 0) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(GrahamScan::getStartingPoint()->x, GrahamScan::getStartingPoint()->y)),
                    sf::Vertex(c.getPosition())
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }

    /** Show the final convex hull */
    if (isFlagEnabled(RenderFlags::RENDER_CONVEX)) {
        if (algorithm->getHull().size() >= 3) {
            auto& hull = algorithm->getHull();
            sf::ConvexShape convex(hull.size());
            for (unsigned i = 0; i < hull.size(); ++i) {
                convex.setPoint(i, sf::Vector2f(hull[i].x, hull[i].y));
            }
            convex.setFillColor(sf::Color(0xD0, 0xFE, 0xFE, 0x55));
            convex.setOutlineColor(sf::Color(0x01, 0x73, 0x74));
            convex.setOutlineThickness(2.0f);
            window.draw(convex);
        }
    }
}

void Renderer::handleEvent()
{
    sf::Event ev;
    while (window.pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::EventType::Closed: {
                onClose();
            } break;
                
            case sf::Event::EventType::KeyPressed: {
                onKeyPressed(ev.key.code);
            }; break;
        }
    }
}

void Renderer::onClose()
{
    isRunning = false;
}

void Renderer::onKeyPressed(sf::Keyboard::Key pressedKey)
{
    switch (pressedKey) {
        case sf::Keyboard::Key::Escape: {
            onClose();
        }; break;

        case sf::Keyboard::Key::R: {
            std::cout << "Updating points..." << std::endl;
            algorithm->refreshPoints();
        }; break;

        case sf::Keyboard::Key::Num1:
            enabledRenderFlags ^= 1 << RenderFlags::RENDER_INDEXES;
            break;
        
        case sf::Keyboard::Key::Num2:
            enabledRenderFlags ^= 1 << RenderFlags::RENDER_COORDS;
            break;
        
        case sf::Keyboard::Key::Num3:
            enabledRenderFlags ^= 1 << RenderFlags::RENDER_LINES;
            break;

        case sf::Keyboard::Key::Num4:
            enabledRenderFlags ^= 1 << RenderFlags::RENDER_CONVEX;
            break;

        default: {
            std::cout << "KeyPressed: " << pressedKey << std::endl;
        }; break;
    }
}

bool Renderer::isFlagEnabled(RenderFlags flag) {
    /** This is better than before, thanks StackOverflow */
    return (enabledRenderFlags >> flag) & 1;
}