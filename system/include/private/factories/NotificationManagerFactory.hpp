#ifndef NOTIFICATION_MANAGER_FACTORY_HPP
#define NOTIFICATION_MANAGER_FACTORY_HPP

#include <memory>
#include "../interfaces/INotificationManager.hpp"
#include "../BasicNotificationManager.hpp"

enum class NotificationManagerType {
    Basic,
};

class NotificationManagerFactory {
public:
    template <typename... Args>
    static std::shared_ptr<INotificationManager> createNotificationManager(NotificationManagerType type, Args... args) {
        switch (type) {
            case NotificationManagerType::Basic:
                return std::make_shared<BasicNotificationManager>(args...);
            default:
                return nullptr;
        }
    }
};

#endif // NOTIFICATION_MANAGER_FACTORY_HPP