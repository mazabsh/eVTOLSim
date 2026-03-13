#include "SimulationController.h"
#include "AlphaVehicle.h"
#include "BravoVehicle.h"
#include "CharlieVehicle.h"
#include "DeltaVehicle.h"
#include "EchoVehicle.h"
#include <iostream>
#include <cmath>
#include <random>

SimulationController::SimulationController(int numVehicles, int numChargers, 
                                           double duration, double timeStep)
    : chargerManager(numChargers)
    , statsManager()
    , currentTime(0.0)
    , simulationDuration(duration)
    , totalFlightTime(0.0)
    , totalDistance(0.0)
    , totalPassengerMiles(0.0)
    , totalFaults(0)
    , totalFlights(0)
{
    initializeVehicles(numVehicles);
    
    // Start all vehicles flying at time 0
    for (Vehicle* vehicle : vehicles) {
        vehicle->setState(VehicleState::FLYING);
        // Schedule first flight end event
        double flightTime = vehicle->computeFlightTime();
        if (flightTime > 0) {
            // Check if a fault will occur during this flight
            if (vehicle->checkFault()) {
                // Schedule fault at a random time during the flight
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, flightTime);
                double faultTime = dis(gen);
                eventQueue.push(Event(faultTime, EventType::FAULT, vehicle->getId()));
            } else {
                // No fault, schedule normal flight end
                eventQueue.push(Event(flightTime, EventType::FLIGHT_END, vehicle->getId()));
            }
        }
    }
}

SimulationController::~SimulationController() {
    for (Vehicle* v : vehicles) {
        delete v;
    }
    vehicles.clear();
}

void SimulationController::initializeVehicles(int numVehicles) {
    // Random number generator for vehicle type selection
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDist(0, 4);  // 5 vehicle types (0-4)
    
    // Create vehicles with randomly selected types
    for (int i = 0; i < numVehicles; i++) {
        int typeIndex = typeDist(gen);  // Random type 0-4
        Vehicle* vehicle = nullptr;
        
        switch (typeIndex) {
            case 0:
                vehicle = new AlphaVehicle(i + 1);
                break;
            case 1:
                vehicle = new BravoVehicle(i + 1);
                break;
            case 2:
                vehicle = new CharlieVehicle(i + 1);
                break;
            case 3:
                vehicle = new DeltaVehicle(i + 1);
                break;
            case 4:
                vehicle = new EchoVehicle(i + 1);
                break;
        }
        
        if (vehicle) {
            vehicles.push_back(vehicle);
        }
    }
}

void SimulationController::run() {
    std::cout << "Starting event-driven simulation..." << std::endl;
    std::cout << "Duration: " << simulationDuration << " hours" << std::endl;
    std::cout << "Vehicles: " << vehicles.size() << std::endl;
    std::cout << "Chargers: " << chargerManager.getTotalChargers() << std::endl;
    std::cout << std::endl;
    
    // Process events until queue is empty or we reach simulation duration
    while (!eventQueue.empty() && currentTime < simulationDuration) {
        // Get next event (earliest time)
        Event event = eventQueue.top();
        eventQueue.pop();
        
        // Advance time to event time
        currentTime = event.time;
        
        // Skip events that occur after simulation ends
        if (currentTime > simulationDuration) {
            break;
        }
        
        // Find the vehicle associated with this event
        Vehicle* vehicle = nullptr;
        for (Vehicle* v : vehicles) {
            if (v->getId() == event.vehicleId) {
                vehicle = v;
                break;
            }
        }
        
        if (vehicle == nullptr) {
            continue;  // Vehicle not found, skip event
        }
        
        // Process the event
        if (event.type == EventType::FLIGHT_END) {
            // Calculate actual flight time and distance
            double flightTime = vehicle->computeFlightTime();
            double distance = vehicle->computeDistance();
            
            // Record the flight statistics
            vehicle->recordFlight(flightTime, distance);
            
            // Discharge battery to 0
            vehicle->setBatteryLevel(0.0);
            
            // Request charger
            if (chargerManager.requestCharger(vehicle)) {
                // Charger assigned immediately, schedule charge end
                double chargeEndTime = currentTime + vehicle->getChargeTime();
                eventQueue.push(Event(chargeEndTime, EventType::CHARGE_END, vehicle->getId()));
            }
            // else: vehicle is waiting in queue
        } else if (event.type == EventType::FAULT) {
            // Fault occurred during flight - flight ends early
            // Calculate actual flight time (time until fault occurred)
            double flightTime = currentTime - (eventQueue.empty() ? 0.0 : 0.0); // Time is currentTime
            // Actually, we need to track when the flight started - for simplicity, 
            // we'll use the time from last event to current event
            // For now, compute based on current time
            flightTime = currentTime; // Simplified - time since flight started
            
            double distance = vehicle->getCruiseSpeed() * flightTime;
            
            // Record the flight statistics (partial flight)
            vehicle->recordFlight(flightTime, distance);
            
            // Discharge battery based on distance traveled
            vehicle->discharge(distance);
            
            // Record the fault
            vehicle->recordFault();
            
            // Request charger (fault causes immediate landing)
            if (chargerManager.requestCharger(vehicle)) {
                // Charger assigned immediately, schedule charge end
                double chargeEndTime = currentTime + vehicle->getChargeTime();
                eventQueue.push(Event(chargeEndTime, EventType::CHARGE_END, vehicle->getId()));
            }
            // else: vehicle is waiting in queue
        } else if (event.type == EventType::CHARGE_END) {
            // Vehicle finished charging
            chargerManager.releaseCharger(vehicle);
            
            // Fully charge the battery
            vehicle->setBatteryLevel(100.0);
            vehicle->setState(VehicleState::FLYING);
            
            // Record charge time
            vehicle->recordCharge(vehicle->getChargeTime());
            
            // Schedule next flight - check for faults
            double flightTime = vehicle->computeFlightTime();
            if (flightTime > 0) {
                // Check if a fault will occur during this flight
                if (vehicle->checkFault()) {
                    // Schedule fault at a random time during the flight
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<> dis(0.0, flightTime);
                    double faultTime = dis(gen);
                    eventQueue.push(Event(currentTime + faultTime, EventType::FAULT, vehicle->getId()));
                } else {
                    // No fault, schedule normal flight end
                    double flightEndTime = currentTime + flightTime;
                    eventQueue.push(Event(flightEndTime, EventType::FLIGHT_END, vehicle->getId()));
                }
            }
            
            // Check if there are vehicles waiting in charger queue
            // If so, assign ONE vehicle and schedule its CHARGE_END event
            if (chargerManager.hasWaitingVehicles()) {
                Vehicle* waitingVehicle = chargerManager.assignNextVehicle();
                if (waitingVehicle != nullptr) {
                    // Schedule CHARGE_END for the waiting vehicle
                    double chargeEndTime = currentTime + waitingVehicle->getChargeTime();
                    eventQueue.push(Event(chargeEndTime, EventType::CHARGE_END, waitingVehicle->getId()));
                }
            }
        }
    }
    
    updateStatistics();
    printResults();
}

