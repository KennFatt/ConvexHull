#ifndef __KF_UTILS_H
#define __KF_UTILS_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "Point.hpp"

namespace kf {

class Utils {
private:
    Utils();

public:
    static int randint(int min, int max) {
        int diff = max - min;
        return rand() % diff + min;
    }

    static void randomizePoints(std::vector<Point> &points, unsigned size,
                                const sf::Vector2u windowSize) {
        if (!points.empty()) {
            points.clear();
        }

        /** Used to prevent the point get outside the viewport */
        unsigned bufferX = windowSize.x / 4;
        unsigned bufferY = windowSize.y / 4;

        for (unsigned i = 0; i < size; ++i) {
            uint16_t x = Utils::randint(bufferX, windowSize.x - bufferX);
            uint16_t y = Utils::randint(bufferY, windowSize.y - bufferY);

            points.emplace_back(x, y);
        }
    }
};

};    // namespace kf

#endif