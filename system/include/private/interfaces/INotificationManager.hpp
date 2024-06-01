#ifndef I_NOTIFICATION_MANAGER_HPP
#define I_NOTIFICATION_MANAGER_HPP

#include <cstdint>
#include "../../public/Types.hpp"

/** Interface for managing user notifications */
class INotificationManager {
public:
    virtual ~INotificationManager() = default;

    /** Send a notification to a user */
    virtual OperationStatus<bool> sendNotification(UserId userId, std::string message) = 0;

    /** Subscribe to notifications for a user */
    virtual OperationStatus<bool> subscribeToNotifications(UserId userId, NotificationHandler handler) = 0;
};

#endif // I_NOTIFICATION_MANAGER_HPP