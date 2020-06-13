#ifndef __KF_GRAHAM_SCAN_H
#define __KF_GRAHAM_SCAN_H

#include <stack>
#include <vector>

#include "Point.hpp"

namespace kf {

class GrahamScan {
private:
    /**
     * All loaded points inside the canvas.
     */
    std::vector<Point> &points;

    /**
     * Stack of valid hull.
     */
    std::stack<Point> hull;

    /**
     * Most bottom (and most left) point.
     */
    Point &startPoint;

    /**
     * Find starting point.
     */
    Point &findStartPoint();

    /**
     * Sort all points based on their polar angle related to start point.
     *
     * The sorting mechanism:
     * 1. Find point with counter-clockwise orientation from the start point.
     * 2. If the orientation is co-linear, then let the furthest comes first.
     *
     * Sorting algorithm: quicksort O(N log N)
     */
    void sortPolarAnglePoitns();

public:
    GrahamScan(std::vector<Point> &);

    GrahamScan(const GrahamScan &) = delete;

    /**
     * Get the start point.
     */
    Point &getStartPoint();

    /**
     * Update its start point due the points also changed.
     */
    void updateStartPoint();
};

};    // namespace kf

#endif