#include "../include/private/LockerSystemAdmin.hpp"
#include "../include/public/LockerSystem.hpp"
#include "../include/private/LockerStation.hpp"
#include "../include/private/PackageLocationManager.hpp"
#include "../include/private/LockerStationRepository.hpp"


LockerSystemAdmin::LockerSystemAdmin(
        std::string adminId, std::string name,
        NotificationManagerType notificationManagerType,
        LockerFinderStrategy lockerFinderStrategy,
        LockerAvailabilityManagerStrategy lockerAvailabilityManagerStrategy,
        LockerCodeManagerStrategy lockerCodeManagerStrategy
    ) : adminId(std::move(adminId)), name(std::move(name)), notificationManagerType(notificationManagerType),
        lockerFinderStrategy(lockerFinderStrategy), lockerAvailabilityManagerStrategy(lockerAvailabilityManagerStrategy),
        lockerCodeManagerStrategy(lockerCodeManagerStrategy) {}

void LockerSystemAdmin::addLockerStation(LockerStationId id, Location location, std::string name, std::vector<LockerConfig> lockers) {
    if (lockerStations.find(id) != lockerStations.end()) {
        throw std::invalid_argument("Locker station with ID " + std::to_string(id) + " already exists");
    }

    lockerStations.emplace(id, std::make_pair(LockerStationDetails(id, location, name), std::move(lockers)));
}

void LockerSystemAdmin::removeLockerStation(LockerStationId id) {
    lockerStations.erase(id);
}

void LockerSystemAdmin::initializeSystem() {
    if (initialized) {
        throw std::logic_error("System already initialized");
    }
    auto lockerFinder = LockerFinderFactory::createLockerFinder(lockerFinderStrategy);
    auto notificationManager = NotificationManagerFactory::createNotificationManager(notificationManagerType);
    auto packageLocationManager = std::make_unique<PackageLocationManager>(lockerFinder);
    auto lockerStationRepository = std::make_unique<LockerStationRepository>(lockerStations);

    for (auto& [id, station] : lockerStations) {
        auto& [details, lockers] = station;
        auto lockerCodeManager = LockerCodeManagerFactory::createLockerCodeManager(lockerCodeManagerStrategy);
        auto lockerAvailabilityManager = LockerAvailabilityManagerFactory::createLockerAvailabilityManager(lockerAvailabilityManagerStrategy, std::move(lockers));

        auto lockerStation = std::make_unique<LockerStation>(id, details.location, details.name, std::move(lockerCodeManager), notificationManager, std::move(lockerAvailabilityManager));
        lockerStationRepository->addLockerStation(std::move(lockerStation));
    }

    LockerSystem::initialize(std::move(lockerFinder), std::move(packageLocationManager), std::move(lockerStationRepository), notificationManager);
    initialized = true;
}