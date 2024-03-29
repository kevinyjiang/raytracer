#include <iostream>
#include <ctime>
#include "constants.h"

#include "camera.h"
#include "bvh.h"
#include "scenes.h"
#include "color.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(0));
    
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = strtol(argv[1], nullptr, 0);
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    bvh_node world(defocus_blur_demo(), 0, 0);
    camera cam = camera_with_time(aspect_ratio);

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
