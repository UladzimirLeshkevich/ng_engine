#pragma once

struct point
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
    }
    vertex v[5];
};

const float pi = 3.1415926f;
