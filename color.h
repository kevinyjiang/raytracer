#pragma once

#include "vec3.h"
#include <iostream>

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        // Abstract away scatter calculation to depend on material type
        // Diffuse uses randomized vector addition, metal uses reflection formula
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    // linear interpolation to create a soft gradiant background
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1, 1, 1) + t*color(.5, .7, 1);
}

void write_color(std::ostream& out, color c) {
    out << static_cast<int>(255.999 * c.x()) << ' '
        << static_cast<int>(255.999 * c.y()) << ' '
        << static_cast<int>(255.999 * c.z()) << '\n';
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
