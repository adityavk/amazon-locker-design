#include "../include/private/RandomLockerCodeManager.hpp"

RandomLockerCodeManager::RandomLockerCodeManager() : uniformDistribution(0, std::numeric_limits<LockerPickupCode>::max()), randomEngine(std::random_device()()) {}

LockerPickupCode RandomLockerCodeManager::generatePickupCode(PackageId packageId, LockerId lockerId) {
    do {
        LockerPickupCode pickupCode = uniformDistribution(randomEngine);
        if (pickupCodeToPackageAndLocker.find(pickupCode) == pickupCodeToPackageAndLocker.end()) {
            pickupCodeToPackageAndLocker[pickupCode] = std::make_pair(packageId, lockerId);
            return pickupCode;
        }
    } while (true);
}

OperationStatus<std::pair<PackageId, LockerId>> RandomLockerCodeManager::getLockerIdForPickupCode(LockerPickupCode pickupCode) {
    if (const auto it = pickupCodeToPackageAndLocker.find(pickupCode); it != pickupCodeToPackageAndLocker.end()) {
        return OperationStatus<std::pair<PackageId, LockerId>>::fromResult(it->second);
    }
    return OperationStatus<std::pair<PackageId, LockerId>>::fromError("Invalid pickup code");
}

void RandomLockerCodeManager::removePickupCode(LockerPickupCode pickupCode) {
    pickupCodeToPackageAndLocker.erase(pickupCode);
}