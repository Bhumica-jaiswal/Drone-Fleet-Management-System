#include "Drone.h"
#include "NavigationSystem.h"
#include "Mission.h"
#include <iostream>

Drone::Drone(std::string id, Point position)
    : id_(std::move(id)), position_(position), batteryLevel_(100.0), speed_(1.0), currentMission_(nullptr) {}

void Drone::assignMission(std::shared_ptr<Mission> mission) {
    currentMission_ = mission;
}

void Drone::move() {
    // delegate actual motion to NavigationSystem
    NavigationSystem::navigate(*this);
}

void Drone::updateBattery(double delta) {
    batteryLevel_ -= delta;
    if (batteryLevel_ < 0.0)
        batteryLevel_ = 0.0;
}

void Drone::update() {
    move();
}

bool Drone::hasMission() const {
    return currentMission_ != nullptr;
}

Point Drone::getMissionDestination() const {
    if (currentMission_)
        return currentMission_->getDestination();
    return position_; // no mission, return current
}

void Drone::clearMission() {
    currentMission_ = nullptr;
}

void Drone::setPosition(Point p) {
    position_ = p;
}

std::string Drone::getStatus() const {
    char buf[128];
    std::snprintf(buf, sizeof(buf), "Drone %s | Pos(%.1f,%.1f) | Batt: %.1f%% %s",
                  id_.c_str(), position_.x, position_.y, batteryLevel_,
                  currentMission_ ? "| en route" : "| idle");
    return std::string(buf);
}

const std::string& Drone::getId() const { return id_; }
Point Drone::getPosition() const { return position_; }
double Drone::getBatteryLevel() const { return batteryLevel_; }
double Drone::getSpeed() const { return speed_; }
