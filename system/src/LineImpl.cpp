//
// Created by Igor Gardzielewski on 27/04/2025.
//
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include "../includes/LineImpl.h"
#include <vector>
#include "../../shared/SIP.h"
LineImpl::LineImpl(const std::string &name) : name(name) {
    std::cout << "created line" << name << std::endl;
};
LineImpl::~LineImpl() {
    std::cout << "destroyed line" << name << std::endl;
}
std::string LineImpl::getName(const Ice::Current& current) {
    std::lock_guard lock(mutex);
    return name;
}
SIP::TramList LineImpl::getTrams(const Ice::Current &current) {
    std::lock_guard lock(mutex);
    return trams;
}
SIP::StopList LineImpl::getStops(const Ice::Current &current) {
    std::lock_guard lock(mutex);
    return stops;
}
void LineImpl::registerTram(const SIP::TramPrx &tram, const Ice::Current &current) {
    if (!tram) {
        std::cout << "trying to register null Tram" << std::endl;
        return;
    }
    std::lock_guard lock(mutex);
    std::cout << "registering tram" << std::endl;
    //co to robi ponizej? nikt nie wie
    auto it = std::ranges::find_if(trams,[&](const SIP::TramInfo &info){
        return info.tram && tram && info.tram->ice_getIdentity() == tram->ice_getIdentity();
    });
    if (it == trams.end()) {
        std::cout << "tram not registered" << std::endl;
        //{} inicjalizuje wszystkie pola
        SIP::TramInfo newTramInfo{};
        newTramInfo.tram = tram;
        //aktualny? czy na trasie?
        newTramInfo.time.hour = 0;
        newTramInfo.time.minute = 0;
        trams.push_back(newTramInfo);
        std::cout << "tram registered "<< tram->ice_toString() << std::endl;
    }
    else {
        std::cout << "tram already registered" << std::endl;
    }
}
void LineImpl::unregisterTram(const SIP::TramPrx &tram, const Ice::Current &current) {
    if (!tram) {
        std::cout << "trying to unregister null Tram" << std::endl;
        return;
    }
    std::lock_guard lock(mutex);
    std::cout << "unregistering tram" << std::endl;
    auto it = std::ranges::find_if(trams,[&](const SIP::TramInfo &info){
        return info.tram && tram && info.tram->ice_getIdentity() == tram->ice_getIdentity();
    });
    if (it != trams.end()) {
        const std::string str = it->tram ? it->tram->ice_toString() : "invalid proxy";
        trams.erase(it);
        std::cout << "tram unregistered" << str << name << std::endl;
    } else {
        std::cout << "tram " << (tram ? tram->ice_toString() : "null proxy")
                  << " not found on line " << name << ", cannot unregister." << std::endl;
    }
}

void LineImpl::setStops(const SIP::StopList &sl, const Ice::Current &current) {
    std::lock_guard lock(mutex);
    stops = sl;
}

