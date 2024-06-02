#ifndef CUSTOMER_LOCKER_SERVICE_HPP
#define CUSTOMER_LOCKER_SERVICE_HPP

#include <chrono>
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
    static constexpr auto STORAGE_DURATION = std::chrono::hours(3 * 24);
    static constexpr auto RESERVATION_DURATION_PRIOR_TO_ETA = std::chrono::hours(24);
public:
    CustomerLockerExperience(UserId userId, std::string name, std::string email, Location location);

    /** Initiate the checkout process for a package to be stored in a locker by finding locker stations nearby within a given radius (in meters) */
    std::vector<LockerStationDetails> findNearbyLockerStations(double radius) const;

    /** Choose a locker station to store a package */
    OperationStatus<bool> checkoutPackage(Package& package, LockerStationId lockerStationId) const;

    /** Collect a package from a locker */
    OperationStatus<Package> collectPackage(PackageId packageId) const;

    /** Get the user ID */
    UserId getUserId() const {
        return userId;
    }

    /** Get the user name */
    std::string getName() const {
        return name;
    }

    /** Get the user location */
    Location getLocation() const {
        return location;
    }
};

#endif // CUSTOMER_LOCKER_SERVICE_HPP