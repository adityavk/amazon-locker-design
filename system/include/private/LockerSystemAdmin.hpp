#ifndef LOCKER_SYSTEM_ADMIN_HPP
#define LOCKER_SYSTEM_ADMIN_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include "../public/Types.hpp"

class LockerSystemAdmin {
    std::string adminId;
    std::string name;
public:
    LockerSystemAdmin(std::string adminId, std::string name);

    void addLockerStation(LockerStationId id, Location location, std::string name, std::unordered_map<PackageSize, uint32_t> lockerCounts);
    void removeLockerStation(LockerStationId id);
};

#endif // LOCKER_SYSTEM_ADMIN_HPP