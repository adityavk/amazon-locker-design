#ifndef LOCKER_SYSTEM_HPP
#define LOCKER_SYSTEM_HPP

#include <vector>
#include <memory>
#include "Types.hpp"

class ILockerFinder;
class ILockerStationRepository;
class INotificationManager;

/** Singleton class for customers and delivery agents to interact with the locker system */
class LockerSystem {
public:
    /** Get the singleton instance of the LockerSystem */
    static LockerSystem& getInstance();

    /** Find locker stations near the given location */
    std::vector<LockerStationDetails> findLockersNearLocation(Location location, double radius) const;

    /** Choose a locker station to store a package for the given duration */
    OperationStatus<bool> storePackage(Package& package, LockerStationId lockerStationId, DateTime fromTime, DateTime toTime) const;

    /** Open the locker to retrieve a package */
    OperationStatus<Package> openLocker(LockerStationId lockerStationId, LockerPickupCode code) const;

    /** Deliver a package to the locker station */
    OperationStatus<bool> deliverPackage(LockerStationId lockerStationId, Package package) const;

    /** Subscribe to system notifications */
    OperationStatus<bool> subscribeToNotifications(UserId userId, NotificationHandler handler) const;

private:
    friend class LockerSystemAdmin;

    static std::unique_ptr<LockerSystem> instance;

    std::unique_ptr<ILockerFinder> lockerFinder;
    std::unique_ptr<ILockerStationRepository> lockerStationRepository;
    std::shared_ptr<INotificationManager> notificationManager;

    LockerSystem(
        std::unique_ptr<ILockerFinder> lockerFinder,
        std::unique_ptr<ILockerStationRepository> lockerStationRepository,
        std::shared_ptr<INotificationManager> notificationManager
    );
    LockerSystem(const LockerSystem&) = delete;
    LockerSystem& operator=(const LockerSystem&) = delete;

    static void initialize(
        std::unique_ptr<ILockerFinder> lockerFinder,
        std::unique_ptr<ILockerStationRepository> lockerStationRepository,
        std::shared_ptr<INotificationManager> notificationManager
    );
};


#endif // LOCKER_SYSTEM_HPP