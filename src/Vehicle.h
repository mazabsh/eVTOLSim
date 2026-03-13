#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <random>
#include <stdexcept>
#include "StatisticsManager.h"

/**
 * @enum VehicleState
 * @brief Represents the possible states of a vehicle based on the state machine:
 *        Flying -> Waiting for Charger -> Charging -> Flying
 */
enum class VehicleState {
    FLYING,              // Vehicle is in flight
    WAITING_FOR_CHARGER,  // Battery empty, waiting for available charger
    CHARGING             // Vehicle is charging
};

/**
 * @class Vehicle
 * @brief Base class for all vehicle types in the Joby Aviation fleet
 * 
 * This class provides the foundation for various vehicle types including
 * AlphaVehicle, BravoVehicle, CharlieVehicle, DeltaVehicle, and EchoVehicle.
 */
class Vehicle {
protected:
    // Static properties
    int id;
    int cruiseSpeed;           // in mph
    double batteryCapacity;    // in kWh
    double energyPerMile;      // in kWh/mile
    double chargeTime;         // in hours
    int passengerCount;
    double faultProbability;   // probability of fault occurring (0.0 - 1.0)
    double batteryLevel;       // current battery level (0.0 - 100.0%)
    VehicleState state;
    
    // Dynamic tracking properties
    double totalFlightTime;    // total hours flown
    double totalDistance;      // total miles traveled
    int totalCharges;         // total number of charges
    double totalChargeTime;    // total hours spent charging
    int totalFaults;          // total number of faults
    double passengerMiles;    // total passenger-miles

public:
    /**
     * @brief Default constructor
     */
    Vehicle();

    /**
     * @brief Parameterized constructor
     * @param id Vehicle identification number
     * @param cruiseSpeed Cruising speed in mph
     * @param batteryCapacity Battery capacity in kWh
     * @param energyPerMile Energy consumption per mile in kWh
     * @param chargeTime Time to fully charge in hours
     * @param passengerCount Maximum passenger capacity
     * @param faultProbability Probability of fault occurrence
     */
    Vehicle(int id, int cruiseSpeed, double batteryCapacity, 
            double energyPerMile, double chargeTime, int passengerCount,
            double faultProbability);

    /**
     * @brief Virtual destructor for proper polymorphic deletion
     */
    virtual ~Vehicle();

    // Getters
    int getId() const;
    int getCruiseSpeed() const;
    double getBatteryCapacity() const;
    double getEnergyPerMile() const;
    double getChargeTime() const;
    int getPassengerCount() const;
    double getFaultProbability() const;
    double getBatteryLevel() const;
    VehicleState getState() const;
    
    // Tracking property getters
    double getTotalFlightTime() const;
    double getTotalDistance() const;
    int getTotalCharges() const;
    double getTotalChargeTime() const;
    int getTotalFaults() const;
    double getPassengerMiles() const;

    // Setters
    void setId(int id);
    void setCruiseSpeed(int speed);
    void setBatteryCapacity(double capacity);
    void setEnergyPerMile(double energy);
    void setChargeTime(double time);
    void setPassengerCount(int count);
    void setFaultProbability(double probability);
    void setBatteryLevel(double level);
    void setState(VehicleState newState);

    /**
     * @brief Compute the flight time based on current battery level
     * @return Estimated flight time in hours
     */
    virtual double computeFlightTime() const;

    /**
     * @brief Compute the maximum distance the vehicle can travel
     * @return Maximum distance in miles
     */
    virtual double computeDistance() const;

    /**
     * @brief Check if a fault occurs based on fault probability
     * @return true if a fault occurs, false otherwise
     */
    virtual bool checkFault() const;

    /**
     * @brief Get the state of the vehicle as a string
     * @return String representation of the vehicle state
     */
    std::string getStateString() const;

    /**
     * @brief Charge the vehicle battery
     * @param duration Charging duration in hours
     */
    void charge(double duration);

    /**
     * @brief Discharge the vehicle battery based on distance traveled
     * @param distance Distance traveled in miles
     */
    void discharge(double distance);
    
    // Methods to update tracking properties
    /**
     * @brief Record flight time and distance
     * @param flightTime Hours of flight
     * @param distance Miles traveled
     */
    void recordFlight(double flightTime, double distance);
    
    /**
     * @brief Record a charging session
     * @param chargeTime Hours spent charging
     */
    void recordCharge(double chargeTime);
    
    /**
     * @brief Record a fault occurrence
     */
    void recordFault();
    
    /**
     * @brief Get the vehicle type (for statistics)
     * @return VehicleType
     */
    virtual VehicleType getVehicleType() const;
};

// Include implementation for template functions if needed
#endif // VEHICLE_H
