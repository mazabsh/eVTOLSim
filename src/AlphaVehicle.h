#ifndef ALPHAVEHICLE_H
#define ALPHAVEHICLE_H

#include "Vehicle.h"

/**
 * @class AlphaVehicle
 * @brief Alpha type vehicle derived from Vehicle base class
 * 
 * Characteristics:
 * - Speed: 120 mph
 * - Battery Capacity: 320 kWh
 * - Charge Time: 0.6 hours
 * - Energy Per Mile: 1.6 kWh/mile
 * - Passenger Capacity: 4
 * - Fault Probability: 0.25
 */
class AlphaVehicle : public Vehicle {
public:
    /**
     * @brief Default constructor for AlphaVehicle
     * @param id Vehicle identification number
     */
    explicit AlphaVehicle(int id);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~AlphaVehicle();
    
    /**
     * @brief Get the vehicle type
     */
    virtual VehicleType getVehicleType() const override;
};

#endif // ALPHAVEHICLE_H
