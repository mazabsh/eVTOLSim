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

## Assumptions

### Fault Handling
- **Fault ends flight early**: When a fault occurs during flight, the flight terminates immediately at that point
- Fault time is randomly distributed during the flight duration (uniform distribution)
- When fault occurs: partial distance is calculated based on time elapsed, battery is discharged proportionally, vehicle immediately goes to charger

### Vehicle Initialization
- Vehicle types are randomly selected at simulation start
- Each vehicle type has equal probability of being selected

### Simulation End Conditions
- Simulation ends when either: (a) event queue is empty, or (b) currentTime exceeds simulation duration
