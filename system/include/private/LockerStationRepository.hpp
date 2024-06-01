#ifndef LOCKER_STATION_REPOSITORY_HPP
#define LOCKER_STATION_REPOSITORY_HPP

#include <unordered_map>
#include <memory>
#include "interfaces/ILockerStationRepository.hpp"

class LockerStationRepository : public ILockerStationRepository {
    std::unordered_map<LockerStationId, std::unique_ptr<LockerStation>> lockerStations;
public:
    std::vector<LockerStationDetails> getAllLockerStations() override;
    OperationStatus<LockerStation*> getLockerStationById(LockerStationId lockerStationId) override;
    OperationStatus<bool> addLockerStation(std::unique_ptr<LockerStation> lockerStation) override;
    OperationStatus<bool> removeLockerStation(LockerStationId lockerStationId) override;
};

#endif // LOCKER_STATION_REPOSITORY_HPP