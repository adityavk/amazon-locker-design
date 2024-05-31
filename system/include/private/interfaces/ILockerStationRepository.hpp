#ifndef I_LOCKER_STATION_REPOSITORY_HPP
#define I_LOCKER_STATION_REPOSITORY_HPP

#include <cstdint>
#include <vector>
#include "../public/Types.hpp"

/** Interface for the repository of locker stations */
class ILockerStationRepository {
public:
    virtual ~ILockerStationRepository() = default;

    /** Get the details of a locker station by ID */
    virtual LockerStationDetails getLockerStationById(LockerStationId id) = 0;

    /** Get the details of all locker stations */
    virtual std::vector<LockerStationDetails> getAllLockerStations() = 0;

    /** Add a new locker station */
    virtual void addLockerStation(const LockerStationDetails& lockerStation) = 0;

    /** Remove a locker station by ID */
    virtual void removeLockerStation(LockerStationId id) = 0;
};

#endif // I_LOCKER_STATION_REPOSITORY_HPP