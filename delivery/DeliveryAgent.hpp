#ifndef DELIVERY_AGENT_HPP
#define DELIVERY_AGENT_HPP

#include <string>
#include <unordered_map>
#include "../system/include/public/Types.hpp"

class DeliveryAgent {
    std::string name;
    std::string agentId;
    std::unordered_map<PackageId, LockerStationDetails> packageToLockerStation;
public:
    DeliveryAgent(std::string name, std::string agentId);

    /** Start delivery of a package by finding the locker station */
    OperationStatus<bool> startDelivery(PackageId packageId);

    /** Finish delivery of a package */
    OperationStatus<bool> completeDelivery(PackageId packageId);
};

#endif // DELIVERY_AGENT_HPP