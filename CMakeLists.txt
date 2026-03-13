cmake_minimum_required(VERSION 3.10)
project(JobyAviation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/Vehicle.cpp
    src/AlphaVehicle.cpp
    src/BravoVehicle.cpp
    src/CharlieVehicle.cpp
    src/DeltaVehicle.cpp
    src/EchoVehicle.cpp
    src/ChargerManager.cpp
    src/StatisticsManager.cpp
    src/SimulationController.cpp
    main.cpp
)

# Main executable
add_executable(simulation ${SOURCES})

# Include directories
target_include_directories(simulation PRIVATE src)

# Enable testing
enable_testing()

# Test executable: Vehicle tests
set(TEST_VEHICLE_SOURCES
    tests/test_vehicle.cpp
    src/Vehicle.cpp
    src/AlphaVehicle.cpp
    src/BravoVehicle.cpp
    src/CharlieVehicle.cpp
    src/DeltaVehicle.cpp
    src/EchoVehicle.cpp
    src/StatisticsManager.cpp
)

add_executable(test_vehicle ${TEST_VEHICLE_SOURCES})
target_include_directories(test_vehicle PRIVATE src)
add_test(NAME VehicleTests COMMAND test_vehicle)

# Test executable: ChargerManager tests
set(TEST_CHARGER_SOURCES
    tests/test_chargermanager.cpp
    src/Vehicle.cpp
    src/AlphaVehicle.cpp
    src/BravoVehicle.cpp
    src/CharlieVehicle.cpp
    src/DeltaVehicle.cpp
    src/EchoVehicle.cpp
    src/ChargerManager.cpp
    src/StatisticsManager.cpp
)

add_executable(test_chargermanager ${TEST_CHARGER_SOURCES})
target_include_directories(test_chargermanager PRIVATE src)
add_test(NAME ChargerManagerTests COMMAND test_chargermanager)

# Test executable: StatisticsManager tests
set(TEST_STATISTICS_SOURCES
    tests/test_statistics.cpp
    src/StatisticsManager.cpp
)

add_executable(test_statistics ${TEST_STATISTICS_SOURCES})
target_include_directories(test_statistics PRIVATE src)
add_test(NAME StatisticsManagerTests COMMAND test_statistics)
