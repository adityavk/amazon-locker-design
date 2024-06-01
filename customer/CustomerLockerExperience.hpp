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
    std::unordered_map<PackageId, LockerStationId> packageToLockerStation;
    const std::chrono::days storageDuration = std::chrono::days(3);
    const std::chrono::days reservationDurationPriorToETA = std::chrono::days(1);
public:
    CustomerLockerExperience(UserId userId, std::string name, std::string email, Location location);

    /** Process checkout from shopping cart to a nearby locker station
     * first displays nearby locker stations, then waits for stdin to select one station
     * if the station is successfully assigned by the system, process is completed
     * otherwise, the customer can try again
     * Returns true if the checkout was eventually successful, false otherwise
     */
    OperationStatus<bool> checkoutFromShoppingCart(double radius, const Package& package, DateTime estimatedDeliveryTime);

    /** Collect a package from a locker */
    OperationStatus<bool> collectPackage(PackageId packageId);
};

#endif // CUSTOMER_LOCKER_SERVICE_HPP