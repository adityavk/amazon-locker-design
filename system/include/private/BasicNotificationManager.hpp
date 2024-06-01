#ifndef BASIC_NOTIFICATION_MANAGER_HPP
#define BASIC_NOTIFICATION_MANAGER_HPP

#include <functional>
#include <unordered_map>
#include "interfaces/INotificationManager.hpp"

class BasicNotificationManager : public INotificationManager {
    std::unordered_map<UserId, NotificationHandler> userToNotificationHandler;
public:
    OperationStatus<bool> sendNotification(UserId userId, std::string message) override;
    OperationStatus<bool> subscribeToNotifications(UserId userId, NotificationHandler handler) override;
};

#endif // BASIC_NOTIFICATION_MANAGER_HPP