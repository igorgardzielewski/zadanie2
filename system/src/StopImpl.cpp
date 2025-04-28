//
// Created by Igor Gardzielewski on 27/04/2025.
//
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include "../includes/StopImpl.h"
#include <vector>
#include "../../shared/SIP.h"
StopImpl::StopImpl(const std::string &name) : name(name) {
    std::cout << "created stop" << name << std::endl;
}
StopImpl::~StopImpl() {
    std::cout << "destroyed stop" << name << std::endl;
}
std::string StopImpl::getName(const Ice::Current& current) {
    std::lock_guard lock(mutex);
    return name;
}
SIP::TramList StopImpl::getNextTrams(int howMany, const Ice::Current &current) {
    std::lock_guard lock(mutex);
    return upcomingTrams;
}
void StopImpl::RegisterPassenger(const SIP::PassengerPrx& p, const Ice::Current &current) {
    if (!p) return;
    std::cout << "registering passenger" << std::endl;
    std::lock_guard lock(mutex);
    const auto it = std::ranges::find_if(passengers,[&](const SIP::PassengerPrx &exist_passenger) {
        return exist_passenger && exist_passenger->ice_getIdentity() == p->ice_getIdentity();
    });
    if (it == passengers.end()) {
        std::cout << "passenger not registered - registering now " << p->ice_toString() << std::endl;
        passengers.push_back(p);
    }
    else {
        std::cout << "passenger already registered" << std::endl;
    }
}
void StopImpl::UnregisterPassenger(const SIP::PassengerPrx &p, const Ice::Current &current) {
    if (!p) return;
    std::cout << "unregistering passenger" << std::endl;
    std::lock_guard lock(mutex);
    const auto it = std::ranges::find_if(passengers,[&](const SIP::PassengerPrx &exist_passenger) {
        return exist_passenger && exist_passenger->ice_getIdentity() == p->ice_getIdentity();
    });
    if (it != passengers.end()) {
        std::cout << "passenger unregistered" << std::endl;
        passengers.erase(it);
    }
}
void StopImpl::UpdateTramInfo(const SIP::TramPrx &tram, const SIP::Time &time, const Ice::Current &current) {
    if (!tram) return;
    std::cout << "updating tram info for stop " << name << std::endl;
    std::lock_guard lock(mutex);

    auto it = std::ranges::find_if(upcomingTrams,[&](const SIP::TramInfo& info) {
        return info.tram && info.tram->ice_getIdentity() == tram->ice_getIdentity();
    });

    if (it != upcomingTrams.end()) {
        std::cout << "Stop " << name << ": Updating time for existing tram to "
                  << time.hour << ":" << time.minute << std::endl;
        it->time = time;
    }
    std::ranges::sort(upcomingTrams,[](const SIP::TramInfo& a, const SIP::TramInfo& b) {
        if (a.time.hour != b.time.hour) {
            return a.time.hour < b.time.hour;
        }
        return a.time.minute < b.time.minute;
    });
}