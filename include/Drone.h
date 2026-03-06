#pragma once

#include <string>
#include <utility>

struct Point {
    double x;
    double y;
};

class Mission;

class Drone {
public:
    Drone(std::string id, Point position);
    void update();
    void assignMission(std::shared_ptr<Mission> mission);

    const std::string& getId() const;
    Point getPosition() const;

private:
    std::string id_;
    Point position_;
    double batteryLevel_;
    std::shared_ptr<Mission> currentMission_;
};
