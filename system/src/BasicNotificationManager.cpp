#include "../include/private/BasicNotificationManager.hpp"

OperationStatus<bool> BasicNotificationManager::sendNotification(UserId userId, std::string message) {
    if (const auto it = userToNotificationHandler.find(userId); it != userToNotificationHandler.end()) {
        it->second(std::move(message));
        return OperationStatus<bool>::fromResult(true);
    }
    return OperationStatus<bool>::fromError("User not subscribed to notifications");
}

OperationStatus<bool> BasicNotificationManager::subscribeToNotifications(UserId userId, NotificationHandler handler) {
    if (userToNotificationHandler.find(userId) != userToNotificationHandler.end()) {
        return OperationStatus<bool>::fromError("User already subscribed to notifications");
    }
    userToNotificationHandler.insert({userId, std::move(handler)});
    return OperationStatus<bool>::fromResult(true);
}