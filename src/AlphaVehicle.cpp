#include "AlphaVehicle.h"

AlphaVehicle::AlphaVehicle(int id)
    : Vehicle(id,           // id
              120,          // cruiseSpeed: 120 mph
              320.0,        // batteryCapacity: 320 kWh
              1.6,          // energyPerMile: 1.6 kWh/mile
              0.6,          // chargeTime: 0.6 hours
              4,            // passengerCount: 4
              0.25)         // faultProbability: 0.25
{
}

AlphaVehicle::~AlphaVehicle() {
}

VehicleType AlphaVehicle::getVehicleType() const {
    return VehicleType::ALPHA;
}
