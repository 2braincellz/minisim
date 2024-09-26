#include <iostream>
#include "Array.h"

double Array::power_in(double irradiance) const {

    double power = irradiance * array_area * (array_efficiency/100);

    return power;
}