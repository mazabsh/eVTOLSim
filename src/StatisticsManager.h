#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <string>
#include <map>

/**
 * @struct Stats
 * @brief Statistics for a vehicle type
 */
struct Stats {
    int totalFlights;
    double totalFlightTime;
    double totalDistance;
    int chargeSessions;
    double totalChargeTime;
    int totalFaults;
    double passengerMiles;
    
    // Constructor to initialize to zero
    Stats() : totalFlights(0), totalFlightTime(0.0), totalDistance(0.0),
              chargeSessions(0), totalChargeTime(0.0), totalFaults(0), passengerMiles(0.0) {}
};

/**
 * @enum VehicleType
 * @brief Types of vehicles in the fleet
 */
enum class VehicleType {
    ALPHA,
    BRAVO,
    CHARLIE,
    DELTA,
    ECHO,
    UNKNOWN
};

/**
 * @class StatisticsManager
 * @brief Keeps statistics per vehicle type
 * 
 * Responsibilities:
 * - Record flight, charge, fault, and passenger miles data per vehicle type
 * - Compute averages
 */
class StatisticsManager {
private:
    std::map<VehicleType, Stats> statsMap;

public:
    /**
     * @brief Constructor
     */
    StatisticsManager();
    
    /**
     * @brief Destructor
     */
    ~StatisticsManager();
    
    /**
     * @brief Record flight data for a vehicle type
     * @param type Vehicle type
     * @param flightTime Flight time in hours
     * @param distance Distance in miles
     */
    void recordFlight(VehicleType type, double flightTime, double distance);
    
    /**
     * @brief Record charge session for a vehicle type
     * @param type Vehicle type
     * @param chargeTime Charging time in hours
     */
    void recordCharge(VehicleType type, double chargeTime);
    
    /**
     * @brief Record fault for a vehicle type
     * @param type Vehicle type
     */
    void recordFault(VehicleType type);
    
    /**
     * @brief Record passenger miles for a vehicle type
     * @param type Vehicle type
     * @param miles Passenger miles
     */
    void recordPassengerMiles(VehicleType type, double miles);
    
    /**
     * @brief Get stats for a vehicle type
     * @param type Vehicle type
     * @return Stats reference
     */
    const Stats& getStats(VehicleType type) const;
    
    /**
     * @brief Print statistics for all vehicle types
     */
    void printStatistics() const;
    
    /**
     * @brief Get vehicle type name as string
     * @param type Vehicle type
     * @return String representation
     */
    static std::string getTypeName(VehicleType type);
    
    /**
     * @brief Compute and print averages
     */
    void computeAverages() const;
};

#endif // STATISTICSMANAGER_H
