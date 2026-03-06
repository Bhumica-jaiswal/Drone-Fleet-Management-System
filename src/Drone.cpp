#include "Drone.h"
#include <iostream>

Drone::Drone(std::string id, Point position)
    : id_(std::move(id)), position_(position), batteryLevel_(100.0), currentMission_(nullptr) {}

void Drone::update() {
    // TODO: movement and battery update
}

void Drone::assignMission(std::shared_ptr<Mission> mission) {
    currentMission_ = mission;
}

const std::string& Drone::getId() const { return id_; }
Point Drone::getPosition() const { return position_; }
