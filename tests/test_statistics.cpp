#include <iostream>
#include <cassert>
#include "StatisticsManager.h"

void testStatisticsManagerCreation() {
    std::cout << "Testing StatisticsManager creation..." << std::endl;
    
    StatisticsManager stats;
    // Just verify it can be created
    std::cout << "  PASSED: StatisticsManager creation" << std::endl;
}

void testRecordFlight() {
    std::cout << "Testing recordFlight..." << std::endl;
    
    StatisticsManager stats;
    stats.recordFlight(VehicleType::ALPHA, 1.5, 180.0);
    stats.recordFlight(VehicleType::ALPHA, 2.0, 240.0);
    
    // This should not crash
    std::cout << "  PASSED: recordFlight" << std::endl;
}

void testRecordCharge() {
    std::cout << "Testing recordCharge..." << std::endl;
    
    StatisticsManager stats;
    stats.recordCharge(VehicleType::BRAVO, 0.5);
    stats.recordCharge(VehicleType::BRAVO, 0.3);
    
    std::cout << "  PASSED: recordCharge" << std::endl;
}

void testRecordFault() {
    std::cout << "Testing recordFault..." << std::endl;
    
    StatisticsManager stats;
    stats.recordFault(VehicleType::CHARLIE);
    stats.recordFault(VehicleType::CHARLIE);
    stats.recordFault(VehicleType::CHARLIE);
    
    std::cout << "  PASSED: recordFault" << std::endl;
}

void testRecordPassengerMiles() {
    std::cout << "Testing recordPassengerMiles..." << std::endl;
    
    StatisticsManager stats;
    stats.recordPassengerMiles(VehicleType::DELTA, 500.0);
    stats.recordPassengerMiles(VehicleType::DELTA, 300.0);
    
    std::cout << "  PASSED: recordPassengerMiles" << std::endl;
}

int main() {
    std::cout << "=== Running StatisticsManager Unit Tests ===" << std::endl << std::endl;
    
    testStatisticsManagerCreation();
    testRecordFlight();
    testRecordCharge();
    testRecordFault();
    testRecordPassengerMiles();
    
    std::cout << std::endl << "=== All tests passed! ===" << std::endl;
    
    return 0;
}
