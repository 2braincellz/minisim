#include "RaceSegmentRunner.h"
#include "RaceConfig/Route/RouteSegment.h"
#include "SolarCar/Aerobody/Aerobody.h"
#include "SolarCar/Aerobody/VelocityVector.h"

#include <cmath>
#include <iostream>
#include <optional>
// #include "RaceConfig/Route/RouteSegment.h"
// #include "RaceConfig/Weather/WeatherDataPoint.h"
// #include "SolarCar/SolarCar.h"

double RaceSegmentRunner::calculate_resistive_force(const RouteSegment & route_segment, const WeatherDataPoint& weather_data, double speed) const {
    
    VelocityVector car_velocity = VelocityVector::from_polar_components(speed, route_segment.heading);
    ApparentWindVector wind = Aerobody::get_wind(weather_data.wind, car_velocity);
    double car_force_gravity = car.mass * route_segment.gravity;
    double const aero_res_force = car.aerobody.aerodynamic_drag(wind, weather_data.air_density);
    double tire_res_force = car.tire.rolling_resistance(car_force_gravity, speed);
    double gravity_res_force = route_segment.gravity_times_sine_road_incline_angle  * car.mass;

    return aero_res_force + tire_res_force + gravity_res_force;
}

double RaceSegmentRunner::calculate_power_out(const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double speed) const {

   const double angular_speed = speed/car.wheel_radius;
   const double torque = car.wheel_radius * calculate_resistive_force(route_segment, weather_data, speed);
   return car.motor.power_consumed(angular_speed, torque);
}

double RaceSegmentRunner::calculate_power_in(const RouteSegment& route_segment, const WeatherDataPoint& weather_data) const {
    
    double irr = weather_data.irradiance;

    double power_in = car.array.power_in(irr);

    static_cast<void>(route_segment);

    return power_in;
}

std::optional<double> RaceSegmentRunner::calculate_power_net(const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double state_of_charge, double speed) const{
    double power_out = calculate_power_out(route_segment, weather_data, speed);
    double power_in = calculate_power_in(route_segment, weather_data);
    double power_demanded = power_in - power_out;
    std::optional<double> net_power = car.battery.power_loss(-power_demanded, state_of_charge);

    if (net_power == std::nullopt) {
        return net_power;
    }

    return power_demanded - *net_power;
}

