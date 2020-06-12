#ifndef __KF_POINT_H
#define __KF_POINT_H

#include <cstdint>

namespace kf {

struct Point {
    int16_t x;
    int16_t y;

    Point(int16_t _x, int16_t _y)
        : x(_x)
        , y(_y) {}
};

}    // namespace kf

#endif