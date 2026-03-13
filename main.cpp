#include "src/SimulationController.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   eVTOL Fleet Simulation               " << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // Create simulation with:
    // - 10 vehicles (2 of each type)
    // - 3 chargers
    // - 3 hours duration
    SimulationController sim(20, 3, 3.0);
    
    // Run the simulation
    sim.run();
    
    return 0;
}
