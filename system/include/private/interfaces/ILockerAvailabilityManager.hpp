#ifndef I_LOCKER_AVAILABILITY_MANAGER_HPP
#define I_LOCKER_AVAILABILITY_MANAGER_HPP

#include <cstdint>
#include "../public/Types.hpp"
#include "../PrivateTypes.hpp"

/** Interface to manage the availability of lockers in a locker station */
class ILockerAvailabilityManager {
public:
    virtual ~ILockerAvailabilityManager() = default;

    /** Assign a locker to a packageId (assuming the size of the package fits) for the given duration, if possible */
    virtual bool assignLocker(PackageId packageId, DateTime startTime, DateTime endTime) = 0;

    /** Free the locker assigned to a packageId */
    virtual void freeLocker(PackageId packageId) = 0;

    /** Get the locker id assigned to a packageId */
    virtual OperationStatus<LockerId> getLockerIdForPackage(PackageId packageId) = 0;
};

#endif // I_LOCKER_AVAILABILITY_MANAGER_HPP