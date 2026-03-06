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

    // mission management
    void assignMission(std::shared_ptr<Mission> mission);

    // per‑tick behavior
    void move();                          // adjust position toward destination
    void updateBattery(double delta);     // drain battery based on movement/usage
    void update();                        // combined movement & battery update

    // status reporting
    std::string getStatus() const;

    const std::string& getId() const;
    Point getPosition() const;
    double getBatteryLevel() const;
    double getSpeed() const;

private:
    std::string id_;
    Point position_;
    double batteryLevel_;
    double speed_;
    std::shared_ptr<Mission> currentMission_;
};
