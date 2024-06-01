#ifndef PACKAGE_LOCATION_MANAGER_HPP
#define PACKAGE_LOCATION_MANAGER_HPP

#include <unordered_map>
#include "interfaces/IPackageLocationManager.hpp"

class PackageLocationManager : public IPackageLocationManager {
    std::unordered_map<PackageId, LockerStationId> packageToLockerStation;
public:
    OperationStatus<LockerStationDetails> getLockerStationForPackage(PackageId packageId) override;
    void setLockerStationForPackage(PackageId packageId, LockerStationId lockerStationId) override;
    void removeLockerStationForPackage(PackageId packageId) override;
};

#endif // PACKAGE_LOCATION_MANAGER_HPP