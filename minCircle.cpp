//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "minCircle.h"
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"


/**
 * return the distance between two point
 **/
float disPointInCircle(const Point &APoint, const Point &BPoint) {
    return sqrt(pow(APoint.x - BPoint.x, 2)
                + pow(APoint.y - BPoint.y, 2));
}

/**
 * the function check if a point is in / ot in boundaries of circle
 **/
bool isInside(const Circle &c, const Point &p) {
    return disPointInCircle(c.center, p) <= c.radius;
}

/**
 * the function used to find circle when 3 point are input
**/
Point getCircleCenter(float bx, float by,
                      float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

/**
 the tunction return a  circle that intersects three points together
 **/
Circle circleFrom(const Point &a, const Point &b,
                  const Point &c) {
    Point I = getCircleCenter(b.x - a.x, b.y - a.y,
                              c.x - a.x, c.y - a.y);

    I.x += a.x;
    I.y += a.y;
    return {I, disPointInCircle(I, a)};
}

/**
 the function  return the smallest circle that intersects 2 points
 **/
Circle circleFrom(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C = {(A.x + B.x) / 2, (A.y + B.y) / 2};

    // Set the radius to be half the distance AB
    return {C, disPointInCircle(A, B) / 2};
}

/**
 the function check if a circle encloses the input points
 **/
bool isValidCircle(const Circle &c,
                   const vector<Point> &P) {
    for (const Point &p: P)
        if (!isInside(c, p))
            return false;
    return true;
}

/**
 the function  return the minimum enclosing circle for N <= 3
 @param PVec vector of point
 **/
Circle minCircleTrivial(vector<Point> &PVec) {
    assert(PVec.size() <= 3);
    if (PVec.empty()) {
        return {{0, 0}, 0};
    } else if (PVec.size() == 1) {
        return {PVec[0], 0};
    } else if (PVec.size() == 2) {
        return circleFrom(PVec[0], PVec[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circleFrom(PVec[i], PVec[j]);
            if (isValidCircle(c, PVec))
                return c;
        }
    }
    return circleFrom(PVec[0], PVec[1], PVec[2]);
}

/**
 *
 * @param PointVec vector of Point
 * @param R Vector of Point in the circle boundary
 * @param n the number of point that not yet in the circle
 * @return return a circle using the welzl algorithm
 */
Circle welzlAlgorithmHelper(vector<Point> &PointVec, vector<Point> R, int n) {
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return minCircleTrivial(R);
    }
    // random point randomly
    int idx = rand() % n;
    Point p = PointVec[idx];

    // picked point at the end of PointVec
    swap(PointVec[idx], PointVec[n - 1]);

    // Get the MEC circle d from the set of points PointVec - {p}
    Circle d = welzlAlgorithmHelper(PointVec, R, n - 1);

    // If d contains p, return d
    if (isInside(d, p)) {
        return d;
    }
    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);
    return welzlAlgorithmHelper(PointVec, R, n - 1);
}

/**
 * creat a circle by the welzl algorithm
 **/
Circle welzl(const vector<Point> &P) {
    vector<Point> P_copy = P;
    random_shuffle(P_copy.begin(), P_copy.end());
    return welzlAlgorithmHelper(P_copy, {}, P_copy.size());
}

/**
 * build a vector form array of pointer to point
 **/
vector<Point> fromPointersToVector(Point **points, size_t size) {
    vector<Point> pointVector;
    for (int i = 0; i < size; ++i) {
        Point &point = *points[i];
        pointVector.push_back(point);
    }
    return pointVector;
}


/**
 *
 * @param points pointer to array of pointer to point
 * @param size the number of point in the array
 * @return a circle contain all the point in his radius
 */
Circle findMinCircle(Point **points, size_t size) {

    vector<Point> pointVector = fromPointersToVector(points, size);
    vector<Point> P_copy = pointVector;
    random_shuffle(P_copy.begin(), P_copy.end());
    return welzlAlgorithmHelper(P_copy, {}, P_copy.size());
}
