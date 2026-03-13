#include "StatisticsManager.h"
#include <iostream>
#include <iomanip>

StatisticsManager::StatisticsManager() {
    // Initialize all vehicle types
    statsMap[VehicleType::ALPHA] = Stats();
    statsMap[VehicleType::BRAVO] = Stats();
    statsMap[VehicleType::CHARLIE] = Stats();
    statsMap[VehicleType::DELTA] = Stats();
    statsMap[VehicleType::ECHO] = Stats();
}

StatisticsManager::~StatisticsManager() {
}

void StatisticsManager::recordFlight(VehicleType type, double flightTime, double distance) {
    if (flightTime > 0.0) {
        statsMap[type].totalFlights++;
        statsMap[type].totalFlightTime += flightTime;
    }
    if (distance > 0.0) {
        statsMap[type].totalDistance += distance;
    }
}

void StatisticsManager::recordCharge(VehicleType type, double chargeTime) {
    if (chargeTime > 0.0) {
        statsMap[type].chargeSessions++;
        statsMap[type].totalChargeTime += chargeTime;
    }
}

void StatisticsManager::recordFault(VehicleType type) {
    statsMap[type].totalFaults++;
}

void StatisticsManager::recordPassengerMiles(VehicleType type, double miles) {
    if (miles > 0.0) {
        statsMap[type].passengerMiles += miles;
    }
}

const Stats& StatisticsManager::getStats(VehicleType type) const {
    static Stats emptyStats;
    auto it = statsMap.find(type);
    if (it != statsMap.end()) {
        return it->second;
    }
    return emptyStats;
}

std::string StatisticsManager::getTypeName(VehicleType type) {
    switch (type) {
        case VehicleType::ALPHA: return "Alpha";
        case VehicleType::BRAVO: return "Bravo";
        case VehicleType::CHARLIE: return "Charlie";
        case VehicleType::DELTA: return "Delta";
        case VehicleType::ECHO: return "Echo";
        default: return "Unknown";
    }
}

void StatisticsManager::printStatistics() const {
    std::cout << "========================================" << std::endl;
    std::cout << "    Statistics by Vehicle Type          " << std::endl;
    std::cout << "========================================" << std::endl;
    
    for (auto const& pair : statsMap) {
        VehicleType type = pair.first;
        const Stats& stats = pair.second;
        
        std::cout << getTypeName(type) << ":" << std::endl;
        std::cout << "  Total Flights: " << stats.totalFlights << std::endl;
        std::cout << "  Total Flight Time: " << std::fixed << std::setprecision(1) 
                  << stats.totalFlightTime << " hours" << std::endl;
        std::cout << "  Total Distance: " << stats.totalDistance << " miles" << std::endl;
        std::cout << "  Charge Sessions: " << stats.chargeSessions << std::endl;
        std::cout << "  Total Charge Time: " << stats.totalChargeTime << " hours" << std::endl;
        std::cout << "  Total Faults: " << stats.totalFaults << std::endl;
        std::cout << "  Passenger-Miles: " << stats.passengerMiles << std::endl;
        std::cout << std::endl;
    }
    
    computeAverages();
}

void StatisticsManager::computeAverages() const {
    std::cout << "--- Averages ---" << std::endl;
    
    // Calculate fleet-wide totals
    int totalFlights = 0;
    double totalFlightTime = 0.0;
    double totalDistance = 0.0;
    int totalChargeSessions = 0;
    double totalChargeTime = 0.0;
    int totalFaults = 0;
    double totalPassengerMiles = 0.0;
    
    for (auto const& pair : statsMap) {
        const Stats& stats = pair.second;
        totalFlights += stats.totalFlights;
        totalFlightTime += stats.totalFlightTime;
        totalDistance += stats.totalDistance;
        totalChargeSessions += stats.chargeSessions;
        totalChargeTime += stats.totalChargeTime;
        totalFaults += stats.totalFaults;
        totalPassengerMiles += stats.passengerMiles;
    }
    
    // Calculate averages per vehicle type
    for (auto const& pair : statsMap) {
        VehicleType type = pair.first;
        const Stats& stats = pair.second;
        
        double avgFlightTime = (stats.totalFlights > 0) ? 
            stats.totalFlightTime / stats.totalFlights : 0.0;
        double avgDistance = (stats.totalFlights > 0) ? 
            stats.totalDistance / stats.totalFlights : 0.0;
        double avgChargeTime = (stats.chargeSessions > 0) ? 
            stats.totalChargeTime / stats.chargeSessions : 0.0;
        double avgPassengerMiles = (stats.totalFlights > 0) ? 
            stats.passengerMiles / stats.totalFlights : 0.0;
        
        std::cout << getTypeName(type) << " Average:" << std::endl;
        std::cout << "  Avg Flight Time: " << std::fixed << std::setprecision(1) 
                  << avgFlightTime << " hours" << std::endl;
        std::cout << "  Avg Distance: " << avgDistance << " miles" << std::endl;
        std::cout << "  Avg Charge Time: " << avgChargeTime << " hours" << std::endl;
        std::cout << "  Avg Passenger-Miles: " << avgPassengerMiles << std::endl;
        std::cout << std::endl;
    }
    
    // Fleet-wide averages
    double fleetAvgFlightTime = (totalFlights > 0) ? totalFlightTime / totalFlights : 0.0;
    double fleetAvgDistance = (totalFlights > 0) ? totalDistance / totalFlights : 0.0;
    double fleetAvgChargeTime = (totalChargeSessions > 0) ? totalChargeTime / totalChargeSessions : 0.0;
    double fleetAvgPassengerMiles = (totalFlights > 0) ? totalPassengerMiles / totalFlights : 0.0;
    
    std::cout << "Fleet Average:" << std::endl;
    std::cout << "  Avg Flight Time: " << std::fixed << std::setprecision(1) 
              << fleetAvgFlightTime << " hours" << std::endl;
    std::cout << "  Avg Distance: " << fleetAvgDistance << " miles" << std::endl;
    std::cout << "  Avg Charge Time: " << fleetAvgChargeTime << " hours" << std::endl;
    std::cout << "  Avg Passenger-Miles: " << fleetAvgPassengerMiles << std::endl;
    std::cout << "========================================" << std::endl;
}
