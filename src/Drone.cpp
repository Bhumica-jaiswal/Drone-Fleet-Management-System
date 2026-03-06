#include "Drone.h"
#include <iostream>

Drone::Drone(std::string id, Point position)
    : id_(std::move(id)), position_(position), batteryLevel_(100.0), speed_(1.0), currentMission_(nullptr) {}

void Drone::assignMission(std::shared_ptr<Mission> mission) {
    currentMission_ = mission;
}

void Drone::move() {
    if (!currentMission_)
        return;

    Point dest = currentMission_->getDestination();
    double dx = dest.x - position_.x;
    double dy = dest.y - position_.y;
    double dist = std::sqrt(dx*dx + dy*dy);
    if (dist < 1e-6) {
        // reached destination
        currentMission_ = nullptr;
        return;
    }
    // calculate step proportional to speed
    double step = std::min(speed_, dist);
    position_.x += dx / dist * step;
    position_.y += dy / dist * step;
    updateBattery(step * 0.1); // battery drain factor
}

void Drone::updateBattery(double delta) {
    batteryLevel_ -= delta;
    if (batteryLevel_ < 0.0)
        batteryLevel_ = 0.0;
}

void Drone::update() {
    move();
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
