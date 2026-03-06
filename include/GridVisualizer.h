#pragma once

#include <vector>
#include <memory>

class Drone;

class GridVisualizer {
public:
    // grid dimensions
    static constexpr int GRID_SIZE = 10;

    // display the fleet on a 2D grid
    // takes the drone list from FleetManager
    void displayGrid(const std::vector<std::shared_ptr<Drone>> &drones) const;

private:
    // helper to convert world coordinate to grid index
    int worldToGrid(double coord) const;
};
