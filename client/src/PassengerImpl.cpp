//
// Created by Igor Gardzielewski on 28/04/2025.
//
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include "../includes/PassengerImpl.h"
#include <vector>
#include "../../shared/SIP.h"
#include <iomanip>
PassengerImpl::PassengerImpl() {
    std::cout << "created passenger" << std::endl;
}
PassengerImpl::~PassengerImpl() {
    std::cout << "destroyed passenger" << std::endl;
}
void PassengerImpl::updateTramInfo(const SIP::TramPrx& tram, const SIP::StopList& stops, const Ice::Current& current) {
    if (!tram) {
        std::cout << "trying to update null tram" << std::endl;
        return;
    }
    std::lock_guard lock(mutex);
    std::cout << "passenger update for tram" << tram->getStockNumber() << std::endl;
    std::cout << "next [" << stops.size()<<"] : "<<std::endl;
    for (const auto& stopInfo:stops) {
        if (stopInfo.stop) {
            try {
                std::cout << "    - Stop: " << stopInfo.stop->getName() << " at " << stopInfo.time.hour << ":" << stopInfo.time.minute << std::endl;
            }catch (const Ice::Exception& e) {
                std::cerr << "    - Error getting stop name: " << e.what() << std::endl;
                std::cout << "    - Stop: [Error getting name]" << " at " << stopInfo.time.hour << ":" << stopInfo.time.minute << std::endl;
            }
        }
        else {
            std::cout << "    - Stop: [Invalid Stop Proxy]"
                      << " at " << stopInfo.time.hour << ":" << stopInfo.time.minute << std::endl;
        }

    }
}
void PassengerImpl::updateStopInfo(const SIP::StopPrx& stop, const SIP::TramList& trams, const Ice::Current& current) {
    if (!stop) {
        std::cout << "trying to update null stop" << std::endl;
        return;
    }
    std::lock_guard lock(mutex);
    std::cout << "  Next " << trams.size() << " trams:" << std::endl;
    for (const auto& tramInfo:trams) {
        if (tramInfo.tram) {
            try {
                std::cout << "    - Tram: " << tramInfo.tram->getStockNumber()
                              << " at " << tramInfo.time.hour << ":"
                              << std::setfill('0') << std::setw(2) << tramInfo.time.minute << std::endl;
            }catch (const Ice::Exception& e) {
                std::cerr << "    - Error getting tram name: " << e.what() << std::endl;
                std::cout << "    - Tram: [Error getting name]" << " at " << tramInfo.time.hour << ":" << tramInfo.time.minute << std::endl;
            }
        }
        else {
            std::cout << "    - Tram: [Invalid Tram Proxy]"
                      << " at " << tramInfo.time.hour << ":" << tramInfo.time.minute << std::endl;
        }
    }
}
