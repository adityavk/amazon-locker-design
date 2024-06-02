#include <iostream>
#include "system/include/public/LockerSystem.hpp"
#include "system/include/admin/LockerSystemAdmin.hpp"
#include "customer/CustomerLockerExperience.hpp"
#include "delivery/DeliveryAgent.hpp"

class MainHelper {
    struct LockerStationConfig {
        LockerStationId id;
        Location location;
        std::string name;
        std::vector<LockerConfig> lockers;

        LockerStationConfig(LockerStationId id, const Location& location, const std::string& name, std::vector<LockerConfig> lockers)
            : id(id), location(location), name(name), lockers(std::move(lockers)) {}
    };

    bool debug;
public:
    MainHelper(bool debug): debug(debug) {}

    LockerSystemAdmin createAdmin(std::vector<LockerStationConfig> stations) {
        LockerSystemAdmin admin(
            "admin", "admin",
            NotificationManagerType::Basic, LockerFinderStrategy::Distance,
            LockerAvailabilityManagerStrategy::IntervalBased, LockerCodeManagerStrategy::Random
        );
        for (const auto& station : stations) {
            admin.addLockerStation(station.id, station.location, station.name, station.lockers);
            if (debug) {
                std::cout << "Added locker station "<< station.id << ": " << station.name << " at " << station.location << std::endl;
            }
        }
        if (debug) {
            std::cout << "Created admin" << std::endl;
        }
        return admin;
    }

    CustomerLockerExperience createCustomer(UserId userId, const std::string& name, const std::string& email, const Location& location) {
        const auto customer = CustomerLockerExperience(userId, name, email, location);
        if (debug) {
            std::cout << "Created customer " << name << " at " << location << std::endl;
        }
        return customer;
    }

    DeliveryAgent createAgent(const std::string& name, const std::string& agentId) {
        const auto agent = DeliveryAgent(name, agentId);
        if (debug) {
            std::cout << "Created agent " << name << std::endl;
        }
        return agent;
    }

    std::vector<LockerStationDetails> getNearbyLockerStations(CustomerLockerExperience& customer, double radius) {
        const auto lockerStations = customer.findNearbyLockerStations(radius);
        if (debug) {
            std::cout << "Locker stations near customer: " << customer.getName() << " within " << radius / 1000.0 << " km: ";
            for (const auto& station : lockerStations) {
                std::cout << station.name << ": " << station.location << ", ";
            }
            std::cout << std::endl;
        }
        return lockerStations;
    }

    Package createPackage(PackageId packageId, const CustomerLockerExperience& customer, PackageSize size, std::chrono::system_clock::time_point estimatedDeliveryTime) {
        return Package { packageId, customer.getUserId(), 0, PackageStatus::Pending, size, estimatedDeliveryTime, 0 };
    }

    LockerStationId chooseRandomLockerStation(const std::vector<LockerStationDetails>& stations) {
        return stations[rand() % stations.size()].id;
    }

    OperationStatus<bool> checkoutPackage(CustomerLockerExperience& customer, Package& package, LockerStationId lockerStationId) {
        if (debug) {
            std::cout << "Trying to store package " << package.id << " from customer " << customer.getName() << " at locker station " << lockerStationId << "..." << std::endl;
        }
        const auto status = customer.checkoutPackage(package, lockerStationId);
        if (debug) {
            if (status.success) {
                std::cout << "Stored package " << package.id << " at locker station " << lockerStationId << std::endl;
            } else {
                std::cerr << "Failed to store package " << package.id << ": " << status.errorMessage << std::endl;
            }
        }
        return status;
    }

    OperationStatus<Package> collectPackage(CustomerLockerExperience& customer, PackageId packageId) {
        const auto collected = customer.collectPackage(packageId);
        if (debug) {
            if (collected.success) {
                std::cout << "Collected package " << packageId << std::endl;
            } else {
                std::cerr << "Failed to collect package " << packageId << ": " << collected.errorMessage << std::endl;
            }
        }
        return collected;
    }
};

int main() {
    std::cout << "Welcome to the locker system, initializing..." << std::endl;

    const Location TECH_SQUARE_ATLANTA(33.7769, -84.393, "Tech Square, Atlanta");
    const Location OIE_GATECH(33.772180, -84.395460, "OIE, Georgia Tech");
    const Location CAMPUS_RECREATION_CENTER(33.7757, -84.404243, "Campus Recreation Center, Georgia Tech");
    const Location MERCEDES_BENZ_STADIUM(33.754589, -84.401779, "Mercedes-Benz Stadium, Atlanta");

    MainHelper helper(true);

    LockerSystemAdmin admin = helper.createAdmin({
        { 1, TECH_SQUARE_ATLANTA, "Tech Square Locker Station", {
            LockerConfig(1, LockerSize::Small),
            LockerConfig(2, LockerSize::Medium),
            LockerConfig(3, LockerSize::Large),
            LockerConfig(4, LockerSize::Small),
            LockerConfig(5, LockerSize::Medium),
            LockerConfig(6, LockerSize::Large),
            LockerConfig(7, LockerSize::Small),
            LockerConfig(8, LockerSize::Medium),
            LockerConfig(9, LockerSize::Large)
        }},
        { 2, MERCEDES_BENZ_STADIUM, "Mercedes-Benz Stadium Locker Station", {
            LockerConfig(1, LockerSize::Small),
            LockerConfig(2, LockerSize::Medium),
            LockerConfig(3, LockerSize::Small),
            LockerConfig(4, LockerSize::Medium)
        }}
    });

    admin.initializeSystem();
    std::cout << "System initialized!" << std::endl;

    CustomerLockerExperience customer1 = helper.createCustomer(42, "Alice", "alice@abc.com", OIE_GATECH);
    CustomerLockerExperience customer2 = helper.createCustomer(43, "Bob", "bob@abc.com", CAMPUS_RECREATION_CENTER);
    DeliveryAgent agent1 = helper.createAgent("John", "agent1");

    const auto stations1 = helper.getNearbyLockerStations(customer1, 4 * 1000);
    const auto stations2 = helper.getNearbyLockerStations(customer2, 2 * 1000);

    Package customer1Package1 = helper.createPackage(
        101, customer1, PackageSize::Small,
        DateTime::clock::now() + std::chrono::hours(48)
    );
    Package customer1Package2 = helper.createPackage(
        105, customer1, PackageSize::Large,
        DateTime::clock::now() + std::chrono::hours(48)
    );
    Package customer2Package1 = helper.createPackage(
        102, customer2, PackageSize::Medium,
        DateTime::clock::now() + std::chrono::hours(48)
    );
    Package customer2Package2 = helper.createPackage(
        103, customer2, PackageSize::Large,
        DateTime::clock::now() + std::chrono::hours(48)
    );

    helper.checkoutPackage(customer1, customer1Package1, helper.chooseRandomLockerStation(stations1));
    helper.checkoutPackage(customer2, customer2Package1, helper.chooseRandomLockerStation(stations2));
    helper.checkoutPackage(customer1, customer1Package2, helper.chooseRandomLockerStation(stations1));
    helper.checkoutPackage(customer2, customer2Package2, helper.chooseRandomLockerStation(stations2));

    agent1.completeDelivery(customer1Package1);
    agent1.completeDelivery(customer2Package2);
    agent1.completeDelivery(customer2Package1);

    helper.collectPackage(customer1, customer1Package1.id);
    helper.collectPackage(customer2, customer2Package1.id);
    helper.collectPackage(customer1, customer1Package2.id);
    helper.collectPackage(customer2, customer2Package2.id);

    return 0;
}
