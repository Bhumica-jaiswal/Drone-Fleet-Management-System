#include "GridVisualizer.h"
#include "Drone.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

int GridVisualizer::worldToGrid(double coord) const {
    // round to nearest integer and clamp to grid bounds
    int gridCoord = static_cast<int>(std::round(coord));
    if (gridCoord < 0) gridCoord = 0;
    if (gridCoord >= GRID_SIZE) gridCoord = GRID_SIZE - 1;
    return gridCoord;
}

void GridVisualizer::displayGrid(const std::vector<std::shared_ptr<Drone>> &drones) const {
    // create a GRID_SIZE x GRID_SIZE grid of empty cells
    std::vector<std::vector<char>> grid(GRID_SIZE, std::vector<char>(GRID_SIZE, '.'));

    // place each drone on the grid
    for (const auto &drone : drones) {
        if (!drone) continue;

        Point pos = drone->getPosition();
        int gridX = worldToGrid(pos.x);
        int gridY = worldToGrid(pos.y);

        // use first letter of drone ID
        char droneChar = drone->getId()[0];
        grid[gridY][gridX] = droneChar;
    }

    // print the grid with borders
    std::cout << "\n  DRONE FLEET MAP\n  ";
    for (int i = 0; i < GRID_SIZE; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;

    for (int y = 0; y < GRID_SIZE; ++y) {
        std::cout << y << " ";
        for (int x = 0; x < GRID_SIZE; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << " " << y << std::endl;
    }

    std::cout << "  ";
    for (int i = 0; i < GRID_SIZE; ++i) {
        std::cout << i;
    }
    std::cout << "\n" << std::endl;
}
