#pragma once

#include <cmath>

struct point
{
    float x = 0.f;
    float y = 0.f;
};

struct vector
{
    float x = 0.f;
    float y = 0.f;
};

struct vertex
{
    float x = 0.f;
    float y = 0.f;

    float tx = 0.f; // textures
    float ty = 0.f;
};

struct triangle
{
    triangle()
    {
        v[0] = vertex();
        v[1] = vertex();
        v[2] = vertex();
    }
    vertex v[3];
};

struct rectangle
{
    rectangle()
    {
        v[0] = vertex();
        v[1] = vertex();
        v[2] = vertex();
        v[3] = vertex();

        // direction relative to the x-axis
        v[4] = vertex();

        // center of the rectangle
        v[5] = vertex();
    }
    vertex v[6];
};

const float pi = 3.1415926f;

// double angle( int x1, int y1, int x2, int y2)
// {
//     double t = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));
//     if     (t<-1) t=-1;
//     else if(t> 1) t= 1;
//     return acos(t);
// }

// https://ru.onlinemschool.com/math/assistance/vector/angl/
// https://allcalc.ru/node/752

float calculate_angle_radian(float x1, float y1, float x2, float y2);
float calculate_angle_radian(vector v1, vector v2);

float calculate_angle_degree(float x1, float y1, float x2, float y2);
float calculate_angle_degree(vector v1, vector v2);