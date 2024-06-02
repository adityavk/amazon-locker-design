#ifndef I_LOCKER_AVAILABILITY_MANAGER_HPP
#define I_LOCKER_AVAILABILITY_MANAGER_HPP

#include <cstdint>
#include <memory>
#include "../../public/Types.hpp"
#include "../PrivateTypes.hpp"

/** Information about a package for which a locker has been reserved */
struct ReservedPackage {
    Package package;
    LockerId lockerId;
    DateTime startTime;
    DateTime endTime;
};

/** Interface to manage the availability of all lockers in a locker station */
class ILockerAvailabilityManager {
public:
    virtual ~ILockerAvailabilityManager() = default;

    /** Assign a locker to a package (making sure that the size of the package fits) for the given duration, if possible */
    virtual bool assignLocker(const Package& package, DateTime startTime, DateTime endTime) = 0;

    /** Free the locker assigned to a packageId */
    virtual void freeLocker(PackageId packageId) = 0;

    /** Get a package for which a locker has been reserved */
    virtual OperationStatus<std::unique_ptr<ReservedPackage>> getReservedPackage(PackageId packageId) = 0;
};

#endif // I_LOCKER_AVAILABILITY_MANAGER_HPP