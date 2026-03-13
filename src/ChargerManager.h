#ifndef CHARGERMANAGER_H
#define CHARGERMANAGER_H

#include "Vehicle.h"
#include <queue>
#include <vector>

/**
 * @class ChargerManager
 * @brief Manages charger resources and vehicle queue
 * 
 * Responsibilities:
 * - Track charger availability
 * - Maintain queue of waiting vehicles
 * - Assign chargers when available
 */
class ChargerManager {
private:
    int totalChargers;
    int availableChargers;
    std::queue<Vehicle*> waitingQueue;
    std::vector<Vehicle*> chargingVehicles;

public:
    /**
     * @brief Constructor
     * @param numChargers Number of available chargers (default: 3)
     */
    explicit ChargerManager(int numChargers = 3);
    
    /**
     * @brief Destructor
     */
    ~ChargerManager();
    
    /**
     * @brief Request a charger for a vehicle
     * @param vehicle Pointer to the vehicle requesting a charger
     * @return true if charger assigned immediately, false if queued
     */
    bool requestCharger(Vehicle* vehicle);
    
    /**
     * @brief Release a charger
     * @param vehicle Pointer to the vehicle releasing the charger
     */
    void releaseCharger(Vehicle* vehicle);
    
    /**
     * @brief Assign next vehicle from queue to available charger
     * @return Pointer to vehicle assigned, nullptr if queue empty
     */
    Vehicle* assignNextVehicle();
    
    /**
     * @brief Get number of available chargers
     * @return Number of available chargers
     */
    int getAvailableChargers() const;
    
    /**
     * @brief Get number of vehicles in queue
     * @return Queue size
     */
    int getQueueSize() const;
    
    /**
     * @brief Get total number of chargers
     * @return Total chargers
     */
    int getTotalChargers() const;
    
    /**
     * @brief Check if there are vehicles waiting
     * @return true if queue is not empty
     */
    bool hasWaitingVehicles() const;
    
    /**
     * @brief Process charging (called each simulation tick)
     * @param deltaTime Time elapsed in hours
     */
    void processCharging(double deltaTime);
};

#endif // CHARGERMANAGER_H
