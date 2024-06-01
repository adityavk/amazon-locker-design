#ifndef DELIVERY_AGENT_HPP
#define DELIVERY_AGENT_HPP

#include <string>
#include <unordered_map>
#include "../system/include/public/Types.hpp"
#include "../system/include/public/LockerSystem.hpp"

class DeliveryAgent {
    std::string name;
    std::string agentId;
public:
    DeliveryAgent(std::string name, std::string agentId): name(name), agentId(agentId) {}

    /** Finish delivery of a package */
    OperationStatus<bool> completeDelivery(Package& package) {
        return LockerSystem::getInstance().deliverPackage(package.lockerStationId, package.id);
    }
};

#endif // DELIVERY_AGENT_HPP