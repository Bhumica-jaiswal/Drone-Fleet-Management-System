#pragma once

#include <vector>
#include <memory>
#include <string>

class Drone;
class Mission;

class FleetManager {
public:
    // fleet management
    void addDrone(std::shared_ptr<Drone> drone);
    void removeDrone(const std::string &droneId);

    // mission operations
    bool assignMission(std::shared_ptr<Mission> mission);

    // simulation tick
    void update();

    // reporting
    std::vector<std::string> getFleetStatus() const;

private:
    std::vector<std::shared_ptr<Drone>> drones_;
};
