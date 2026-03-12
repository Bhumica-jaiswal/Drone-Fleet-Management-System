#include "GridVisualizer.h"
#include "Drone.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

GridVisualizer::GridVisualizer() {
    // Initialize the persistent grid ONCE with empty cells
    trailGrid_ = std::vector<std::vector<char>>(GRID_SIZE, std::vector<char>(GRID_SIZE, '.'));
}

int GridVisualizer::worldToGrid(double coord) const {
    // round to nearest integer and clamp to grid bounds
    int gridCoord = static_cast<int>(std::round(coord));
    if (gridCoord < 0) gridCoord = 0;
    if (gridCoord >= GRID_SIZE) gridCoord = GRID_SIZE - 1;
    return gridCoord;
}

void GridVisualizer::displayGrid(const std::vector<std::shared_ptr<Drone>> &drones) {
    // Step 1: Mark previous positions with trails before updating positions
    for (const auto &drone : drones) {
        if (!drone) continue;

        std::string droneId = drone->getId();
        
        // Check if we have a recorded position from the last step
        auto it = currentDronePositions_.find(droneId);
        if (it != currentDronePositions_.end()) {
            int prevGridX = it->second.first;
            int prevGridY = it->second.second;
            
            // Mark the previous position with a trail (if it's not already a trail)
            if (trailGrid_[prevGridY][prevGridX] != '*') {
                trailGrid_[prevGridY][prevGridX] = '*';
            }
        }
    }

    // Step 2: Clear current drone positions and place drones at their current locations
    for (const auto &drone : drones) {
        if (!drone) continue;

        std::string droneId = drone->getId();
        Point pos = drone->getPosition();
        
        int gridX = worldToGrid(pos.x);
        int gridY = worldToGrid(pos.y);
        
        char droneChar = droneId[0]; // First letter of drone ID (A, B, C)
        
        // Place drone at current position (overwrites any trail)
        trailGrid_[gridY][gridX] = droneChar;
        
        // Record this position for the next step
        currentDronePositions_[droneId] = std::make_pair(gridX, gridY);
    }

    // Step 3: Display the grid
    std::cout << "\n  DRONE FLEET MAP\n  ";
    for (int i = 0; i < GRID_SIZE; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;

    for (int y = 0; y < GRID_SIZE; ++y) {
        std::cout << y << " ";
        for (int x = 0; x < GRID_SIZE; ++x) {
            std::cout << trailGrid_[y][x];
        }
        std::cout << " " << y << std::endl;
    }

    std::cout << "  ";
    for (int i = 0; i < GRID_SIZE; ++i) {
        std::cout << i;
    }
    std::cout << "\n" << std::endl;
}

void GridVisualizer::clearTrails() {
    // Reinitialize the grid to all empty cells
    trailGrid_ = std::vector<std::vector<char>>(GRID_SIZE, std::vector<char>(GRID_SIZE, '.'));
    // Clear position tracking
    currentDronePositions_.clear();
}
