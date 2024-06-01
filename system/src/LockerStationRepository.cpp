#include "../include/private/LockerStationRepository.hpp"
#include <algorithm>

std::vector<LockerStationDetails> LockerStationRepository::getAllLockerStations() {
    return std::transform(lockerStations.begin(), lockerStations.end(), std::vector<LockerStationDetails>(), [](const auto& pair) {
        return pair.second->getDetails();
    });
}

OperationStatus<LockerStation*> LockerStationRepository::getLockerStationById(LockerStationId lockerStationId) {
    if (const auto it = lockerStations.find(lockerStationId); it != lockerStations.end()) {
        return OperationStatus<LockerStation*>(it->second.get());
    }
    return OperationStatus<LockerStation*>(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " not found");
}

OperationStatus<bool> LockerStationRepository::addLockerStation(std::unique_ptr<LockerStation> lockerStation) {
    const auto lockerStationId = lockerStation->getDetails().id;
    if (lockerStations.find(lockerStationId) != lockerStations.end()) {
        return OperationStatus<bool>(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " already exists");
    }
    lockerStations.emplace(lockerStationId, std::move(lockerStation));
    return OperationStatus<bool>(true);
}

OperationStatus<bool> LockerStationRepository::removeLockerStation(LockerStationId lockerStationId) {
    if (lockerStations.erase(lockerStationId) == 0) {
        return OperationStatus<bool>(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " not found");
    }
    return OperationStatus<bool>(true);
}


