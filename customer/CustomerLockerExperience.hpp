#ifndef CUSTOMER_LOCKER_SERVICE_HPP
#define CUSTOMER_LOCKER_SERVICE_HPP

#include <string>
#include <unordered_map>
#include "../system/include/public/Types.hpp"

/** A small part of the customer only to interact with locker stations */
class CustomerLockerExperience {
    UserId userId;
    std::string name;
    std::string email;
    Location location;
    std::unordered_map<PackageId, std::pair<LockerStationId, LockerPickupCode>> packageCollectionDetails;
    const std::chrono::days storageDuration = std::chrono::days(3);
    const std::chrono::days reservationDurationPriorToETA = std::chrono::days(1);
public:
    CustomerLockerExperience(UserId userId, std::string name, std::string email, Location location);

    /** Initiate the checkout process for a package to be stored in a locker */
    std::vector<LockerStationDetails> findNearbyLockerStations(double radius);

    /** Choose a locker station to store a package */
    OperationStatus<bool> storePackage(Package& package, LockerStationId lockerStationId);

    /** Collect a package from a locker */
    OperationStatus<Package> collectPackage(PackageId packageId);
};

#endif // CUSTOMER_LOCKER_SERVICE_HPP