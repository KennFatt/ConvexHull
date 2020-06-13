#ifndef __KF_GRAHAM_SCAN_H
#define __KF_GRAHAM_SCAN_H

#include <vector>

#include "Point.hpp"

namespace kf {

class GrahamScan {
private:
    /**
     * Initial size for GrahamScan::points.
     */
    unsigned pointsSize;

    /**
     * All loaded points inside the canvas.
     */
    std::vector<Point> &points;

    /**
     * This is optional, but if we implement with multimedia library like SDL or
     * SFML, the value should be the width and height of the viewport.
     */
    unsigned canvasWidth;
    unsigned canvasHeight;

    /**
     * Stack of valid hull.
     */
    std::vector<Point> hull;

    /**
     * Most bottom (and most left) point.
     */
    // Point *startPoint;

    /**
     * Find starting point.
     */
    void findStartPoint();

    /**
     * Sort all points based on their polar angle related to start point.
     *
     * The sorting mechanism:
     * 1. Find point with counter-clockwise orientation from the start point.
     * 2. If the orientation is co-linear, then let the furthest comes first.
     *
     * Sorting algorithm: quicksort O(N log N)
     */
    void sortPolarAnglePoints();

public:
    static Point *startPoint;

    /**
     * Constructor will call GrahamScan::refreshPoints() to organize the points.
     */
    GrahamScan(std::vector<Point> &_points, unsigned _pointsSize,
               unsigned _canvasWidth = 0, unsigned _canvasHeight = 0);
    GrahamScan(const GrahamScan &) = delete;

    /**
     * Get points reference.
     */
    std::vector<Point> &getPoints();

    /**
     * Get final known hull.
     */
    std::vector<Point> &getHull();

    // /**
    //  * Get the start point.
    //  */
    // Point *getStartPoint();

    /**
     * Re-organize the points.
     *
     * 1. Reset points
     * 2. Find new starting point
     * 3. Sort all points polar angle respect to known starting point
     */
    void refreshPoints();
};

};    // namespace kf

#endif