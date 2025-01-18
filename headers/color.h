#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "interval.h"
#include "vec3.h"
#include <string>
#include <format>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);

	return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// apply a linear to gamma transform for gamma 2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	// translate [0, 1] to byte range [0, 255]
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// write out the pixel color
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

std::string write_color_string(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// apply a linear to gamma transform for gamma 2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	// translate [0, 1] to byte range [0, 255]
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// write out the pixel color
	std::string colorString = std::format("{} {} {}\n", rbyte, gbyte, bbyte);
	
	return colorString;
}

#endif
