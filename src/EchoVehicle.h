#ifndef ECHOVEHICLE_H
#define ECHOVEHICLE_H

#include "Vehicle.h"

/**
 * @class EchoVehicle
 * @brief Echo type vehicle derived from Vehicle base class
 * 
 * Characteristics:
 * - Speed: 30 mph
 * - Battery Capacity: 150 kWh
 * - Charge Time: 0.3 hours
 * - Energy Per Mile: 5.8 kWh/mile
 * - Passenger Capacity: 2
 * - Fault Probability: 0.61
 */
class EchoVehicle : public Vehicle {
public:
    /**
     * @brief Default constructor for EchoVehicle
     * @param id Vehicle identification number
     */
    explicit EchoVehicle(int id);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~EchoVehicle();
    
    /**
     * @brief Get the vehicle type
     */
    virtual VehicleType getVehicleType() const override;
};

#endif // ECHOVEHICLE_H
