#ifndef DELTAVEHICLE_H
#define DELTAVEHICLE_H

#include "Vehicle.h"

/**
 * @class DeltaVehicle
 * @brief Delta type vehicle derived from Vehicle base class
 * 
 * Characteristics:
 * - Speed: 90 mph
 * - Battery Capacity: 120 kWh
 * - Charge Time: 0.62 hours
 * - Energy Per Mile: 0.8 kWh/mile
 * - Passenger Capacity: 2
 * - Fault Probability: 0.22
 */
class DeltaVehicle : public Vehicle {
public:
    /**
     * @brief Default constructor for DeltaVehicle
     * @param id Vehicle identification number
     */
    explicit DeltaVehicle(int id);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~DeltaVehicle();
    
    /**
     * @brief Get the vehicle type
     */
    virtual VehicleType getVehicleType() const override;
};

#endif // DELTAVEHICLE_H
