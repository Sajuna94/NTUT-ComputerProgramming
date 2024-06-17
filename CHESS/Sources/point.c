#include "../Tools/point.h"

Point newPoint(int x, int y) {
    Point point = {
        .X = x,
        .Y = y
    };
    return point;
}