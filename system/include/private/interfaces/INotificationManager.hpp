#ifndef I_NOTIFICATION_MANAGER_HPP
#define I_NOTIFICATION_MANAGER_HPP

#include <cstdint>
#include "../public/Types.hpp"

/** Interface for managing user notifications */
class INotificationManager {
public:
    virtual ~INotificationManager() = default;

    /** Send a notification to a user */
    virtual void sendNotification(UserId userId, std::string message) = 0;
};

#endif // I_NOTIFICATION_MANAGER_HPP