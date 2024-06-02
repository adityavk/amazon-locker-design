#ifndef TYPES_HPP
#define TYPES_HPP

#include <chrono>
#include <cstdint>
#include <functional>
#include <ostream>
#include <string>

/** Represents a location on the Earth's surface */
struct Location {
    double latitude;
    double longitude;
    std::string address;

    Location(double latitude, double longitude, std::string address) : latitude(latitude), longitude(longitude), address(address) {}

    friend std::ostream& operator<<(std::ostream& os, const Location& location) {
        os << location.address;
        return os;
    }

    double distanceTo(const Location& other) const {
        double lat1 = latitude;
        double lon1 = longitude;
        double lat2 = other.latitude;
        double lon2 = other.longitude;

        // Haversine formula
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;

        lat1 = lat1 * M_PI / 180.0;
        lat2 = lat2 * M_PI / 180.0;

        double a = std::pow(std::sin(dLat / 2), 2) + std::pow(std::sin(dLon / 2), 2) * std::cos(lat1) * std::cos(lat2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

        return 6371000 * c;
    }
};

/** Date-time representation */
using DateTime = std::chrono::system_clock::time_point;

/** Pick-up code for a package */
using LockerPickupCode = uint64_t;

/** Status of a package */
enum class PackageStatus {
    Pending,
    InTransit,
    Delivered,
    Collected,
    Cancelled
};

/** Size of a package */
enum class PackageSize {
    Small,
    Medium,
    Large,
    ExtraLarge,
    Invalid
};

/** ID of a package */
using PackageId = uint64_t;

/** User's internal ID */
using UserId = uint64_t;

/** Order's internal ID */
using OrderId = uint64_t;

/** Locker station ID */
using LockerStationId = uint64_t;

/** Represents a package */
struct Package {
    PackageId id;
    UserId userId;
    OrderId orderId;
    PackageStatus status;
    PackageSize size;
    DateTime estimatedDeliveryTime;
    LockerStationId lockerStationId;
};

/** Represents a Locker station */
struct LockerStationDetails {
    LockerStationId id;
    Location location;
    std::string name;

    LockerStationDetails(LockerStationId id, Location location, std::string name) : id(id), location(location), name(std::move(name)) {}
};

/** Common response type for operations to indicate success (with result object) or failure (with error message) */
template <typename T>
struct OperationStatus {
    bool success;
    std::string message;
    T result;

    OperationStatus(T result) : success(true), result(result) {}
    OperationStatus(std::string message) : success(false), message(message) {}
};

using NotificationHandler = std::function<void(std::string)>;

#endif // TYPES_HPP