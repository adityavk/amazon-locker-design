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

/** Represents a package */
struct Package {
    PackageId id;
    UserId userId;
    OrderId orderId;
    PackageStatus status;
    PackageSize size;
};

/** Locker station ID */
using LockerStationId = uint64_t;

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

using NotificationHandler = std::function<void(UserId, std::string)>;

#endif // TYPES_HPP