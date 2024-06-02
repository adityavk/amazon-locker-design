#include <iostream>
#include "system/include/public/LockerSystem.hpp"
#include "system/include/admin/LockerStationAdmin.hpp"
#include "customer/CustomerLockerExperience.hpp"
#include "delivery/DeliveryAgent.hpp"

LockerSystemAdmin createAdmin() {
    LockerSystemAdmin admin(
        "admin", "admin",
        NotificationManagerType::Basic, LockerFinderStrategy::Distance,
        LockerAvailabilityManagerStrategy::IntervalBased, LockerCodeManagerStrategy::Random
    );
    admin.addLockerStation(1, Location(0, 0), "Locker Station 1", {
        LockerConfig(1, LockerSize::Small),
        LockerConfig(2, LockerSize::Medium),
        LockerConfig(3, LockerSize::Large),
        LockerConfig(4, LockerSize::Small),
        LockerConfig(5, LockerSize::Medium),
        LockerConfig(6, LockerSize::Large)
        LockerConfig(7, LockerSize::Small),
        LockerConfig(8, LockerSize::Medium),
        LockerConfig(9, LockerSize::Large)
    });
    admin.addLockerStation(2, Location(3, 3), "Locker Station 2", {
        LockerConfig(1, LockerSize::Small),
        LockerConfig(2, LockerSize::Medium),
        LockerConfig(3, LockerSize::Small),
        LockerConfig(4, LockerSize::Medium)
    });
    return admin;
}

int main() {
    LockerSystemAdmin admin = createAdmin();
    admin.initializeSystem();

    CustomerLockerExperience customer1(42, "Alice", "alice@abc.com", Location(1, 1)), customer2(43, "Bob", "bob@abc.com", Location(2, 2));
    DeliveryAgent agent1("John", "agent1");

    auto stations1 = customer1.findNearbyLockerStations(100);
    auto stations2 = customer2.findNearbyLockerStations(100);

    Package package1(101, 42, 1, PackageStatus::Pending, PackageSize::Small, DateTime::clock::now() + std::chrono::days(2));
    Package package2(102, 43, 2, PackageStatus::Pending, PackageSize::Medium, DateTime::clock::now() + std::chrono::days(2));
    Package package3(103, 42, 3, PackageStatus::Pending, PackageSize::Large, DateTime::clock::now() + std::chrono::days(2));
    Package package4(104, 43, 4, PackageStatus::Pending, PackageSize::Small, DateTime::clock::now() + std::chrono::days(2));

    auto status1 = customer1.storePackage(package1, stations1[0].id);
    if (!status1.success) {
        std::cerr << "Failed to store package 1: " << status1.message << std::endl;
    }
    auto status2 = customer2.storePackage(package2, stations2[0].id);
    if (!status2.success) {
        std::cerr << "Failed to store package 2: " << status2.message << std::endl;
    }
    auto status3 = customer1.storePackage(package3, stations1[1].id);
    if (!status3.success) {
        std::cerr << "Failed to store package 3: " << status3.message << std::endl;
    }
    auto status4 = customer2.storePackage(package4, stations2[1].id);
    if (!status4.success) {
        std::cerr << "Failed to store package 4: " << status4.message << std::endl;
    }

    agent1.deliverPackage(package1);
    agent1.deliverPackage(package2);

    auto collected1 = customer1.collectPackage(package1.id);
    if (!collected1.success) {
        std::cerr << "Failed to collect package 1: " << collected1.message << std::endl;
    } else {
        std::cout << "Collected package 1" << std::endl;
    }

    auto collected2 = customer2.collectPackage(package2.id);
    if (!collected2.success) {
        std::cerr << "Failed to collect package 2: " << collected2.message << std::endl;
    } else {
        std::cout << "Collected package 2" << std::endl;
    }

    auto collected3 = customer1.collectPackage(package3.id);
    if (!collected3.success) {
        std::cerr << "Failed to collect package 3: " << collected3.message << std::endl;
    } else {
        std::cout << "Collected package 3" << std::endl;
    }

    auto collected4 = customer2.collectPackage(package4.id);
    if (!collected4.success) {
        std::cerr << "Failed to collect package 4: " << collected4.message << std::endl;
    } else {
        std::cout << "Collected package 4" << std::endl;
    }

    return 0;
}
