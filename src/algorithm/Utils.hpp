#ifndef __KF_UTILS_H
#define __KF_UTILS_H

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
    static int randint(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    /**
     * Randomize unique positions.
     */
    static void randomizePoints(std::vector<Point> &points, unsigned size, unsigned canvasWidth, unsigned canvasHeight)
    {
        if (!points.empty()) {
            points.clear();
        }

        /** Used to prevent the point get outside the viewport */
        unsigned bufferX = canvasWidth / 6;
        unsigned bufferY = canvasHeight / 6;

        for (unsigned i = 0; i < size; ++i) {
            int x = Utils::randint(bufferX, canvasWidth - bufferX);
            int y = Utils::randint(bufferY, canvasHeight - bufferY);

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
    static int orientation(Point a, Point b, Point c)
    {
        int value = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);

        /**
         * 0 -> Co-linear
         * 1 -> Clockwise
         * 2 -> Counter-Clockwise
         */
        return value == 0 ? 0 : (value > 0 ? 1 : 2);
    }

    /**
     * Get distance (non squared) between 2 point in cartesian plane.
     */
    static int distanceNonSquared(Point &a, Point &b)
    {
        return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    }
};

};    // namespace kf

#endif