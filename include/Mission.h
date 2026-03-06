#pragma once

#include "Drone.h"

class Mission {
public:
    Mission(Point destination);
    Point getDestination() const;

private:
    Point destination_;
};
