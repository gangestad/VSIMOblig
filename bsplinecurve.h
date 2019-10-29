#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include "vector3d.h"
typedef gsl::Vector3D vec3;
/**
 * @brief The BSplineCurve class
 */
class BSplineCurve
{
public:
    std::vector<vec3> b;  // control points
    int n;                // n number of knots
    int d;                // d degrees
    std::vector<float> t; // knots

    // default constructor
    BSplineCurve() {}
    BSplineCurve(std::vector<float> knots, std::vector<vec3> controlpoints, int degree = 2) : b(controlpoints), d(degree), t(knots) {
        n = knots.size();
    }
};

#endif // BSPLINECURVE_H
