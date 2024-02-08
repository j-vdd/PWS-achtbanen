#include "Sphere.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

Sphere::Sphere(const int radius, const int resolution)
{
    float delta_theta = 2 * M_PI / resolution;
    float delta_phi = M_PI / resolution;
    float theta, phi;

    // vertex
    float x, y, z, xy;

    // entity
    int k1, k2;


    // vertex
    for (unsigned int i = 0; i <= resolution; ++i)      // each stack
    {
        phi = M_PI / 2 - i * delta_phi;
        xy = radius * cosf(phi);
        z = radius * sinf(phi);

        for (unsigned int j = 0; j <= resolution; ++j)  // each sector 
        {
            theta = j * delta_theta;
            x = xy * cosf(theta);
            y = xy * sinf(theta);

            std::cout << "x :" << x << " y:" << y << " z :" << z << "\n";

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

        }
    }
    // entity
    for (int i = 0; i < resolution; ++i)
    {
        k1 = i * (resolution + 1);
        k2 = k1 + resolution + 1;

        for (unsigned int j = 0; j < resolution; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);      // form a upper left triangle
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (resolution - 1))      // form a lower right triangle
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            line_indices.push_back(k1);
            line_indices.push_back(k2);

            if (i != 0)
            {
                line_indices.push_back(k1);
                line_indices.push_back(k1 + 1);
            }
            std::cout << "1 :" << k1 << " 2 :" << k2 << " 3 :" << (k1 + 1) << "\n";
        }
    }
};
