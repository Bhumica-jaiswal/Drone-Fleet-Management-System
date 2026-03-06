#pragma once

#include <string>
#include "Drone.h"

enum class MissionType {
    Delivery,
    Surveillance,
    Inspection
};

class Mission {
public:
    Mission(std::string id, MissionType type, Point destination, int priority);

    std::string getMissionDetails() const;
    Point getDestination() const;
    int getPriority() const;
    MissionType getType() const;
    const std::string& getId() const;

private:
    std::string id_;
    MissionType type_;
    Point destination_;
    int priority_;
};
