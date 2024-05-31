#include "DeliveryAgent.hpp"
#include "../system/include/public/LockerSystem.hpp"

DeliveryAgent::DeliveryAgent(std::string name, std::string agentId) : name(name), agentId(agentId) {}

OperationStatus<bool> DeliveryAgent::startDelivery(PackageId packageId) {
    auto& lockerSystem = LockerSystem::getInstance();
    auto lockerStationStatus = lockerSystem.getLockerStationForPackage(packageId);
    if (!lockerStationStatus.success) {
        return OperationStatus<bool>(std::move(lockerStationStatus.message));
    }
    packageToLockerStation[packageId] = std::move(lockerStationStatus.result);
    return OperationStatus<bool>(true);
}

OperationStatus<bool> DeliveryAgent::completeDelivery(PackageId packageId) {
    const auto it = packageToLockerStation.find(packageId);
    if (it == packageToLockerStation.end()) {
        return OperationStatus<bool>("Package not picked up by Agent " + name);
    }
    LockerSystem::getInstance().deliverPackage(it->second, packageId);
    packageToLockerStation.erase(it);
    return OperationStatus<bool>(true);
}
