#include "../include/public/LockerSystem.hpp"
#include "../include/private/interfaces/ILockerFinder.hpp"
#include "../include/private/interfaces/ILockerStationRepository.hpp"

LockerSystem::LockerSystem(
    std::unique_ptr<ILockerFinder> lockerFinder,
    std::unique_ptr<ILockerStationRepository> lockerStationRepository,
    std::shared_ptr<INotificationManager> notificationManager
) : lockerFinder(std::move(lockerFinder)),
    lockerStationRepository(std::move(lockerStationRepository)), notificationManager(notificationManager) {}

void LockerSystem::initialize(
    std::unique_ptr<ILockerFinder> lockerFinder,
    std::unique_ptr<ILockerStationRepository> lockerStationRepository,
    std::shared_ptr<INotificationManager> notificationManager
) {
    instance = std::make_unique<LockerSystem>(std::move(lockerFinder), std::move(lockerStationRepository), notificationManager);
}

LockerSystem& LockerSystem::getInstance() {
    // We are assured that the instance is created only once by the LockerSystemAdmin instance before any other class can access it
    return *instance;
}

std::vector<LockerStationDetails> LockerSystem::findLockersNearLocation(Location location, double radius) const {
    return lockerFinder->findLockersNearLocation(location, radius, lockerStationRepository.get());
}

OperationStatus<bool> LockerSystem::storePackage(Package& package, LockerStationId lockerStationId, DateTime fromTime, DateTime toTime) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>(std::move(lockerStationStatus.message));
    }

    const auto lockerStation = lockerStationStatus.result;
    auto result = lockerStation->assignLocker(package, fromTime, toTime);
    if (!result.success) {
        return OperationStatus<bool>(std::move(result.message));
    }

    package.lockerStationId = lockerStationId;
    return OperationStatus<bool>(true);
}

OperationStatus<bool> LockerSystem::openLocker(LockerStationId lockerStationId, LockerPickupCode code) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>(std::move(lockerStationStatus.message));
    }

    const auto lockerStation = lockerStationStatus.result;
    return lockerStation->openLocker(code);
}

OperationStatus<bool> LockerSystem::deliverPackage(LockerStationId lockerStationId, PackageId packageId) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>(std::move(lockerStationStatus.message));
    }

    const auto lockerStation = lockerStationStatus.result;
    return lockerStation->deliverPackage(packageId);
}

OperationStatus<bool> LockerSystem::subscribeToNotifications(UserId userId, NotificationHandler handler) const {
    return notificationManager->subscribeToNotifications(userId, std::move(handler));
}
