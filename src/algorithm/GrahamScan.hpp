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

    void sortPolarAnglePoitns();

public:
    GrahamScan(std::vector<Point> &);

    GrahamScan(const GrahamScan &) = delete;

    Point &getStartPoint();

    void updateStartPoint();
};

};    // namespace kf

#endif