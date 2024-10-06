#include "Aerobody.h"
#include "VelocityVector.hpp"





ApparentWindVector Aerobody::get_wind(const VelocityVector& reported_wind, const VelocityVector& car_velocity) {

    double x_vector_sum = car_velocity.get_north_south() + reported_wind.get_north_south();
    double y_vector_sum = car_velocity.get_east_west() + reported_wind.get_east_west();

    VelocityVector v = VelocityVector::from_cartesian_components(x_vector_sum, y_vector_sum); //look into further

    double yaw = car_velocity.angle_between(v);
    double speed = v.get_magnitude();

    return ApparentWindVector{speed, yaw};
}

double Aerobody::aerodynamic_drag(const ApparentWindVector& apparent_wind, double air_density) const {

    double vel = apparent_wind.speed * std::abs(cos(apparent_wind.yaw));
    return (1.0/2) * drag_coefficient * frontal_area * vel * vel * air_density;
    // return 0.0;
    
    //D = 0.5 * rho * V^2 * A * Cd Aerodynamic Drag formula
}