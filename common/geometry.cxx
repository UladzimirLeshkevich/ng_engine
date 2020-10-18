#include "geometry.hxx"

float calculate_angle_radian(float x1, float y1, float x2, float y2)
{
    float t = (x1 * x2 + y1 * y2) / (sqrt((float)x1 * x1 + y1 * y1) * sqrt((float)x2 * x2 + y2 * y2));
    if (t < -1)
        t = -1;
    else if (t > 1)
        t = 1;
    return acos(t);
}

float calculate_angle_radian(vector v1, vector v2)
{
    float t = (v1.x * v2.x + v1.y * v2.y) / (sqrt((float)v1.x * v1.x + v1.y * v1.y) * sqrt((float)v2.x * v2.x + v2.y * v2.y));

    if (t < -1)
        t = -1;
    else if (t > 1)
        t = 1;
    return acos(t);
}

float calculate_angle_degree(float x1, float y1, float x2, float y2)
{
    float t = (x1 * x2 + y1 * y2) / (sqrt((float)x1 * x1 + y1 * y1) * sqrt((float)x2 * x2 + y2 * y2));
    if (t < -1)
        t = -1;
    else if (t > 1)
        t = 1;
    return acos(t) * 180.0f / pi;
}

float calculate_angle_degree(vector v1, vector v2)
{
    float t = (v1.x * v2.x + v1.y * v2.y) / (sqrt((float)v1.x * v1.x + v1.y * v1.y) * sqrt((float)v2.x * v2.x + v2.y * v2.y));

    if (t < -1)
        t = -1;
    else if (t > 1)
        t = 1;
    return acos(t) * 180.0f / pi;
}