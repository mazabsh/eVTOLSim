#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include "Vehicle.h"
#include "ChargerManager.h"
#include "StatisticsManager.h"
#include "Event.h"
#include <vector>
#include <string>
#include <queue>

/**
 * @class SimulationController
 * @brief Central class that runs the simulation using event-driven approach
 * 
 * Responsibilities:
 * - Create vehicles
 * - Manage priority queue of events
 * - Process events in chronological order
 * - Collect statistics
 */
class SimulationController {
private:
    std::vector<Vehicle*> vehicles;
    ChargerManager chargerManager;
    StatisticsManager statsManager;
    std::priority_queue<Event, std::vector<Event>, EventComparator> eventQueue;
    double currentTime;           // Current simulation time in hours
    double simulationDuration;    // Total simulation duration in hours
    
    // Statistics
    double totalFlightTime;
    double totalDistance;
    double totalPassengerMiles;
    int totalFaults;
    int totalFlights;

public:
    /**
     * @brief Constructor
     * @param numVehicles Number of vehicles to create
     * @param numChargers Number of chargers (default: 3)
     * @param duration Simulation duration in hours
     * @param timeStep Simulation time step in hours
     */
    SimulationController(int numVehicles, int numChargers = 3, 
                        double duration = 24.0, double timeStep = 0.1);
    
    /**
     * @brief Destructor
     */
    ~SimulationController();
    
    /**
     * @brief Run the simulation
     */
    void run();
    
    /**
     * @brief Print simulation results
     */
    void printResults() const;
    
    /**
     * @brief Get total flight time
     */
    double getTotalFlightTime() const;
    
    /**
     * @brief Get total distance
     */
    double getTotalDistance() const;
    
    /**
     * @brief Get total passenger miles
     */
    double getTotalPassengerMiles() const;
    
    /**
     * @brief Get total faults
     */
    int getTotalFaults() const;
    
    /**
     * @brief Get simulation time
     */
    double getCurrentTime() const;
    
private:
    /**
     * @brief Initialize vehicles
     */
    void initializeVehicles(int numVehicles);
    
    /**
     * @brief Process one simulation step
     */
    void processStep();
    
    /**
     * @brief Update vehicle statistics
     */
    void updateStatistics();
};

#endif // SIMULATIONCONTROLLER_H
