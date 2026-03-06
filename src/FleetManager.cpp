#include "FleetManager.h"
#include "Drone.h"
#include <iostream>

void FleetManager::addDrone(std::shared_ptr<Drone> drone) {
    drones_.push_back(drone);
}

void FleetManager::assignMission(std::shared_ptr<Mission> mission) {
    // TODO: assign to available drone
}

void FleetManager::update() {
    for (auto &d : drones_) {
        d->update();
    }
}
