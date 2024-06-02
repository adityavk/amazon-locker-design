#ifndef LOCKER_AVAILABILITY_MANAGER_FACTORY_HPP
#define LOCKER_AVAILABILITY_MANAGER_FACTORY_HPP

#include <memory>
#include "../interfaces/ILockerAvailabilityManager.hpp"
#include "../IntervalBasedLockerAvailabilityManager.hpp"

enum class LockerAvailabilityManagerStrategy {
    IntervalBased,
};

class LockerAvailabilityManagerFactory {
public:
    template <typename... Args>
    static std::unique_ptr<ILockerAvailabilityManager> createLockerAvailabilityManager(LockerAvailabilityManagerStrategy strategy, Args... args) {
        switch (strategy) {
            case LockerAvailabilityManagerStrategy::IntervalBased:
                return std::make_unique<IntervalBasedLockerAvailabilityManager>(args...);
            default:
                return nullptr;
        }
    }
};

#endif // LOCKER_AVAILABILITY_MANAGER_FACTORY_HPP