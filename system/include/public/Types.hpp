#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <string>
#include <chrono>

/** Represents a location on the Earth's surface */
struct Location {
    double latitude;
    double longitude;
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
    ExtraLarge
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

#endif // TYPES_HPP