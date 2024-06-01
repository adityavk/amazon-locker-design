#include "../include/private/DistanceBasedLockerFinder.hpp"

std::vector<LockerStationDetails> DistanceBasedLockerFinder::findLockersNearLocation(Location location, double radius, ILockerStationRepository* repository) {
    std::vector<LockerStationDetails> lockerStations;
    for (const auto& station : repository->getAllLockerStations()) {
        if (station.location.distanceTo(location) <= radius) {
            lockerStations.push_back(station);
        }
    }
    return lockerStations;
}