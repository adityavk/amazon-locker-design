#ifndef LOCKER_CODE_MANAGER_FACTORY_HPP
#define LOCKER_CODE_MANAGER_FACTORY_HPP

#include <memory>
#include "../interfaces/ILockerCodeManager.hpp"
#include "../RandomLockerCodeManager.hpp"

enum class LockerCodeManagerStrategy {
    Random,
};

class LockerCodeManagerFactory {
public:
    template <typename... Args>
    static std::unique_ptr<ILockerCodeManager> createLockerCodeManager(LockerCodeManagerStrategy strategy, Args... args) {
        switch (strategy) {
            case LockerCodeManagerStrategy::Random:
                return std::make_unique<RandomLockerCodeManager>(args...);
            default:
                return nullptr;
        }
    }
};

#endif // LOCKER_CODE_MANAGER_FACTORY_HPP