#include "Aerobody.h"
#include "VelocityVector.hpp"

ApparentWindVector Aerobody::get_wind(const VelocityVector& reported_wind, const VelocityVector& car_velocity) {
    double x_vector_sum = 0.0;
    double y_vector_sum = 0.0;

    return {0.0, 0.0};
}

double Aerobody::aerodynamic_drag(const ApparentWindVector& apparent_wind, double air_density) const {
    return 0.0;
}