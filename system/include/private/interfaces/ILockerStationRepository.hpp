#ifndef I_LOCKER_STATION_REPOSITORY_HPP
#define I_LOCKER_STATION_REPOSITORY_HPP

#include <cstdint>
#include <vector>
#include <memory>
#include "../../public/Types.hpp"
#include "../LockerStation.hpp"

/** Interface for a repository of locker stations */
class ILockerStationRepository {
public:
    virtual ~ILockerStationRepository() = default;

    /** Get all locker station details */
    virtual std::vector<LockerStationDetails> getAllLockerStations() = 0;

    /** Get a locker station by id */
    virtual OperationStatus<LockerStation*> getLockerStationById(LockerStationId lockerStationId) = 0;

    /** Add a new locker station */
    virtual OperationStatus<bool> addLockerStation(std::unique_ptr<LockerStation> lockerStation) = 0;

    /** Remove a locker station */
    virtual OperationStatus<bool> removeLockerStation(LockerStationId lockerStationId) = 0;
};

#endif // I_LOCKER_STATION_REPOSITORY_HPP