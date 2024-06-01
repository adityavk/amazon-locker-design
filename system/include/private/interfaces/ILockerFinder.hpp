#ifndef I_LOCKER_FINDER_HPP
#define I_LOCKER_FINDER_HPP

#include <vector>
#include "../../public/Types.hpp"
#include "ILockerStationRepository.hpp"

/** Interface to find locker stations near a location */
class ILockerFinder {
public:
    virtual ~ILockerFinder() = default;

    /** Find locker stations near the given location */
    virtual std::vector<LockerStationDetails> findLockersNearLocation(Location location, double radius, ILockerStationRepository* repository) = 0;
};

#endif // I_LOCKER_FINDER_HPP