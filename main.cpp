#include "constants.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "moving_sphere.h"
#include "bvh.h"

#include <iostream>
#include <ctime>

hittable_list random_scene() {
    const color metals[2] = { color(.83, .7, .36), color(.01, .01, .01) };
    const color shiny[2] = { color(.95, .95, .95), color(.08, .08, .08) };

    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

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

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
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

int main() {
    std::srand(std::time(0));
    
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 300;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World

    auto world_raw = random_scene();
    bvh_node world(world_raw, 0, 0);

    // Camera

    point3 lookfrom(11.5,3,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
        
    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = double(i + random_double()) / (image_width-1);
                auto v = double(j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
