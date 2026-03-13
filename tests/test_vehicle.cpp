#include <iostream>
#include <cassert>
#include "Vehicle.h"
#include "AlphaVehicle.h"
#include "BravoVehicle.h"
#include "CharlieVehicle.h"
#include "DeltaVehicle.h"
#include "EchoVehicle.h"

// Test Vehicle class
void testVehicleCreation() {
    std::cout << "Testing Vehicle creation..." << std::endl;
    
    AlphaVehicle vehicle(1);
    assert(vehicle.getId() == 1);
    assert(vehicle.getCruiseSpeed() == 120);
    assert(vehicle.getBatteryCapacity() == 320);
    assert(vehicle.getEnergyPerMile() == 1.6);
    assert(vehicle.getChargeTime() == 0.6);
    assert(vehicle.getPassengerCount() == 4);
    
    std::cout << "  PASSED: Vehicle creation" << std::endl;
}

void testFlightTimeCalculation() {
    std::cout << "Testing flight time calculation..." << std::endl;
    
    AlphaVehicle vehicle(1);
    double flightTime = vehicle.computeFlightTime();
    
    // Flight time = battery / (energy per mile * speed)
    // 320 / (1.6 * 120) = 1.667 hours
    assert(flightTime > 1.6 && flightTime < 1.7);
    
    std::cout << "  PASSED: Flight time calculation" << std::endl;
}

void testDistanceCalculation() {
    std::cout << "Testing distance calculation..." << std::endl;
    
    AlphaVehicle vehicle(1);
    double distance = vehicle.computeDistance();
    
    // Distance = speed * flight time = 120 * 1.667 = 200 miles
    assert(distance > 199 && distance < 201);
    
    std::cout << "  PASSED: Distance calculation" << std::endl;
}

void testVehicleState() {
    std::cout << "Testing vehicle state transitions..." << std::endl;
    
    AlphaVehicle vehicle(1);
    
    assert(vehicle.getState() == VehicleState::FLYING);
    
    vehicle.setState(VehicleState::CHARGING);
    assert(vehicle.getState() == VehicleState::CHARGING);
    
    vehicle.setState(VehicleState::WAITING_FOR_CHARGER);
    assert(vehicle.getState() == VehicleState::WAITING_FOR_CHARGER);
    
    std::cout << "  PASSED: Vehicle state transitions" << std::endl;
}

void testRecordFlight() {
    std::cout << "Testing recordFlight..." << std::endl;
    
    AlphaVehicle vehicle(1);
    vehicle.recordFlight(1.5, 180.0);
    
    assert(vehicle.getTotalFlightTime() == 1.5);
    assert(vehicle.getTotalDistance() == 180.0);
    
    std::cout << "  PASSED: Record flight" << std::endl;
}

void testPassengerMiles() {
    std::cout << "Testing passenger miles..." << std::endl;
    
    AlphaVehicle vehicle(1);  // 4 passengers
    vehicle.recordFlight(1.0, 120.0);
    
    // Passenger miles = passengers * distance = 4 * 120 = 480
    assert(vehicle.getPassengerMiles() == 480.0);
    
    std::cout << "  PASSED: Passenger miles" << std::endl;
}

void testBravoVehicle() {
    std::cout << "Testing BravoVehicle..." << std::endl;
    
    BravoVehicle vehicle(1);
    
    assert(vehicle.getCruiseSpeed() == 100);
    assert(vehicle.getBatteryCapacity() == 100);
    assert(vehicle.getChargeTime() == 0.2);
    assert(vehicle.getPassengerCount() == 5);
    
    std::cout << "  PASSED: BravoVehicle properties" << std::endl;
}

void testCharlieVehicle() {
    std::cout << "Testing CharlieVehicle..." << std::endl;
    
    CharlieVehicle vehicle(1);
    
    assert(vehicle.getCruiseSpeed() == 160);
    assert(vehicle.getBatteryCapacity() == 220);
    assert(vehicle.getChargeTime() == 0.8);
    assert(vehicle.getPassengerCount() == 3);
    assert(vehicle.getFaultProbability() == 0.05);
    
    std::cout << "  PASSED: CharlieVehicle properties" << std::endl;
}

void testDeltaVehicle() {
    std::cout << "Testing DeltaVehicle..." << std::endl;
    
    DeltaVehicle vehicle(1);
    
    assert(vehicle.getCruiseSpeed() == 90);
    assert(vehicle.getBatteryCapacity() == 120);
    assert(vehicle.getChargeTime() == 0.62);
    assert(vehicle.getPassengerCount() == 2);
    assert(vehicle.getFaultProbability() == 0.22);
    
    std::cout << "  PASSED: DeltaVehicle properties" << std::endl;
}

void testEchoVehicle() {
    std::cout << "Testing EchoVehicle..." << std::endl;
    
    EchoVehicle vehicle(1);
    
    assert(vehicle.getCruiseSpeed() == 30);
    assert(vehicle.getBatteryCapacity() == 150);
    assert(vehicle.getChargeTime() == 0.3);
    assert(vehicle.getPassengerCount() == 2);
    assert(vehicle.getFaultProbability() == 0.61);
    
    std::cout << "  PASSED: EchoVehicle properties" << std::endl;
}

int main() {
    std::cout << "=== Running Vehicle Unit Tests ===" << std::endl << std::endl;
    
    testVehicleCreation();
    testFlightTimeCalculation();
    testDistanceCalculation();
    testVehicleState();
    testRecordFlight();
    testPassengerMiles();
    testBravoVehicle();
    testCharlieVehicle();
    testDeltaVehicle();
    testEchoVehicle();
    
    std::cout << std::endl << "=== All tests passed! ===" << std::endl;
    
    return 0;
}
