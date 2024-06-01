#ifndef INTERVAL_BASED_LOCKER_AVAILABILITY_MANAGER_HPP
#define INTERVAL_BASED_LOCKER_AVAILABILITY_MANAGER_HPP

#include <optional>
#include <set>
#include <unordered_map>
#include "interfaces/ILockerAvailabilityManager.hpp"

struct FreeInterval {
    DateTime startTime;
    DateTime endTime;
    LockerId lockerId;

    FreeInterval(DateTime startTime, DateTime endTime, LockerId lockerId)
        : startTime(startTime), endTime(endTime), lockerId(lockerId) {}

    bool operator<(const FreeInterval& other) const {
        return startTime < other.startTime || (startTime == other.startTime && endTime < other.endTime);
    }
};

using LockerSize = PackageSize;

struct LockerConfig {
    LockerId lockerId;
    LockerSize lockerSize;
};

class IntervalBasedLockerAvailabilityManager : public ILockerAvailabilityManager {
    using FreeIntervals = std::set<FreeInterval>;
    std::unordered_map<PackageId, ReservedPackage> packageToReservedLocker;
    std::unordered_map<LockerId, LockerSize> lockerIdToSize;
    std::array<FreeIntervals, static_cast<size_t>(LockerSize::Invalid)> freeIntervalsPerSize;
    std::optional<LockerId> reserveLocker(LockerSize lockerSize, DateTime startTime, DateTime endTime);
public:
    IntervalBasedLockerAvailabilityManager(const std::vector<LockerConfig>& lockers);
    bool assignLocker(const Package& package, DateTime startTime, DateTime endTime) override;
    void freeLocker(PackageId packageId) override;
    OperationStatus<ReservedPackage> getReservedPackage(PackageId packageId) override;
};

#endif // INTERVAL_BASED_LOCKER_AVAILABILITY_MANAGER_HPP