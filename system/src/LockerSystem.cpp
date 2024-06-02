#include "../include/public/LockerSystem.hpp"
#include "../include/private/interfaces/ILockerFinder.hpp"
#include "../include/private/interfaces/ILockerStationRepository.hpp"

void LockerSystem::initialize(
    std::unique_ptr<ILockerFinder> lockerFinder,
    std::unique_ptr<ILockerStationRepository> lockerStationRepository,
    std::shared_ptr<INotificationManager> notificationManager
) {
    auto& sInstance = getInstance();
    if (sInstance.initialized) {
        throw std::logic_error("LockerSystem is already initialized");
    }
    sInstance.initialized = true;
    sInstance.lockerFinder = std::move(lockerFinder);
    sInstance.lockerStationRepository = std::move(lockerStationRepository);
    sInstance.notificationManager = std::move(notificationManager);
}

LockerSystem& LockerSystem::getInstance() {
    static LockerSystem instance;
    return instance;
}

std::vector<LockerStationDetails> LockerSystem::findLockersNearLocation(Location location, double radius) const {
    return lockerFinder->findLockersNearLocation(location, radius, lockerStationRepository.get());
}

OperationStatus<bool> LockerSystem::storePackage(Package& package, LockerStationId lockerStationId, DateTime fromTime, DateTime toTime) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>::fromError(std::move(lockerStationStatus.errorMessage));
    }

    const auto lockerStation = lockerStationStatus.result;
    auto result = lockerStation->assignLocker(package, fromTime, toTime);
    if (!result.success) {
        return OperationStatus<bool>::fromError(std::move(result.errorMessage));
    }

    package.lockerStationId = lockerStationId;
    return OperationStatus<bool>::fromResult(true);
}

OperationStatus<Package> LockerSystem::openLocker(LockerStationId lockerStationId, LockerPickupCode code) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<Package>::fromError(std::move(lockerStationStatus.errorMessage));
    }

    const auto lockerStation = lockerStationStatus.result;
    return lockerStation->openLocker(code);
}

OperationStatus<bool> LockerSystem::deliverPackage(LockerStationId lockerStationId, Package package) const {
    auto lockerStationStatus = lockerStationRepository->getLockerStationById(lockerStationId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>::fromError(std::move(lockerStationStatus.errorMessage));
    }

    const auto lockerStation = lockerStationStatus.result;
    return lockerStation->deliverPackage(std::move(package));
}

OperationStatus<bool> LockerSystem::subscribeToNotifications(UserId userId, NotificationHandler handler) const {
    return notificationManager->subscribeToNotifications(userId, std::move(handler));
}
