#ifndef CHARLIEVEHICLE_H
#define CHARLIEVEHICLE_H

#include "Vehicle.h"

/**
 * @class CharlieVehicle
 * @brief Charlie type vehicle derived from Vehicle base class
 * 
 * Characteristics:
 * - Speed: 160 mph
 * - Battery Capacity: 220 kWh
 * - Charge Time: 0.8 hours
 * - Energy Per Mile: 2.2 kWh/mile
 * - Passenger Capacity: 3
 * - Fault Probability: 0.05
 */
class CharlieVehicle : public Vehicle {
public:
    /**
     * @brief Default constructor for CharlieVehicle
     * @param id Vehicle identification number
     */
    explicit CharlieVehicle(int id);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~CharlieVehicle();
    
    /**
     * @brief Get the vehicle type
     */
    virtual VehicleType getVehicleType() const override;
};

#endif // CHARLIEVEHICLE_H
