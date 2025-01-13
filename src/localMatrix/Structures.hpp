#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_



#define _LOCAL_MATRIX_IN_DEBUG_ON_


#ifdef _LOCAL_MATRIX_IN_DEBUG_ON_

struct Point {
    int index;
    double x, y;
};

struct Triangle {
    Point a, b, c;

    Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}
};

#endif /* _LOCAL_MATRIX_IN_DEBUG_ON_ */

struct Sijk {
    double i, j, k;
};

#endif /* _STRUCTURES_HPP_ */