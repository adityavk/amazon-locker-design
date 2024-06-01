#ifndef DISTANCE_BASED_LOCKER_FINDER_HPP
#define DISTANCE_BASED_LOCKER_FINDER_HPP

#include "interfaces/ILockerFinder.hpp"

class DistanceBasedLockerFinder : public ILockerFinder {
public:
    std::vector<LockerStationDetails> findLockersNearLocation(Location location, double radius, ILockerStationRepository* repository) override;
};

#endif // DISTANCE_BASED_LOCKER_FINDER_HPP