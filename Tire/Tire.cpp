#include "Tire.h"
#include <iostream>
#include <cmath>

double Tire::rolling_resistance(double tire_load, double vehicle_speed, std::optional<double> tire_pressure) const {

    double vehicle_speed_km_h = (vehicle_speed / 1000) * 3600; 

    double rolling_res = std::pow(tire_pressure.value_or(tire_pressure_at_stc), alpha) * std::pow(tire_load, beta) * (a + (b * vehicle_speed_km_h) + (c * std::pow(vehicle_speed_km_h, 2)));

    return rolling_res;

}

