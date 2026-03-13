#include "CharlieVehicle.h"

CharlieVehicle::CharlieVehicle(int id)
    : Vehicle(id,           // id
              160,          // cruiseSpeed: 160 mph
              220.0,        // batteryCapacity: 220 kWh
              2.2,          // energyPerMile: 2.2 kWh/mile
              0.8,          // chargeTime: 0.8 hours
              3,            // passengerCount: 3
              0.05)         // faultProbability: 0.05
{
}

CharlieVehicle::~CharlieVehicle() {
}

VehicleType CharlieVehicle::getVehicleType() const {
    return VehicleType::CHARLIE;
}
