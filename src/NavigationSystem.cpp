#include "NavigationSystem.h"
#include <cmath>

void NavigationSystem::navigate(Drone &drone) {
    if (!drone.hasMission())
        return;

    Point dest = drone.getMissionDestination();
    Point pos = drone.getPosition();

    double dx = dest.x - pos.x;
    double dy = dest.y - pos.y;
    double dist = std::sqrt(dx*dx + dy*dy);
    if (dist < 1e-6) {
        // arrived
        drone.clearMission();
        return;
    }

    double step = std::min(drone.getSpeed(), dist);
    Point newPos { pos.x + dx / dist * step,
                   pos.y + dy / dist * step };
    drone.setPosition(newPos);

    // drain battery proportionally
    drone.updateBattery(step * 0.1);
    if (step == dist) {
        // exactly reached
        drone.clearMission();
    }
}
