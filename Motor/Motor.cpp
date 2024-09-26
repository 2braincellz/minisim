#include "Motor.h"

double Motor::power_consumed(double angular_speed, double torque) const {
    return (angular_speed * torque) + (angular_speed * eddy_current_loss_coefficient) + hysteresis_loss;
}



