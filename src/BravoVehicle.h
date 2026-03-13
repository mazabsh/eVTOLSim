#ifndef BRAVOVEHICLE_H
#define BRAVOVEHICLE_H

#include "Vehicle.h"

/**
 * @class BravoVehicle
 * @brief Bravo type vehicle derived from Vehicle base class
 * 
 * Characteristics:
 * - Speed: 100 mph
 * - Battery Capacity: 100 kWh
 * - Charge Time: 0.2 hours
 * - Energy Per Mile: 1.5 kWh/mile
 * - Passenger Capacity: 5
 * - Fault Probability: 0.10
 */
class BravoVehicle : public Vehicle {
public:
    /**
     * @brief Default constructor for BravoVehicle
     * @param id Vehicle identification number
     */
    explicit BravoVehicle(int id);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~BravoVehicle();
    
    /**
     * @brief Get the vehicle type
     */
    virtual VehicleType getVehicleType() const override;
};

#endif // BRAVOVEHICLE_H
