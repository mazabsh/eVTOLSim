#include <iostream>
#include <cassert>
#include "ChargerManager.h"
#include "AlphaVehicle.h"

void testChargerManagerCreation() {
    std::cout << "Testing ChargerManager creation..." << std::endl;
    
    ChargerManager manager(3);
    assert(manager.getTotalChargers() == 3);
    assert(manager.getAvailableChargers() == 3);
    assert(manager.getQueueSize() == 0);
    
    std::cout << "  PASSED: ChargerManager creation" << std::endl;
}

void testRequestCharger() {
    std::cout << "Testing requestCharger..." << std::endl;
    
    ChargerManager manager(3);
    AlphaVehicle v1(1);
    AlphaVehicle v2(2);
    
    // First vehicle gets charger immediately
    bool result1 = manager.requestCharger(&v1);
    assert(result1 == true);
    assert(manager.getAvailableChargers() == 2);
    assert(manager.getQueueSize() == 0);
    
    // Second vehicle gets charger immediately
    bool result2 = manager.requestCharger(&v2);
    assert(result2 == true);
    assert(manager.getAvailableChargers() == 1);
    
    std::cout << "  PASSED: requestCharger" << std::endl;
}

void testChargerQueue() {
    std::cout << "Testing charger queue..." << std::endl;
    
    ChargerManager manager(1);  // Only 1 charger
    AlphaVehicle v1(1);
    AlphaVehicle v2(2);
    AlphaVehicle v3(3);
    
    // First vehicle gets charger
    bool result1 = manager.requestCharger(&v1);
    assert(result1 == true);
    assert(manager.getAvailableChargers() == 0);
    
    // Second vehicle goes to queue
    bool result2 = manager.requestCharger(&v2);
    assert(result2 == false);
    assert(manager.getQueueSize() == 1);
    
    // Third vehicle goes to queue
    bool result3 = manager.requestCharger(&v3);
    assert(result3 == false);
    assert(manager.getQueueSize() == 2);
    
    std::cout << "  PASSED: charger queue" << std::endl;
}

void testReleaseCharger() {
    std::cout << "Testing releaseCharger..." << std::endl;
    
    ChargerManager manager(2);
    AlphaVehicle v1(1);
    AlphaVehicle v2(2);
    
    manager.requestCharger(&v1);
    manager.requestCharger(&v2);
    assert(manager.getAvailableChargers() == 0);
    
    // Release one charger
    manager.releaseCharger(&v1);
    assert(manager.getAvailableChargers() == 1);
    
    std::cout << "  PASSED: releaseCharger" << std::endl;
}

void testAssignNextVehicle() {
    std::cout << "Testing assignNextVehicle..." << std::endl;
    
    ChargerManager manager(1);  // Only 1 charger
    AlphaVehicle v1(1);
    AlphaVehicle v2(2);
    
    // First vehicle takes the charger
    manager.requestCharger(&v1);
    assert(manager.getAvailableChargers() == 0);
    
    // Second vehicle waits in queue
    manager.requestCharger(&v2);
    assert(manager.getQueueSize() == 1);
    
    // Release first vehicle - this should auto-assign next vehicle
    manager.releaseCharger(&v1);
    
    // After release, v2 should be assigned automatically
    // and queue should be empty
    assert(manager.getQueueSize() == 0);
    assert(manager.getAvailableChargers() == 0);  // Charger now taken by v2
    
    // v2 should now be charging
    assert(v2.getState() == VehicleState::CHARGING);
    
    std::cout << "  PASSED: assignNextVehicle" << std::endl;
}

void testHasWaitingVehicles() {
    std::cout << "Testing hasWaitingVehicles..." << std::endl;
    
    ChargerManager manager(1);
    AlphaVehicle v1(1);
    AlphaVehicle v2(2);
    
    manager.requestCharger(&v1);
    assert(manager.hasWaitingVehicles() == false);
    
    manager.requestCharger(&v2);
    assert(manager.hasWaitingVehicles() == true);
    
    manager.releaseCharger(&v1);
    manager.assignNextVehicle();
    assert(manager.hasWaitingVehicles() == false);
    
    std::cout << "  PASSED: hasWaitingVehicles" << std::endl;
}

int main() {
    std::cout << "=== Running ChargerManager Unit Tests ===" << std::endl << std::endl;
    
    testChargerManagerCreation();
    testRequestCharger();
    testChargerQueue();
    testReleaseCharger();
    testAssignNextVehicle();
    testHasWaitingVehicles();
    
    std::cout << std::endl << "=== All tests passed! ===" << std::endl;
    
    return 0;
}
