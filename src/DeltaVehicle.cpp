#include "DeltaVehicle.h"

DeltaVehicle::DeltaVehicle(int id)
    : Vehicle(id,           // id
              90,           // cruiseSpeed: 90 mph
              120.0,        // batteryCapacity: 120 kWh
              0.8,          // energyPerMile: 0.8 kWh/mile
              0.62,         // chargeTime: 0.62 hours
              2,            // passengerCount: 2
              0.22)         // faultProbability: 0.22
{
}

DeltaVehicle::~DeltaVehicle() {
}

VehicleType DeltaVehicle::getVehicleType() const {
    return VehicleType::DELTA;
}
