//
// Created by Igor Gardzielewski on 28/04/2025.
//
#include "../includes/TramImpl.h"
#include <algorithm>
#include <vector>
#include <mutex>
#include <iostream>
#include <Ice/Ice.h>
#include "../../shared/SIP.h"
TramImpl::TramImpl(const std::string &number) : number(number) {
    std::cout << "created tram" << number << std::endl;

};
TramImpl::~TramImpl() {
    std::cout << "destroyed tram" << number << std::endl;
}
SIP::TramStopPrx TramImpl::getLocation(const Ice::Current &current) {
    std::cout << "getting location" << std::endl;
    std::lock_guard lock(mutex);
    return currentStop;
}
SIP::LinePrx TramImpl::getLine(const Ice::Current &current) {
    std::cout << "getting line" << std::endl;
    std::lock_guard lock(mutex);
    return currentLine;
}
void TramImpl::setLine(const SIP::LinePrx &line, const Ice::Current &current) {
    if (!line) return;
    std::cout << "setting line" << std::endl;
    std::lock_guard lock(mutex);
    if (currentLine) {
        try{
            currentLine->unregisterTram(Ice::uncheckedCast<SIP::TramPrx>(current.adapter->createProxy(current.id)));
        }catch (const Ice::Exception &e) {
            std::cout << "error unregistering tram" << e.what() << std::endl;
        }
    }
    currentLine = line;
    if (currentLine) {
        try{
            currentLine->registerTram(Ice::uncheckedCast<SIP::TramPrx>(current.adapter->createProxy(current.id)));
        }catch (const Ice::Exception &e) {
            std::cout << "error registering tram" << e.what() << std::endl;
        }
    }
}
SIP::StopList TramImpl::getNextStops(Ice::Int howMany, const Ice::Current &current) {
    std::cout << "getting next stops" << std::endl;
    std::lock_guard lock(mutex);
    SIP::StopList result;
    if (nextStops.empty() || howMany <=0) {
        return result;
    }
    int count = std::min(static_cast<size_t>(howMany), nextStops.size());
    result.reserve(count);
    for (int i = 0; i < count; i++) {
        result.push_back(nextStops[i]);
    }
    return result;
}
void TramImpl::RegisterPassenger(const SIP::PassengerPrx &p, const Ice::Current &current) {
    if (!p) {
        std::cerr << "register passenger with null proxy." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mutex);
    auto [_, inserted] = passengers.insert(p);
    if (inserted) {
        std::cout << "passenger registered in tram " << number << std::endl;
    } else {
        std::cout << "passenger already registered" << std::endl;
    }
}
void TramImpl::UnregisterPassenger(const SIP::PassengerPrx &p, const Ice::Current &current) {
    if (!p) {
        std::cerr << "unregister passenger with null proxy." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mutex);
    auto it = passengers.find(p);
    if (it != passengers.end()) {
        passengers.erase(it);
        std::cout << "passenger unregistered from tram " << number << std::endl;
    } else {
        std::cout << "passenger not registered" << std::endl;
    }
}
std::string TramImpl::getStockNumber(const Ice::Current &current) {
    std::lock_guard lock(mutex);
    return number;
}
