#include "CollisionDetector.h"
#include "Drone.h"
#include <cmath>
#include <iostream>

bool CollisionDetector::checkCollision(const std::vector<std::shared_ptr<Drone>> &drones) {
    const double kMinSeparation = 1.0; // units
    bool collisionDetected = false;

    size_t n = drones.size();
    for (size_t i = 0; i < n; ++i) {
        if (!drones[i]) continue;
        auto pos1 = drones[i]->getPosition();
        for (size_t j = i + 1; j < n; ++j) {
            if (!drones[j]) continue;
            auto pos2 = drones[j]->getPosition();
            double dx = pos1.x - pos2.x;
            double dy = pos1.y - pos2.y;
            double dist = std::sqrt(dx*dx + dy*dy);
            if (dist < kMinSeparation) {
                collisionDetected = true;
                std::cout << "Warning: potential collision between "
                          << drones[i]->getId() << " and "
                          << drones[j]->getId() << " (distance="
                          << dist << ")" << std::endl;
            }
        }
    }
    return collisionDetected;
}
