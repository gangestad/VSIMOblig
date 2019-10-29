#include "bsplinecurve.h"

BSplineCurve::BSplineCurve()
{

}
/**
 * @brief BSplineCurve::evaluateBSpline deBoor's algorithm for evaluating b-spline
 * @param my
 * @param x
 * @return
 */
vec3 BSplineCurve::evaluateBSpline(int my, float x)
{
    vec3 a[20];//
    for (int j = 0; j<=d; j++){
        a[d-j] = b[my-j];
    }

    for (int k=d; k>0; k--) {
        int j = my-k;
        for (int i=0; i<k; i++) {
            j++;
            float w = (x-t[j])/(t[j+k]-t[j]);
            a[i] = a[i] * (1-w) + a[i+1] * w;
        }
    }
    return a[0];
}
