#include "Mission.h"
#include <sstream>

Mission::Mission(std::string id, MissionType type, Point destination, int priority)
    : id_(std::move(id)), type_(type), destination_(destination), priority_(priority) {}

std::string Mission::getMissionDetails() const {
    std::ostringstream oss;
    oss << "[" << id_ << "] ";
    switch (type_) {
        case MissionType::Delivery:    oss << "Delivery"; break;
        case MissionType::Surveillance: oss << "Surveillance"; break;
        case MissionType::Inspection:   oss << "Inspection"; break;
    }
    oss << " to (" << destination_.x << "," << destination_.y << ") ";
    oss << "prio=" << priority_;
    return oss.str();
}

Point Mission::getDestination() const { return destination_; }
int Mission::getPriority() const { return priority_; }
MissionType Mission::getType() const { return type_; }
const std::string& Mission::getId() const { return id_; }
