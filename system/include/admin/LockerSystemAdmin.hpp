#ifndef LOCKER_SYSTEM_ADMIN_HPP
#define LOCKER_SYSTEM_ADMIN_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include "../public/Types.hpp"
#include "../private/factories/NotificationManagerFactory.hpp"
#include "../private/factories/LockerFinderFactory.hpp"
#include "../private/factories/LockerAvailabilityManagerFactory.hpp"
#include "../private/factories/LockerCodeManagerFactory.hpp"

/** Admin for the locker system */
class LockerSystemAdmin {
    std::string adminId;
    std::string name;
    std::unordered_map<LockerStationId, std::pair<LockerStationDetails, std::vector<LockerConfig>>> lockerStations;
    NotificationManagerType notificationManagerType;
    LockerFinderStrategy lockerFinderStrategy;
    LockerAvailabilityManagerStrategy lockerAvailabilityManagerStrategy;
    LockerCodeManagerStrategy lockerCodeManagerStrategy;
    bool initialized = false;
public:
    LockerSystemAdmin(
        std::string adminId, std::string name,
        NotificationManagerType notificationManagerType,
        LockerFinderStrategy lockerFinderStrategy,
        LockerAvailabilityManagerStrategy lockerAvailabilityManagerStrategy,
        LockerCodeManagerStrategy lockerCodeManagerStrategy
    );

    void addLockerStation(LockerStationId id, Location location, std::string name, std::vector<LockerConfig> lockers);

    void removeLockerStation(LockerStationId id);

    void initializeSystem();
};

#endif // LOCKER_SYSTEM_ADMIN_HPP