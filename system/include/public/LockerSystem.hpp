#ifndef LOCKER_SYSTEM_HPP
#define LOCKER_SYSTEM_HPP

#include <vector>
#include <memory>
#include "Types.hpp"

class ILockerFinder;
class IPackageLocationManager;
class ILockerStationRepository;

/** Singleton class for customers and delivery agents to interact with the locker system */
class LockerSystem {
public:
    /** Get the singleton instance of the LockerSystem */
    static LockerSystem& getInstance();

    /** Find locker stations near the given location */
    std::vector<LockerStationDetails> findLockersNearLocation(Location location, double radius);

    /** Choose a locker station to store a package for the given duration */
    OperationStatus<bool> storePackage(const Package& package, LockerStationId lockerStationId, DateTime fromTime, DateTime toTime);

    /** Get the locker station where a package is stored */
    OperationStatus<LockerStationDetails> getLockerStationForPackage(PackageId packageId);

    /** Open the locker to retrieve a package */
    OperationStatus<bool> openLocker(LockerStationId lockerStationId, LockerPickupCode code);

    /** Deliver a package to the locker station */
    OperationStatus<bool> deliverPackage(LockerStationId lockerStationId, PackageId packageId);

private:
    friend class LockerSystemAdmin;

    std::unique_ptr<ILockerFinder> lockerFinder;
    std::unique_ptr<IPackageLocationManager> packageManager;
    std::unique_ptr<ILockerStationRepository> lockerStationRepository;

    LockerSystem(std::unique_ptr<ILockerFinder> lockerFinder, std::unique_ptr<IPackageLocationManager> packageManager, std::unique_ptr<ILockerStationRepository> lockerStationRepository);
    LockerSystem(const LockerSystem&) = delete;
    LockerSystem& operator=(const LockerSystem&) = delete;
};


#endif // LOCKER_SYSTEM_HPP