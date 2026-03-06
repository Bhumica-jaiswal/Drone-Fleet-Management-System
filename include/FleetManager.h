#pragma once

#include <vector>
#include <memory>

class Drone;
class Mission;

class FleetManager {
public:
    void addDrone(std::shared_ptr<Drone> drone);
    void assignMission(std::shared_ptr<Mission> mission);
    void update();

private:
    std::vector<std::shared_ptr<Drone>> drones_;
};
