#ifndef LOCKER_FINDER_FACTORY_HPP
#define LOCKER_FINDER_FACTORY_HPP

#include <memory>
#include "../interfaces/ILockerFinder.hpp"
#include "../DistanceBasedLockerFinder.hpp"

enum class LockerFinderStrategy {
    Distance,
};

class LockerFinderFactory {
public:
    template <typename... Args>
    static std::unique_ptr<ILockerFinder> createLockerFinder(LockerFinderStrategy strategy, Args... args) {
        switch (strategy) {
            case LockerFinderStrategy::Distance:
                return std::make_unique<DistanceBasedLockerFinder>(args...);
            default:
                return nullptr;
        }
    }
};

#endif // LOCKER_FINDER_FACTORY_HPP