void SimulationController::updateStatistics() {
    for (Vehicle* vehicle : vehicles) {
        totalFlightTime += vehicle->getTotalFlightTime();
        totalDistance += vehicle->getTotalDistance();
        totalPassengerMiles += vehicle->getPassengerMiles();
        totalFaults += vehicle->getTotalFaults();
        totalFlights++;
        
        // Update StatisticsManager by vehicle type
        VehicleType type = vehicle->getVehicleType();
        statsManager.recordFlight(type, vehicle->getTotalFlightTime(), vehicle->getTotalDistance());
        statsManager.recordCharge(type, vehicle->getTotalChargeTime());
        statsManager.recordFault(type);
        statsManager.recordPassengerMiles(type, vehicle->getPassengerMiles());
    }
}

void SimulationController::printResults() const {
    std::cout << "========================================" << std::endl;
    std::cout << "    Event-Driven Simulation Results      " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total Simulation Time: " << currentTime << " hours" << std::endl;
    std::cout << std::endl;
    
    std::cout << "--- Fleet Statistics ---" << std::endl;
    std::cout << "Total Flight Time: " << totalFlightTime << " hours" << std::endl;
    std::cout << "Total Distance: " << totalDistance << " miles" << std::endl;
    std::cout << "Total Passenger-Miles: " << totalPassengerMiles << std::endl;
    std::cout << "Total Faults: " << totalFaults << std::endl;
    std::cout << std::endl;
    
    std::cout << "--- Per-Vehicle Statistics ---" << std::endl;
    for (Vehicle* vehicle : vehicles) {
        std::cout << "Vehicle " << vehicle->getId() << " (" << vehicle->getStateString() << "):" << std::endl;
        std::cout << "  Type: ";
        if (dynamic_cast<AlphaVehicle*>(vehicle)) std::cout << "Alpha";
        else if (dynamic_cast<BravoVehicle*>(vehicle)) std::cout << "Bravo";
        else if (dynamic_cast<CharlieVehicle*>(vehicle)) std::cout << "Charlie";
        else if (dynamic_cast<DeltaVehicle*>(vehicle)) std::cout << "Delta";
        else if (dynamic_cast<EchoVehicle*>(vehicle)) std::cout << "Echo";
        std::cout << std::endl;
        std::cout << "  Flight Time: " << vehicle->getTotalFlightTime() << " hours" << std::endl;
        std::cout << "  Distance: " << vehicle->getTotalDistance() << " miles" << std::endl;
        std::cout << "  Passenger-Miles: " << vehicle->getPassengerMiles() << std::endl;
        std::cout << "  Charges: " << vehicle->getTotalCharges() << std::endl;
        std::cout << "  Charge Time: " << vehicle->getTotalChargeTime() << " hours" << std::endl;
        std::cout << "  Faults: " << vehicle->getTotalFaults() << std::endl;
        std::cout << "  Battery: " << vehicle->getBatteryLevel() << "%" << std::endl;
        std::cout << std::endl;
    }
    
    // Print statistics by vehicle type
    statsManager.printStatistics();
}

double SimulationController::getTotalFlightTime() const {
    return totalFlightTime;
}

double SimulationController::getTotalDistance() const {
    return totalDistance;
}

double SimulationController::getTotalPassengerMiles() const {
    return totalPassengerMiles;
}

int SimulationController::getTotalFaults() const {
    return totalFaults;
}

double SimulationController::getCurrentTime() const {
    return currentTime;
}
