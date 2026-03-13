#include "BravoVehicle.h"

BravoVehicle::BravoVehicle(int id)
    : Vehicle(id,           // id
              100,          // cruiseSpeed: 100 mph
              100.0,        // batteryCapacity: 100 kWh
              1.5,          // energyPerMile: 1.5 kWh/mile
              0.2,          // chargeTime: 0.2 hours
              5,            // passengerCount: 5
              0.10)         // faultProbability: 0.10
{
}

BravoVehicle::~BravoVehicle() {
}

VehicleType BravoVehicle::getVehicleType() const {
    return VehicleType::BRAVO;
}
