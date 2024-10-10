#ifndef MINISIM_VECTOR_H
#define MINISIM_VECTOR_H

#include <cmath>
#include <numbers>  // 2π = std::numbers::pi * 2
#include <iostream>
#include <VelocityVector.h>

static VelocityVector::from_cartesian_components(double north_south, double east_west) {
    return VelocityVector(north_south, east_west);
}

static VelocityVector::from_polar_components(double speed, double, heading) {
        return VelocityVector(          //
			speed * std::cos(heading),  // north_south
			speed * std::sin(heading)   // east_west
    );
}

double VelocityVector::get_north_south() const {
    return north_south;
}

double VelocityVector::get_east_west() const {
    return east_west;
}

double VelocityVector::get_magnitude() const {
    double res = std::sqrt(std::pow(north_south,2) + std::pow(east_west, 2));
    return res;
}

double VelocityVector::get_heading() const {
		double pi = std::numbers::pi;

		std::cout << pi << "\n";

		double range = std::atan2(east_west, north_south);

		if (range < 0) {
			range += 2 * pi;
		}

		return range;
}

double VelocityVector::angle_between(const VelocityVector& other) const {

		if (this->get_magnitude() == 0 or other.get_magnitude() == 0) {return 0;}


		double dot_product = (other.north_south * north_south) + (other.east_west * east_west);
		// double cross_product = (other.north_south * east_west) - (other.east_west * north_south);
		double cross_product = (other.east_west * north_south) - (other.north_south * east_west);
		return -std::atan2(cross_product, dot_product);
}

VelocityVector::VelocityVector(double north_south, double east_west) 
    :north_south(north_south), east_west(east_west) {}