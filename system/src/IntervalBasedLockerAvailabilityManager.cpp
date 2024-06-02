#include "../include/private/IntervalBasedLockerAvailabilityManager.hpp"

IntervalBasedLockerAvailabilityManager::IntervalBasedLockerAvailabilityManager(const std::vector<LockerConfig>& lockers) {
    const auto currentTime = DateTime::clock::now();
    const auto infinteTime = DateTime::max();
    lockerIdToSize.reserve(lockers.size());
    for (const auto& locker : lockers) {
        freeIntervalsPerSize[static_cast<size_t>(locker.lockerSize)].insert(FreeInterval(currentTime, infinteTime, locker.lockerId));
        lockerIdToSize.emplace(locker.lockerId, locker.lockerSize);
    }
}

bool IntervalBasedLockerAvailabilityManager::assignLocker(const Package& package, DateTime startTime, DateTime endTime) {
    for (size_t i = static_cast<size_t>(package.size); i < static_cast<size_t>(LockerSize::Invalid); ++i) {
        const auto lockerId = reserveLocker(static_cast<LockerSize>(i), startTime, endTime);
        if (lockerId.has_value()) {
            packageToReservedLocker[package.id] = ReservedPackage{package, *lockerId, startTime, endTime};
            return true;
        }
    }
    return false;
}

void IntervalBasedLockerAvailabilityManager::freeLocker(PackageId packageId) {
    const auto it = packageToReservedLocker.find(packageId);
    if (it == packageToReservedLocker.end()) {
        return;
    }

    const auto& reservedLocker = it->second;
    auto& freeIntervals = freeIntervalsPerSize[static_cast<size_t>(lockerIdToSize.find(reservedLocker.lockerId)->second)];
    const auto now = DateTime::clock::now();
    if (now < reservedLocker.endTime) {
        freeIntervals.insert(FreeInterval(now, reservedLocker.endTime, reservedLocker.lockerId));
    }
    packageToReservedLocker.erase(it);
}

OperationStatus<std::unique_ptr<ReservedPackage>> IntervalBasedLockerAvailabilityManager::getReservedPackage(PackageId packageId) {
    const auto it = packageToReservedLocker.find(packageId);
    if (it == packageToReservedLocker.end()) {
        return OperationStatus<std::unique_ptr<ReservedPackage>>::fromError("No locker reserved for package " + std::to_string(packageId));
    }
    return OperationStatus<std::unique_ptr<ReservedPackage>>::fromResult(std::make_unique<ReservedPackage>(it->second));
}

std::optional<LockerId> IntervalBasedLockerAvailabilityManager::reserveLocker(LockerSize lockerSize, DateTime startTime, DateTime endTime) {
    auto& freeIntervals = freeIntervalsPerSize[static_cast<size_t>(lockerSize)];

    // Greedily find the first interval that fits
    auto it = freeIntervals.begin();

    while (it != freeIntervals.end() && it->startTime <= startTime && it->endTime < endTime) {
        ++it;
    }

    if (it == freeIntervals.end() || it->startTime > startTime) {
        return std::nullopt;
    }

    const auto lockerId = it->lockerId;
    freeIntervals.erase(it);
    if (it->startTime < startTime) {
        freeIntervals.insert(FreeInterval(it->startTime, startTime, lockerId));
    }
    if (it->endTime > endTime) {
        freeIntervals.insert(FreeInterval(endTime, it->endTime, lockerId));
    }
    return lockerId;
}
