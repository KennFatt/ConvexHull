#include "GrahamScan.hpp"

#include <cstdlib>    // qsort()
#include <iostream>
#include <utility>    // swap()

#include "Utils.hpp"

using namespace kf;

// -------------------- INTERNAL --------------------

/** Re-define static field inside current source code */
Point *GrahamScan::startPoint = nullptr;

// --------------------- PUBLIC ---------------------

GrahamScan::GrahamScan(std::vector<Point> &_points, const unsigned _pointsSize, const unsigned _canvasWidth, const unsigned _canvasHeight)
    : pointsSize(_pointsSize)
    , canvasWidth(_canvasWidth)
    , canvasHeight(_canvasHeight)
    , points(_points)
{
    /** Call this function immediately for the first time ever */
    refreshPoints();
}

Point *GrahamScan::getStartingPoint()
{
    return startPoint;
}

std::vector<Point> &GrahamScan::getPoints()
{
    return points;
}

std::vector<Point> &GrahamScan::getHull()
{
    return hull;
}

void GrahamScan::refreshPoints()
{
    /** Generate random points */
    Utils::randomizePoints(points, pointsSize, canvasWidth, canvasHeight);

    /** Find the starting point */
    findStartPoint();

    /** Sort points' based on polar angle that respect to starting point */
    sortPolarAnglePoints();

    /** Clear previous records */
    if (!hull.empty()) {
        hull.clear();
    }

    /** Measure the hull now */
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (unsigned i = 2; i < points.size(); ++i) {
        while (Utils::orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
            hull.pop_back();
        }

        hull.push_back(points[i]);
    }

    std::cout << "Hull: " << std::endl;
    for (auto &h : hull) {
        std::cout << "- {" << h.x << ", " << h.y << "}" << std::endl;
    }
}

// --------------------- PRIVATE ---------------------

void GrahamScan::findStartPoint()
{
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

    /** Swap element at tmpIndex with element at 0 */
    std::swap(points[0], points[tmpIndex]);

    GrahamScan::startPoint = &points.at(0);
}

void GrahamScan::sortPolarAnglePoints()
{
    /** Sorting by polar angle, respect to `startPoint` or points[0] */
    qsort(&points[1], points.size() - 1, sizeof(Point),
        [](const void *_a, const void *_b) -> int {
            Point a = *((Point *) _a);
            Point b = *((Point *) _b);

            std::cout << "start -> {" << a.x << "," << a.y << "} -> {" << b.x
                    << "," << b.y << "}" << std::endl;
            int o = Utils::orientation(*startPoint, a, b);

            /** Co-linear case */
            if (o == 0) {
                std::cout << "Co-linear case..." << std::endl;
                /** Take the furthest distance first */
                return Utils::distanceNonSquared(*startPoint, b) >= Utils::distanceNonSquared(*startPoint, a) ? -1 : 1;
            }

            if (o == 2) {
                std::cout << "Point{" << a.x << "," << a.y << "} comes first!" << std::endl;
            }

            return o == 2 ? -1 : 1;
        }
    );
}