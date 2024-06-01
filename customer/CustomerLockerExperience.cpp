#include <iostream>
#include "CustomerLockerExperience.hpp"
#include "../system/include/public/LockerSystem.hpp"

CustomerLockerExperience::CustomerLockerExperience(UserId userId, std::string name, std::string email, Location location)
    : userId(userId), name(name), email(email), location(location) {}

OperationStatus<bool> CustomerLockerExperience::checkoutFromShoppingCart(double radius, const Package& package, DateTime estimatedDeliveryTime) {
    auto& lockerSystem = LockerSystem::getInstance();
    const auto lockerStations = lockerSystem.findLockersNearLocation(location, radius);
    if (lockerStations.empty()) {
        return OperationStatus<bool>("Failed to find locker stations nearby");
    }

    std::cout << "Nearby locker stations: " << std::endl;
    for (int i = 0; i < lockerStations.size(); i++) {
        std::cout << (i + 1) << ". " << lockerStations[i].name << ": " << lockerStations[i].location << std::endl;
    }

    int numTries = 5;
    while (numTries-- > 0) {

        std::cout << "Select a locker station (input the number of the station and press enter):";
        int stationIndex;
        std::cin >> stationIndex;
        if (stationIndex < 1 || stationIndex > lockerStations.size()) {
            std::cout << "Invalid station number. Please try again." << std::endl;
            continue;
        }

        const auto storeStatus = lockerSystem.storePackage(
            package,
            lockerStations[stationIndex - 1].id,
            estimatedDeliveryTime - reservationDurationPriorToETA,
            estimatedDeliveryTime + storageDuration
        );
        if (!storeStatus.success) {
            std::cout << "Failed to store package: " << storeStatus.message << std::endl;
            std::cout << "Try again? (y/n): ";
            char tryAgain;
            std::cin >> tryAgain;
            if (tryAgain != 'y') {
                return OperationStatus<bool>(false);
            } else {
                continue;
            }
        }

        packageToLockerStation[package.id] = lockerStations[stationIndex - 1].id;
        return OperationStatus<bool>(true);
    }

    std::cout << "Failed to select a locker station after multiple tries" << std::endl;
    return OperationStatus<bool>(false);
}

OperationStatus<bool> CustomerLockerExperience::collectPackage(PackageId packageId) {
    const auto it = packageToLockerStation.find(packageId);
    if (it == packageToLockerStation.end()) {
        return OperationStatus<bool>("User has not ordered package " + std::to_string(packageId));
    }

    const auto status = LockerSystem::getInstance().openLocker(it->second, packageId);
    if (status.success) {
        packageToLockerStation.erase(it);
    }
    return status;
}