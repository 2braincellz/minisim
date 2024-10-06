#include "Battery.h"
#include <cmath>

double Battery::state_of_charge(double energy_remaining) const {

    return energy_remaining/energy_capacity;
}

double Battery::current_voltage(double state_of_charge) const {

    double volt_diff = max_voltage - min_voltage;

    return  state_of_charge * volt_diff + min_voltage;
}

std::optional<double> Battery::power_loss(double net_power_demanded, double state_of_charge) const {

    double voltage = this->current_voltage(state_of_charge);
    
    if (std::pow(voltage, 2) + (4 * pack_resistance * net_power_demanded) < 0) {
        return std::nullopt;
    }

    double current = (((-1 * voltage) + std::sqrt(std::pow(voltage, 2) + (4 * pack_resistance * net_power_demanded)))/(2 * pack_resistance));

    return std::pow(current, 2) * pack_resistance;

}


