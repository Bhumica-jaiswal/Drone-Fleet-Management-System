#pragma once

#include <vector>
#include <memory>

class Drone;

class CollisionDetector {
public:
    static bool checkCollision(const std::vector<std::shared_ptr<Drone>> &drones);
};
