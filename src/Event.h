#ifndef EVENT_H
#define EVENT_H

#include <string>

/**
 * @enum EventType
 * @brief Types of events in the simulation
 */
enum class EventType {
    FLIGHT_END,    // Vehicle finishes flying (battery depleted)
    CHARGE_END,    // Vehicle finishes charging
    FAULT          // Vehicle experiences a fault, flight ends early
};

/**
 * @struct Event
 * @brief Represents an event in the simulation
 */
struct Event {
    double time;           // Time when event occurs
    EventType type;        // Type of event
    int vehicleId;          // ID of vehicle associated with event
    
    // Constructor
    Event(double t, EventType et, int vid) : time(t), type(et), vehicleId(vid) {}
};

/**
 * @class EventComparator
 * @brief Comparator for priority queue (earliest time first)
 */
class EventComparator {
public:
    bool operator()(const Event& a, const Event& b) const {
        // Higher time value = lower priority (we want earliest first)
        return a.time > b.time;
    }
};

#endif // EVENT_H
