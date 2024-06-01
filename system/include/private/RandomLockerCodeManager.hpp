#ifndef RANDOM_LOCKER_CODE_MANAGER_HPP
#define RANDOM_LOCKER_CODE_MANAGER_HPP

#include <unordered_map>
#include "interfaces/ILockerCodeManager.hpp"

class RandomLockerCodeManager : public ILockerCodeManager {
    std::unordered_map<LockerPickupCode, std::pair<PackageId, LockerId>> pickupCodeToPackageAndLocker;
public:
    LockerPickupCode generatePickupCode(PackageId packageId, LockerId lockerId) override;
    OperationStatus<std::pair<PackageId, LockerId>> getLockerIdForPickupCode(LockerPickupCode pickupCode) override;
    void removePickupCode(LockerPickupCode pickupCode) override;
};

#endif // RANDOM_LOCKER_CODE_MANAGER_HPP