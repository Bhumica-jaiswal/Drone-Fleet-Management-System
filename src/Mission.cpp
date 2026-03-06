#include "Mission.h"

Mission::Mission(Point destination) : destination_(destination) {}

Point Mission::getDestination() const { return destination_; }
