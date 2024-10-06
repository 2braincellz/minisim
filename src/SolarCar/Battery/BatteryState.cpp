#include "BatteryState.h"
#include<iostream>

void BatteryState::update_energy_remaining(double delta_energy) {

    energy_remaining  = energy_remaining + delta_energy;
}
