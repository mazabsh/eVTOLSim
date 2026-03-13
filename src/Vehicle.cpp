#include "Vehicle.h"
#include <cmath>
#include <sstream>

// Default constructor
Vehicle::Vehicle()
    : id(0)
    , cruiseSpeed(0)
    , batteryCapacity(0.0)
    , energyPerMile(0.0)
    , chargeTime(0.0)
    , passengerCount(0)
    , faultProbability(0.0)
    , batteryLevel(100.0)  // Start with full battery
    , state(VehicleState::FLYING)  // Start in Flying state
    , totalFlightTime(0.0)
    , totalDistance(0.0)
    , totalCharges(0)
    , totalChargeTime(0.0)
    , totalFaults(0)
    , passengerMiles(0.0)
{
}

// Parameterized constructor
Vehicle::Vehicle(int id, int cruiseSpeed, double batteryCapacity, 
                 double energyPerMile, double chargeTime, int passengerCount,
                 double faultProbability)
    : id(id)
    , cruiseSpeed(cruiseSpeed)
    , batteryCapacity(batteryCapacity)
    , energyPerMile(energyPerMile)
    , chargeTime(chargeTime)
    , passengerCount(passengerCount)
    , faultProbability(faultProbability)
    , batteryLevel(100.0)  // Start with full battery
    , state(VehicleState::FLYING)  // Start in Flying state
    , totalFlightTime(0.0)
    , totalDistance(0.0)
    , totalCharges(0)
    , totalChargeTime(0.0)
    , totalFaults(0)
    , passengerMiles(0.0)
{
    // Validate fault probability is in valid range
    if (faultProbability < 0.0 || faultProbability > 1.0) {
        throw std::invalid_argument("Fault probability must be between 0.0 and 1.0");
    }
}

// Virtual destructor
Vehicle::~Vehicle() {
}

// Getters
int Vehicle::getId() const {
    return id;
}

int Vehicle::getCruiseSpeed() const {
    return cruiseSpeed;
}

double Vehicle::getBatteryCapacity() const {
    return batteryCapacity;
}

double Vehicle::getEnergyPerMile() const {
    return energyPerMile;
}

double Vehicle::getChargeTime() const {
    return chargeTime;
}

int Vehicle::getPassengerCount() const {
    return passengerCount;
}

double Vehicle::getFaultProbability() const {
    return faultProbability;
}

double Vehicle::getBatteryLevel() const {
    return batteryLevel;
}

VehicleState Vehicle::getState() const {
    return state;
}

// Tracking property getters
double Vehicle::getTotalFlightTime() const {
    return totalFlightTime;
}

double Vehicle::getTotalDistance() const {
    return totalDistance;
}

int Vehicle::getTotalCharges() const {
    return totalCharges;
}

double Vehicle::getTotalChargeTime() const {
    return totalChargeTime;
}

int Vehicle::getTotalFaults() const {
    return totalFaults;
}

double Vehicle::getPassengerMiles() const {
    return passengerMiles;
}

// Setters
void Vehicle::setId(int id) {
    this->id = id;
}

void Vehicle::setCruiseSpeed(int speed) {
    if (speed < 0) {
        throw std::invalid_argument("Cruise speed cannot be negative");
    }
    this->cruiseSpeed = speed;
}

void Vehicle::setBatteryCapacity(double capacity) {
    if (capacity < 0.0) {
        throw std::invalid_argument("Battery capacity cannot be negative");
    }
    this->batteryCapacity = capacity;
}

void Vehicle::setEnergyPerMile(double energy) {
    if (energy < 0.0) {
        throw std::invalid_argument("Energy per mile cannot be negative");
    }
    this->energyPerMile = energy;
}

void Vehicle::setChargeTime(double time) {
    if (time < 0.0) {
        throw std::invalid_argument("Charge time cannot be negative");
    }
    this->chargeTime = time;
}

void Vehicle::setPassengerCount(int count) {
    if (count < 0) {
        throw std::invalid_argument("Passenger count cannot be negative");
    }
    this->passengerCount = count;
}

void Vehicle::setFaultProbability(double probability) {
    if (probability < 0.0 || probability > 1.0) {
        throw std::invalid_argument("Fault probability must be between 0.0 and 1.0");
    }
    this->faultProbability = probability;
}

