#include "../include/private/LockerStationRepository.hpp"
#include <algorithm>

std::vector<LockerStationDetails> LockerStationRepository::getAllLockerStations() {
    std::vector<LockerStationDetails> result;
    std::transform(lockerStations.begin(), lockerStations.end(), std::back_inserter(result), [](const auto& pair) {
        return pair.second->getDetails();
    });
    return result;
}

OperationStatus<LockerStation*> LockerStationRepository::getLockerStationById(LockerStationId lockerStationId) {
    if (const auto it = lockerStations.find(lockerStationId); it != lockerStations.end()) {
        return OperationStatus<LockerStation*>::fromResult(it->second.get());
    }
    return OperationStatus<LockerStation*>::fromError(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " not found");
}

OperationStatus<bool> LockerStationRepository::addLockerStation(std::unique_ptr<LockerStation> lockerStation) {
    const auto lockerStationId = lockerStation->getDetails().id;
    if (lockerStations.find(lockerStationId) != lockerStations.end()) {
        return OperationStatus<bool>::fromError(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " already exists");
    }
    lockerStations.emplace(lockerStationId, std::move(lockerStation));
    return OperationStatus<bool>::fromResult(true);
}

OperationStatus<bool> LockerStationRepository::removeLockerStation(LockerStationId lockerStationId) {
    if (lockerStations.erase(lockerStationId) == 0) {
        return OperationStatus<bool>::fromError(std::string("Locker station with ID ") + std::to_string(lockerStationId) + " not found");
    }
    return OperationStatus<bool>::fromResult(true);
}


