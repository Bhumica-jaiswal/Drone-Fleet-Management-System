#include "SimulationEngine.h"
#include "FleetManager.h"
#include "Drone.h"
#include "Mission.h"
#include "CollisionDetector.h"

#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

SimulationEngine::SimulationEngine() {
    // nothing yet; clients can add drones and missions before calling run()
}

void SimulationEngine::addDrone(std::shared_ptr<Drone> drone) {
    fleet_.addDrone(drone);
}

void SimulationEngine::addMission(std::shared_ptr<Mission> mission) {
    pendingMissions_.push_back(mission);
}

void SimulationEngine::run() {
    std::cout << "Simulation started" << std::endl;

    // if configuration empty, populate with some defaults
    if (fleet_.getDrones().empty() && pendingMissions_.empty()) {
        addDrone(std::make_shared<Drone>("D1", Point{0,0}));
        addDrone(std::make_shared<Drone>("D2", Point{5,5}));
        addDrone(std::make_shared<Drone>("D3", Point{10,0}));

        addMission(std::make_shared<Mission>("M1", MissionType::Delivery, Point{8,8}, 1));
        addMission(std::make_shared<Mission>("M2", MissionType::Surveillance, Point{2,6}, 2));
        addMission(std::make_shared<Mission>("M3", MissionType::Inspection, Point{12,3}, 3));
    }

    const int maxSteps = 20;
    int step = 0;
    for (; step < maxSteps; ++step) {
        std::cout << "\n=== Step " << step << " ===" << std::endl;

        // dispatch a mission when possible
        if (!pendingMissions_.empty()) {
            if (fleet_.assignMission(pendingMissions_.front())) {
                pendingMissions_.erase(pendingMissions_.begin());
            }
        }

        fleet_.update();

        auto statuses = fleet_.getFleetStatus();
        for (const auto &s : statuses) {
            std::cout << s << std::endl;
        }

        if (CollisionDetector::checkCollision(fleet_.getDrones())) {
            std::cout << "-- collision(s) detected this step" << std::endl;
        }

        // if no drone is active and no pending missions, stop early
        if (fleet_.allDronesIdle() && pendingMissions_.empty()) {
            std::cout << "All drones idle and no pending missions; ending simulation early." << std::endl;
            break;
        }

        // slow down output
#ifdef _WIN32
        ::Sleep(200);
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
#endif
    }
    if (step == maxSteps) {
        std::cout << "Reached maximum steps." << std::endl;
    }

    std::cout << "Simulation ended" << std::endl;
}
