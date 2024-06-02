#include <iostream>
#include "CustomerLockerExperience.hpp"
#include "../system/include/public/LockerSystem.hpp"

CustomerLockerExperience::CustomerLockerExperience(UserId userId, std::string name, std::string email, Location location)
    : userId(userId), name(name), email(email), location(location) {
        LockerSystem::getInstance().subscribeToNotifications(userId, [this](std::string message) {
            std::cout << "Received notification: " << message << std::endl;
            // "Package " + std::to_string(package.id) + " delivered to locker " + std::to_string(package.lockerStationId) + ". Pickup code: " + std::to_string(code)
            if (message.find(" delivered to locker ") != std::string::npos) {
                auto packageIdStart = message.find("Package ") + 8;
                auto packageIdEnd = message.find(" delivered to locker ");
                auto lockerStationIdStart = packageIdEnd + 21;
                auto lockerStationIdEnd = message.find(". Pickup code: ");
                auto codeStart = lockerStationIdEnd + 14;
                auto codeEnd = message.size();
                auto packageId = std::stoull(message.substr(packageIdStart, packageIdEnd - packageIdStart));
                auto lockerStationId = std::stoull(message.substr(lockerStationIdStart, lockerStationIdEnd - lockerStationIdStart));
                auto code = std::stoull(message.substr(codeStart, codeEnd - codeStart));
                packageCollectionDetails[packageId] = std::make_pair(lockerStationId, code);
            }
        });
    }

std::vector<LockerStationDetails> CustomerLockerExperience::findNearbyLockerStations(double radius) const {
    return LockerSystem::getInstance().findLockersNearLocation(location, radius);
}

OperationStatus<bool> CustomerLockerExperience::checkoutPackage(Package& package, LockerStationId lockerStationId) const {
    package.userId = userId;
    package.status = PackageStatus::InTransit;
    return LockerSystem::getInstance().storePackage(
        package,
        lockerStationId,
        package.estimatedDeliveryTime - RESERVATION_DURATION_PRIOR_TO_ETA,
        package.estimatedDeliveryTime + STORAGE_DURATION
    );
}

OperationStatus<Package> CustomerLockerExperience::collectPackage(PackageId packageId) const {
    auto packageDetails = packageCollectionDetails.find(packageId);
    if (packageDetails == packageCollectionDetails.end()) {
        return OperationStatus<Package>::fromError("Package not found");
    }
    return LockerSystem::getInstance().openLocker(packageDetails->second.first, packageDetails->second.second);
}