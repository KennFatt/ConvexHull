#include "GrahamScan.hpp"

#include <cstdlib>    // qsort
#include <utility>    // std::swap

#include "Utils.hpp"

using namespace kf;

// Global variable
// TODO: Find the proper way to handle this hack,
Point _startPoint(0, 0);

GrahamScan::GrahamScan(std::vector<Point> &_points)
    : points(_points)
    , startPoint(findStartPoint()) {
    sortPolarAnglePoitns();
}

Point &GrahamScan::findStartPoint() {
    unsigned tmpIndex = 0;
    Point tmp = points.at(tmpIndex);

    /** O(N) */
    for (unsigned i = 1; i < points.size(); ++i) {
        const Point &p = points[i];
        /** Check if p is has lower or equals y value */
        if (p.y >= tmp.y) {
            /** Case: p is lower than tmp */
            if (p.y > tmp.y) {
                tmpIndex = i;
                tmp = points.at(tmpIndex);
            }
            /** Case: both at the same y-axis but p has lower x-axis */
            else if (p.x < tmp.x) {
                tmpIndex = i;
                tmp = points.at(tmpIndex);
            }
        }
    }

    /** In case the tmp were in correct place since then */
    if (tmpIndex == 0) {
        return points[0];
    }

    /** Swap element at tmpIndex with element at 0 */
    std::swap(points[0], points[tmpIndex]);

    /** HACK: Store the startPoint to internal global varible */
    _startPoint = points.at(0);

    return points[0];
}

void GrahamScan::sortPolarAnglePoitns() {
    /** Sorting by polar angle, respect to `startPoint` or points[0] */
    qsort(&points[1], points.size() - 1, sizeof(Point),
          [](const void *_a, const void *_b) -> int {
              Point a = *((Point *) _a);
              Point b = *((Point *) _b);

              int o = Utils::orientation(_startPoint, a, b);

              /** Co-linear case */
              if (o == 0) {
                  /** Take the furthest distance first */
                  return Utils::distanceNonSquared(_startPoint, b)
                               >= Utils::distanceNonSquared(_startPoint, a)
                            ? -1
                            : 1;
              }

              return o == 2 ? -1 : 1;
          });
}

Point &GrahamScan::getStartPoint() {
    return startPoint;
}

void GrahamScan::updateStartPoint() {
    startPoint = findStartPoint();
    sortPolarAnglePoitns();
}