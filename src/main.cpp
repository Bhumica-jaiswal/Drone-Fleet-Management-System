#include "SimulationEngine.h"
#include "Drone.h"
#include "Mission.h"

#include <memory>

int main() {
    SimulationEngine engine;

    // build fleet externally
    engine.addDrone(std::make_shared<Drone>("Alpha", Point{0,0}));
    engine.addDrone(std::make_shared<Drone>("Bravo", Point{3,4}));
    engine.addDrone(std::make_shared<Drone>("Charlie", Point{6,1}));

    // create some missions
    engine.addMission(std::make_shared<Mission>("MX1", MissionType::Delivery, Point{5,5}, 1));
    engine.addMission(std::make_shared<Mission>("MX2", MissionType::Surveillance, Point{1,7}, 2));
    engine.addMission(std::make_shared<Mission>("MX3", MissionType::Inspection, Point{8,2}, 3));

    // run the simulation (which will print results to console)
    engine.run();

    return 0;
}
