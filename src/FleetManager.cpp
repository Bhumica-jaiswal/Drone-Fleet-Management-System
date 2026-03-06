#include "FleetManager.h"
#include "Drone.h"
#include "Mission.h"

#include <algorithm>
#include <iostream>

void FleetManager::addDrone(std::shared_ptr<Drone> drone) {
    if (!drone) return;
    drones_.push_back(drone);
}

void FleetManager::removeDrone(const std::string &droneId) {
    drones_.erase(
        std::remove_if(drones_.begin(), drones_.end(),
                       [&](const std::shared_ptr<Drone> &d) {
                           return d->getId() == droneId;
                       }),
        drones_.end());
}

bool FleetManager::assignMission(std::shared_ptr<Mission> mission) {
    // simple first-idle selection
    for (auto &d : drones_) {
        // need a way to check if drone has no mission
        // will assume Drone::getStatus or introspection later
        // for now downcast to check via getStatus() containing "idle"
        if (d && d->getStatus().find("idle") != std::string::npos) {
            d->assignMission(mission);
            return true;
        }
    }
    return false; // no available drone
}

void FleetManager::update() {
    for (auto &d : drones_) {
        d->update();
    }
}

std::vector<std::string> FleetManager::getFleetStatus() const {
    std::vector<std::string> status;
    for (auto &d : drones_) {
        if (d)
            status.push_back(d->getStatus());
    }
    return status;
}
