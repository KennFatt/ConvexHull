#ifndef __KF_UTILS_H
#define __KF_UTILS_H

#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <vector>

#include "Point.hpp"

namespace kf {

class Utils {
private:
    Utils();

public:
    /**
     * Generate random int from `min` to `max` inclusively.
     */
    static int randint(int min, int max) {
        int diff = max - min;
        return rand() % diff + min;
    }

    /**
     * Randomize unique positions.
     */
    static void randomizePoints(std::vector<Point> &points, unsigned size,
                                const sf::Vector2u windowSize) {
        if (!points.empty()) {
            points.clear();
        }

        /** Used to prevent the point get outside the viewport */
        unsigned bufferX = windowSize.x / 6;
        unsigned bufferY = windowSize.y / 6;

        for (unsigned i = 0; i < size; ++i) {
            uint16_t x = Utils::randint(bufferX, windowSize.x - bufferX);
            uint16_t y = Utils::randint(bufferY, windowSize.y - bufferY);

            points.emplace_back(x, y);
        }
    }

    /**
     * Find out the orientation from given 3 ordered points.
     * Cross product of V x W: (Vx.Wy) - (Wx.Vy)
     *
     * Vector V = a->b
     * Vector W = a->c
     *
     * Expression:
     *  (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)
     *
     * @return int 0 -> Co-linear, 1 -> Clockwise, 2 -> Counter-Clockwise
     */
    static int orientation(Point &a, Point &b, Point &c) {
        int value = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);

        /** 0 -> Co-linear */
        if (value == 0) {
            return 0;
        }

        /**
         * 1 -> Clockwise
         * 2 -> Counter-Clockwise
         */
        return value < 0 ? 2 : 1;
    }

    static int distanceNonSquared(Point &a, Point &b) {
        return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    }
};

};    // namespace kf

#endif