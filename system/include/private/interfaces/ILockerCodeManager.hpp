#ifndef I_LOCKER_CODE_MANAGER_HPP
#define I_LOCKER_CODE_MANAGER_HPP

#include <cstdint>
#include <utility>
#include "../../public/Types.hpp"
#include "../PrivateTypes.hpp"

/** Interface for managing pickup codes for a locker station */
class ILockerCodeManager {
public:
    virtual ~ILockerCodeManager() = default;

    /** Generate a new pickup code for a package */
    virtual LockerPickupCode generatePickupCode(PackageId packageId, LockerId lockerId) = 0;

    /** Get the locker id and package id for a pickup code */
    virtual OperationStatus<std::pair<PackageId, LockerId>> getLockerIdForPickupCode(LockerPickupCode pickupCode) = 0;

    /** Remove a pickup code */
    virtual void removePickupCode(LockerPickupCode pickupCode) = 0;
};

#endif // I_LOCKER_CODE_MANAGER_HPP