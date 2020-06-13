#ifndef __KF_POINT_H
#define __KF_POINT_H

namespace kf {

struct Point {
    int x;
    int y;

    Point(int _x, int _y)
        : x(_x)
        , y(_y) {}
};

}    // namespace kf

#endif