void Vehicle::setBatteryLevel(double level) {
    if (level < 0.0) {
        this->batteryLevel = 0.0;
    } else if (level > 100.0) {
        this->batteryLevel = 100.0;
    } else {
        this->batteryLevel = level;
    }
}

void Vehicle::setState(VehicleState newState) {
    this->state = newState;
}

/**
 * @brief Compute the flight time based on current battery level
 * @return Estimated flight time in hours
 */
double Vehicle::computeFlightTime() const {
    // Calculate available energy in kWh based on current battery level
    double availableEnergy = (batteryLevel / 100.0) * batteryCapacity;
    
    // Flight time = Available energy / Energy consumption per hour
    // Energy per hour = cruiseSpeed * energyPerMile
    if (energyPerMile <= 0.0 || cruiseSpeed <= 0) {
        return 0.0;
    }
    
    double energyPerHour = cruiseSpeed * energyPerMile;
    return availableEnergy / energyPerHour;
}

/**
 * @brief Compute the maximum distance the vehicle can travel
 * @return Maximum distance in miles
 */
double Vehicle::computeDistance() const {
    // Calculate available energy in kWh based on current battery level
    double availableEnergy = (batteryLevel / 100.0) * batteryCapacity;
    
    // Distance = Available energy / Energy per mile
    if (energyPerMile <= 0.0) {
        return 0.0;
    }
    
    return availableEnergy / energyPerMile;
}

/**
 * @brief Check if a fault occurs based on fault probability
 * @return true if a fault occurs, false otherwise
 */
bool Vehicle::checkFault() const {
    // Use random number generation to simulate fault probability
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    
    double randomValue = dis(gen);
    return randomValue < faultProbability;
}

/**
 * @brief Get the state of the vehicle as a string
 * @return String representation of the vehicle state
 */
std::string Vehicle::getStateString() const {
    switch (state) {
        case VehicleState::FLYING:
            return "FLYING";
        case VehicleState::WAITING_FOR_CHARGER:
            return "WAITING_FOR_CHARGER";
        case VehicleState::CHARGING:
            return "CHARGING";
        default:
            return "UNKNOWN";
    }
}

/**
 * @brief Charge the vehicle battery
 * @param duration Charging duration in hours
 */
void Vehicle::charge(double duration) {
    if (duration < 0.0) {
        throw std::invalid_argument("Charging duration cannot be negative");
    }
    
    // Calculate charge rate (kWh per hour)
    double chargeRate = batteryCapacity / chargeTime;
    
    // Calculate energy added
    double energyAdded = chargeRate * duration;
    
    // Update battery level
    double energyLevel = (batteryLevel / 100.0) * batteryCapacity + energyAdded;
    double newLevel = (energyLevel / batteryCapacity) * 100.0;
    
    // Clamp to 100%
    setBatteryLevel(newLevel);
}

/**
 * @brief Discharge the vehicle battery based on distance traveled
 * @param distance Distance traveled in miles
 */
void Vehicle::discharge(double distance) {
    if (distance < 0.0) {
        throw std::invalid_argument("Distance cannot be negative");
    }
    
    // Calculate energy consumed
    double energyConsumed = distance * energyPerMile;
    
    // Update battery level
    double currentEnergy = (batteryLevel / 100.0) * batteryCapacity;
    double newEnergy = currentEnergy - energyConsumed;
    double newLevel = (newEnergy / batteryCapacity) * 100.0;
    
    // Clamp to 0%
    setBatteryLevel(newLevel);
}

/**
 * @brief Record flight time and distance
 */
void Vehicle::recordFlight(double flightTime, double distance) {
    if (flightTime > 0.0) {
        totalFlightTime += flightTime;
    }
    if (distance > 0.0) {
        totalDistance += distance;
        // Calculate passenger-miles
        passengerMiles += distance * passengerCount;
    }
}

/**
 * @brief Record a charging session
 */
void Vehicle::recordCharge(double chargeTime) {
    if (chargeTime > 0.0) {
        totalCharges++;
        totalChargeTime += chargeTime;
    }
}

/**
 * @brief Record a fault occurrence
 */
void Vehicle::recordFault() {
    totalFaults++;
}

/**
 * @brief Get the vehicle type (for statistics)
 */
VehicleType Vehicle::getVehicleType() const {
    return VehicleType::UNKNOWN;
}
