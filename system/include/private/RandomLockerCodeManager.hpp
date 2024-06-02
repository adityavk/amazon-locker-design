#ifndef RANDOM_LOCKER_CODE_MANAGER_HPP
#define RANDOM_LOCKER_CODE_MANAGER_HPP

#include <random>
#include <unordered_map>
#include "interfaces/ILockerCodeManager.hpp"

class RandomLockerCodeManager : public ILockerCodeManager {
    std::unordered_map<LockerPickupCode, std::pair<PackageId, LockerId>> pickupCodeToPackageAndLocker;
    std::uniform_int_distribution<LockerPickupCode> uniformDistribution;
    std::mt19937 randomEngine;
public:
    RandomLockerCodeManager();
    LockerPickupCode generatePickupCode(PackageId packageId, LockerId lockerId) override;
    OperationStatus<std::pair<PackageId, LockerId>> getLockerIdForPickupCode(LockerPickupCode pickupCode) override;
    void removePickupCode(LockerPickupCode pickupCode) override;
};

#endif // RANDOM_LOCKER_CODE_MANAGER_HPP