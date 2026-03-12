#pragma once

#include <vector>
#include <memory>
#include <map>

class Drone;
struct Point;

class GridVisualizer {
public:
    // grid dimensions
    static constexpr int GRID_SIZE = 10;

    GridVisualizer();

    // display the fleet on a 2D grid
    // maintains persistent trails as drones move
    void displayGrid(const std::vector<std::shared_ptr<Drone>> &drones);

    // clear all trails
    void clearTrails();

private:
    // persistent grid that never gets reinitialized
    // stores: '.', '*' (trail), and drone letters (A, B, C)
    std::vector<std::vector<char>> trailGrid_;

    // track each drone's current grid position for next iteration
    std::map<std::string, std::pair<int, int>> currentDronePositions_; // droneId -> (gridX, gridY)

    // helper to convert world coordinate to grid index
    int worldToGrid(double coord) const;
};
