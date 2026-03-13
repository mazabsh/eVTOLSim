#include "ChargerManager.h"

ChargerManager::ChargerManager(int numChargers)
    : totalChargers(numChargers)
    , availableChargers(numChargers)
{
}

ChargerManager::~ChargerManager() {
}

bool ChargerManager::requestCharger(Vehicle* vehicle) {
    if (vehicle == nullptr) {
        return false;
    }
    
    if (availableChargers > 0) {
        // Assign charger immediately
        availableChargers--;
        chargingVehicles.push_back(vehicle);
        vehicle->setState(VehicleState::CHARGING);
        return true;
    } else {
        // Add to queue
        waitingQueue.push(vehicle);
        vehicle->setState(VehicleState::WAITING_FOR_CHARGER);
        return false;
    }
}

void ChargerManager::releaseCharger(Vehicle* vehicle) {
    if (vehicle == nullptr) {
        return;
    }
    
    // Remove from charging vehicles
    for (auto it = chargingVehicles.begin(); it != chargingVehicles.end(); ++it) {
        if (*it == vehicle) {
            chargingVehicles.erase(it);
            break;
        }
    }
    
    availableChargers++;
    
    // Try to assign next vehicle from queue
    assignNextVehicle();
}

Vehicle* ChargerManager::assignNextVehicle() {
    if (!waitingQueue.empty() && availableChargers > 0) {
        Vehicle* vehicle = waitingQueue.front();
        waitingQueue.pop();
        
        availableChargers--;
        chargingVehicles.push_back(vehicle);
        vehicle->setState(VehicleState::CHARGING);
        
        return vehicle;
    }
    return nullptr;
}

int ChargerManager::getAvailableChargers() const {
    return availableChargers;
}

int ChargerManager::getQueueSize() const {
    return static_cast<int>(waitingQueue.size());
}

int ChargerManager::getTotalChargers() const {
    return totalChargers;
}

bool ChargerManager::hasWaitingVehicles() const {
    return !waitingQueue.empty();
}

void ChargerManager::processCharging(double deltaTime) {
    // Process each vehicle currently charging. Currently not used,
    // designed for potential time-stepped simulation mode.
    for (Vehicle* vehicle : chargingVehicles) {
        if (vehicle != nullptr) {
            vehicle->charge(deltaTime);
            
            // Check if fully charged
            if (vehicle->getBatteryLevel() >= 100.0) {
                // Release the charger and vehicle goes back to flying
                releaseCharger(vehicle);
                vehicle->setState(VehicleState::FLYING);
            }
        }
    }
}
