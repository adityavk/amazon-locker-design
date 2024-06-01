#include "../include/private/LockerStation.hpp"

LockerStation::LockerStation(
        LockerStationId id, Location location, std::string name,
        std::unique_ptr<ILockerCodeManager> lockerCodeManager,
        std::shared_ptr<INotificationManager> notificationManager,
        std::unique_ptr<ILockerAvailabilityManager> lockerAvailabilityManager
    )
    :   details(id, location, name),
        lockerCodeManager(std::move(lockerCodeManager)),
        notificationManager(notificationManager),
        lockerAvailabilityManager(std::move(lockerAvailabilityManager)) {}

LockerStationDetails LockerStation::getDetails() const {
    return details;
}

OperationStatus<bool> LockerStation::assignLocker(const Package& package, DateTime fromTime, DateTime toTime) {
    if (lockerAvailabilityManager->assignLocker(package, fromTime, toTime)) {
        return OperationStatus<bool>(true);
    }
    return OperationStatus<bool>("No locker available");
}

OperationStatus<bool> LockerStation::deliverPackage(PackageId packageId) {
    auto packageDetailsStatus = lockerAvailabilityManager->getReservedPackage(packageId);
    if (!packageDetailsStatus.success) {
        return OperationStatus<bool>(std::move(packageDetailsStatus.message));
    }

    auto& packageDetails = packageDetailsStatus.result;
    packageDetails.package.status = PackageStatus::Delivered;
    const auto code = lockerCodeManager->generatePickupCode(packageId, packageDetails.lockerId);
    notificationManager->sendNotification(packageDetails.package.userId, "Package delivered to locker " + details.name + ". Pickup code: " + std::to_string(code));
    return OperationStatus<bool>(true);
}

OperationStatus<bool> LockerStation::openLocker(LockerPickupCode code) {
    auto lockerIdStatus = lockerCodeManager->getLockerIdForPickupCode(code);
    if (!lockerIdStatus.success) {
        return OperationStatus<bool>(std::move(lockerIdStatus.message));
    }

    const auto [packageId, lockerId] = lockerIdStatus.result;
    auto packageDetailsStatus = lockerAvailabilityManager->getReservedPackage(packageId);
    if (!packageDetailsStatus.success) {
        return OperationStatus<bool>(std::move(packageDetailsStatus.message));
    }

    notificationManager->sendNotification(packageDetailsStatus.result.package.userId, "Package picked up from locker " + details.name);
    lockerCodeManager->removePickupCode(code);
    lockerAvailabilityManager->freeLocker(packageId);
    return OperationStatus<bool>(true);
}

