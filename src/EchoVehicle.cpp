#include "EchoVehicle.h"

EchoVehicle::EchoVehicle(int id)
    : Vehicle(id,           // id
              30,           // cruiseSpeed: 30 mph
              150.0,        // batteryCapacity: 150 kWh
              5.8,          // energyPerMile: 5.8 kWh/mile
              0.3,          // chargeTime: 0.3 hours
              2,            // passengerCount: 2
              0.61)         // faultProbability: 0.61
{
}

EchoVehicle::~EchoVehicle() {
}

VehicleType EchoVehicle::getVehicleType() const {
    return VehicleType::ECHO;
}
