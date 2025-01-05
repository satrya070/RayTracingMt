#include "color.h"
#include "vec3.h"

#include <iostream>

int main()
{
	int image_width = 256;
	int image_height = 256;

	//render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			/*auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);*/
			auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
			write_color(std::cout, pixel_color);

			//std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	std::clog << "\r Done. \n";
}