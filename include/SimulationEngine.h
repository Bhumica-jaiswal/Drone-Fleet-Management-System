#pragma once

#include <memory>
#include <vector>

#include "FleetManager.h"
#include "GridVisualizer.h"

class Drone;
class Mission;

class SimulationEngine {
public:
    SimulationEngine();

    // allow external setup
    void addDrone(std::shared_ptr<Drone> drone);
    void addMission(std::shared_ptr<Mission> mission);

    void run();

private:
    // internal components
    FleetManager fleet_;
    GridVisualizer visualizer_;
    std::vector<std::shared_ptr<Mission>> pendingMissions_;
};
