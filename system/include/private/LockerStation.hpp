#ifndef LOCKER_STATION_HPP
#define LOCKER_STATION_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>
#include "../public/Types.hpp"
#include "PrivateTypes.hpp"
#include "interfaces/ILockerAvailabilityManager.hpp"
#include "interfaces/ILockerCodeManager.hpp"
#include "interfaces/INotificationManager.hpp"

class LockerStation {
public:
    /** Get the locker station details */
    LockerStationDetails getDetails() const;

    /** Assign a locker to a package for the given duration */
    OperationStatus<bool> assignLocker(const Package& package, DateTime fromTime, DateTime toTime);

    /** Open the locker to retrieve a package */
    OperationStatus<Package> openLocker(LockerPickupCode code);

    /** Deliver a package to the locker station */
    OperationStatus<bool> deliverPackage(Package package);

private:
    friend class LockerSystemAdmin;

    LockerStationDetails details;
    std::unique_ptr<ILockerCodeManager> lockerCodeManager;
    std::shared_ptr<INotificationManager> notificationManager;
    std::unique_ptr<ILockerAvailabilityManager> lockerAvailabilityManager;

    LockerStation(
        LockerStationId id, Location location, std::string name,
        std::unique_ptr<ILockerCodeManager> lockerCodeManager,
        std::shared_ptr<INotificationManager> notificationManager,
        std::unique_ptr<ILockerAvailabilityManager> lockerAvailabilityManager
    );
};

#endif // LOCKER_STATION_HPP