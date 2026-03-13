# eVTOL Fleet Simulation

An event-driven simulation of an eVTOL (Electric Vertical Takeoff and Landing) aircraft fleet with charger management and statistics tracking.

## Architecture

```
                 +-------------------+
                 |   Simulation      |
                 |-------------------|
                 | currentTime       |
                 | eventQueue        |
                 | vehicles          |
                 | chargerManager    |
                 | statsManager      |
                 +---------+---------+
                           |
                           |
                           v
                 +-------------------+
                 |      Event        |
                 |-------------------|
                 | time              |
                 | eventType         |
                 | vehicleID         |
                 +-------------------+
                           |
                           v
         +--------------------------------------+
         |         priority_queue<Event>        |
         |     (ordered by earliest time)       |
         +--------------------------------------+




                    +----------------------+
                    |      Vehicle         |
                    |----------------------|
                    | id                   |
                    | cruiseSpeed          |
                    | batteryCapacity      |
                    | energyPerMile        |
                    | chargeTime           |
                    | passengerCount       |
                    | faultProbability     |
                    | batteryLevel         |
                    | state                |
                    |----------------------|
                    | computeFlightTime()  |
                    | computeDistance()    |
                    | checkFault()         |
                    +----------+-----------+
                               |
     ---------------------------------------------------------
     |           |            |            |                 |
     v           v            v            v                 v

 AlphaVehicle  BravoVehicle  CharlieVehicle  DeltaVehicle  EchoVehicle


             +---------+
             | Flying  |
             +----+----+
                  |
      battery empty
                  |
                  v
           +-------------+
           | Waiting     |
           | for Charger |
           +------+------+
                  |
          charger free
                  |
                  v
            +-----------+
            | Charging  |
            +-----+-----+
                  |
            charge done
                  |
                  v
               Flying
```

## Vehicle Types

| Type    | Speed | Battery | Charge Time | Energy/Mile | Passengers | Fault Prob |
| ------- | ----- | ------- | ---------- | ----------- | ---------- | ---------- |
| Alpha   | 120   | 320     | 0.6        | 1.6         | 4          | 0.25       |
| Bravo   | 100   | 100     | 0.2        | 1.5         | 5          | 0.10       |
| Charlie | 160   | 220     | 0.8        | 2.2         | 3          | 0.05       |
| Delta   | 90    | 120     | 0.62       | 0.8         | 2          | 0.22       |
| Echo    | 30    | 150     | 0.3        | 5.8         | 2          | 0.61       |

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./simulation
```

## Testing

```bash
# Run all tests
ctest --output-on-failure

# Or run individual tests
./test_vehicle        # 10 tests (all vehicle types)
./test_chargermanager # 6 tests
./test_statistics     # 5 tests
```

### Test Summary
- **VehicleTests**: Vehicle creation, flight time calculation, distance calculation, state transitions, recordFlight, passengerMiles, plus all 5 vehicle types (Alpha, Bravo, Charlie, Delta, Echo)
- **ChargerManagerTests**: Creation, requestCharger, charger queue, releaseCharger, assignNextVehicle, hasWaitingVehicles
- **StatisticsManagerTests**: Creation, recordFlight, recordCharge, recordFault, recordPassengerMiles

## Components

- **Simulation** - Main controller managing the event-driven simulation loop
- **Vehicle** - Base class with flight/charging logic
- **ChargerManager** - Manages 3 chargers and vehicle queue
- **StatisticsManager** - Tracks statistics per vehicle type
- **Event** - Priority queue events (FLIGHT_END, CHARGE_END)

## Event-Driven Simulation

1. At time 0, all vehicles start flying
2. FLIGHT_END events are scheduled based on battery life
3. When flight ends: vehicle requests charger, records stats
4. When charging finishes: vehicle starts new flight, next vehicle from queue starts charging
5. Events are processed in chronological order using priority queue

## Assumptions

### Fault Handling
- **Fault ends flight early**: When a fault occurs during flight, the flight terminates immediately at that point
- Fault time is randomly distributed during the flight duration (uniform distribution)
- When fault occurs: partial distance is calculated based on time elapsed, battery is discharged proportionally, vehicle immediately goes to charger

### Charging
- Event-driven approach: vehicles are charged instantaneously to 100% when CHARGE_END event occurs
- No incremental charging simulation - full charge time is used for scheduling
- Vehicles in charger queue wait until a charger becomes available

### Vehicle Initialization
- Vehicle types are randomly selected at simulation start
- Each vehicle type has equal probability of being selected

### Simulation End Conditions
- Simulation ends when either: (a) event queue is empty, or (b) currentTime exceeds simulation duration

### Statistics
- Passenger-miles = passengers × distance traveled
- Total flight time accumulates across all flights (including partial flights due to faults)
- Faults are counted per vehicle and aggregated by type
