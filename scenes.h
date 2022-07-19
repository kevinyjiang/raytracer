#pragma once

#include "hittable_list.h"
#include "constants.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "material.h"

void _add_ground(hittable_list& world, color ground_color, int ground_size) {
    auto ground_material = make_shared<lambertian>(ground_color);
    world.add(make_shared<sphere>(point3(0, -ground_size, 0), ground_size, ground_material));
}

hittable_list defocus_blur_demo() {
    hittable_list world;
    _add_ground(world, color(0.9, 0.9, 0.9), 1000);

    for (int a = -10; a < 10; a++) {
        for (int b = -8; b < 8; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.25, b + 0.9*random_double());

            if ((center - point3(3, 0.25, 0)).length() > .9) {
                shared_ptr<material> sphere_material;
                auto choose_albedo = static_cast<int>(random_double(0, 2));
                if (choose_mat < 0.4) {
                    // shiny
                    auto albedo = metals[choose_albedo];
                    sphere_material = make_shared<metal>(albedo, 0);
                    world.add(make_shared<sphere>(center, 0.25, sphere_material));
                } else if (choose_mat < 0.8) {
                    // metal
                    auto albedo = shiny[choose_albedo];
                    auto fuzz = random_double(.5, 1);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.25, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.25, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(1.5, 1, 0), 1, material1));
    world.add(make_shared<sphere>(point3(1.5, 1, 0), -.92, material1));

    auto material3 = make_shared<metal>(color(.83, .7, .36), 0.0); 
    world.add(make_shared<sphere>(point3(3, .75, -.5), .75, material3));
   
    return world;
}

hittable_list motion_blur_demo() {
    hittable_list world;
    _add_ground(world, color(0.9, 0.9, 0.9), 1000);

    for (int a = -10; a < 10; a++) {
        for (int b = -8; b < 8; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.25, b + 0.9*random_double());

            if ((center - point3(3, 0.25, 0)).length() > .9) {
                shared_ptr<material> sphere_material;
                auto choose_albedo = static_cast<int>(random_double(0, 2));
                if (choose_mat < 0.4) {
                    // shiny, bouncing
                    auto albedo = metals[choose_albedo];
                    sphere_material = make_shared<metal>(albedo, 0);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                        center, center2, 0.0, 1.0, 0.25, sphere_material));
                } else if (choose_mat < 0.8) {
                    // metal
                    auto albedo = shiny[choose_albedo];
                    auto fuzz = random_double(.5, 1);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.25, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.25, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(1.5, 1, 0), 1, material1));
    world.add(make_shared<sphere>(point3(1.5, 1, 0), -.92, material1));

    auto material3 = make_shared<metal>(color(.83, .7, .36), 0.0); 
    world.add(make_shared<sphere>(point3(3, .75, -.5), .75, material3));
   

    return world;
}