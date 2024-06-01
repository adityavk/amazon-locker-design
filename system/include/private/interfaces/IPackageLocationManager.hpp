#ifndef I_PACKAGE_LOCATION_MANAGER_HPP
#define I_PACKAGE_LOCATION_MANAGER_HPP

#include <cstdint>
#include "../../public/Types.hpp"

/** Interface to manage the location (locker station) of packages */
class IPackageLocationManager {
public:
    virtual ~IPackageLocationManager() = default;

    /** Get the locker station where a package is stored */
    virtual OperationStatus<LockerStationDetails> getLockerStationForPackage(PackageId packageId) = 0;

    /** Set the locker station where a package is stored */
    virtual void setLockerStationForPackage(PackageId packageId, LockerStationId lockerStationId) = 0;

    /** Remove the locker station where a package is stored */
    virtual void removeLockerStationForPackage(PackageId packageId) = 0;
};

#endif // I_PACKAGE_LOCATION_MANAGER_HPP