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

using LockerSize = PackageSize;

class LockerStation {

    /** Assign a locker to a package for the given duration */
    OperationStatus<bool> assignLocker(const Package& package, DateTime fromTime, DateTime toTime);

    /** Open the locker to retrieve a package */
    OperationStatus<bool> openLocker(LockerPickupCode code);

    /** Close the locker after package retrieval */
    void closeLocker(LockerId lockerId);

    /** Deliver a package to the locker station */
    OperationStatus<bool> deliverPackage(PackageId packageId);

private:
    friend class LockerSystemAdmin;

    LockerStationDetails representation;
    std::unique_ptr<ILockerCodeManager> lockerCodeManager;
    std::unique_ptr<INotificationManager> notificationManager;

    // One ILockerAvailabilityManager instance per type of locker size
    using LockerAvailabilityManagers = std::unordered_map<LockerSize, std::unique_ptr<ILockerAvailabilityManager>>;
    LockerAvailabilityManagers lockerAvailabilityManagers;

    LockerStation(
        LockerStationId id, Location location, std::string name,
        std::unique_ptr<ILockerCodeManager> lockerCodeManager,
        std::unique_ptr<INotificationManager> notificationManager,
        LockerAvailabilityManagers&& lockerAvailabilityManagers
    );
};

#endif // LOCKER_STATION_HPP