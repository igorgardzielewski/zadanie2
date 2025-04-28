//
// Created by Igor Gardzielewski on 27/04/2025.
//
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include "../includes/MPKImpl.h"
#include <vector>
#include "../../shared/SIP.h"
#include <iostream>

MPKImpl::MPKImpl() {
    std::cout << "created MPK" << std::endl;
}

MPKImpl::~MPKImpl() {
    std::cout << "destroyed MPK" << std::endl;
}

SIP::TramStopPrx MPKImpl::getTramStop(const std::string &name, const Ice::Current& current) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::find_if(stops.begin(), stops.end(), [&](const SIP::StopInfo& stopInfo) {
        return stopInfo.stop && stopInfo.stop->ice_getIdentity().name == name;
    });
    if (it != stops.end()) {
        return it->stop;
    }
    std::cout << "tram stop not found: " << name << std::endl;
    return nullptr;
}

void MPKImpl::registerDepo(const SIP::DepoPrx& depo, const Ice::Current& current) {
    if (!depo) {
        std::cerr << "register depo with null proxy." << std::endl;
        return;
    }
    std::string depoName = depo->ice_getIdentity().name;
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::ranges::find_if(depos, [&](const SIP::DepoInfo& existingDepo) {
        return existingDepo.name == depoName;
    });
    if (it != depos.end()) {
        std::cout << "depo already registered: " << depo->ice_toString() << std::endl;
    } else {
        std::cout << "registering depo: " << depo->ice_toString() << std::endl;
        SIP::DepoInfo newDepoInfo;
        newDepoInfo.name = depoName;
        newDepoInfo.stop = depo;
        depos.push_back(newDepoInfo);
    }
}

void MPKImpl::unregisterDepo(const SIP::DepoPrx& depo, const Ice::Current& current) {
    if (!depo) {
        std::cerr << "unregister depo with null proxy." << std::endl;
        return;
    }
    std::string depoName = depo->ice_getIdentity().name;
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::ranges::find_if(depos, [&](const SIP::DepoInfo& existingDepoInfo) {
        return existingDepoInfo.name == depoName;
    });

    if (it != depos.end()) {
        std::cout << "unregistering depo: " << depoName << std::endl;
        depos.erase(it);
    }
    else {
        std::cout << "depo not registered: " << depoName << std::endl;
    }
}

SIP::DepoPrx MPKImpl::getDepo(const std::string &name, const Ice::Current& current) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::ranges::find_if(depos, [&](const SIP::DepoInfo& existingDepoInfo) {
        return existingDepoInfo.name == name;
    });

    if (it != depos.end()) {
        std::cout << "MPK: Found depo '" << name << "'" << std::endl;
        return it->stop;
    }
    std::cout << "MPK: Depo '" << name << "' not found." << std::endl;
    return nullptr;
}

SIP::DepoList MPKImpl::getDepos(const Ice::Current& current) {
    std::lock_guard<std::mutex> lock(mutex);
    return depos;
}

SIP::LineList MPKImpl::getLines(const Ice::Current& current) {
    std::lock_guard<std::mutex> lock(mutex);
    return lines;
}

void MPKImpl::registerLineFactory(const SIP::LineFactoryPrx &lf, const Ice::Current &current) {
    if (!lf) {
        std::cerr << "register line factory with null proxy." << std::endl;
        return;
    }
    
    std::lock_guard lock(mutex);
    auto it = std::find_if(lineFactories.begin(), lineFactories.end(), [&](const SIP::LineFactoryPrx& factory) {
        return factory && factory->ice_getIdentity() == lf->ice_getIdentity();
    });
    
    if (it != lineFactories.end()) {
        std::cout << "line factory already registered: " << lf->ice_toString() << std::endl;
    } else {
        std::cout << "registering line factory: " << lf->ice_toString() << std::endl;
        lineFactories.push_back(lf);
    }
}

void MPKImpl::unregisterLineFactory(const SIP::LineFactoryPrx &lf, const Ice::Current &current) {
    if (!lf) {
        std::cerr << "unregister line factory with null proxy." << std::endl;
        return;
    }
    
    std::lock_guard lock(mutex);
    auto it = std::find_if(lineFactories.begin(), lineFactories.end(), [&](const SIP::LineFactoryPrx& factory) {
        return factory && factory->ice_getIdentity() == lf->ice_getIdentity();
    });
    
    if (it != lineFactories.end()) {
        std::cout << "unregistering line factory: " << lf->ice_toString() << std::endl;
        lineFactories.erase(it);
    } else {
        std::cout << "line factory not registered: " << lf->ice_toString() << std::endl;
    }
}

void MPKImpl::registerStopFactory(const SIP::StopFactoryPrx &sf, const Ice::Current &current) {
    if (!sf) {
        std::cerr << "register stop factory with null proxy." << std::endl;
        return;
    }
    
    std::lock_guard lock(mutex);
    auto it = std::ranges::find_if(stopFactories, [&](const SIP::StopFactoryPrx& factory) {
        return factory && factory->ice_getIdentity() == sf->ice_getIdentity();
    });
    
    if (it != stopFactories.end()) {
        std::cout << "stop factory already registered: " << sf->ice_toString() << std::endl;
    } else {
        std::cout << "registering stop factory: " << sf->ice_toString() << std::endl;
        stopFactories.push_back(sf);
    }
}

void MPKImpl::unregisterStopFactory(const SIP::StopFactoryPrx &sf, const Ice::Current &current) {
    if (!sf) {
        std::cerr << "unregister stop factory with null proxy." << std::endl;
        return;
    }
    
    std::lock_guard lock(mutex);
    auto it = std::ranges::find_if(stopFactories, [&](const SIP::StopFactoryPrx& factory) {
        return factory && factory->ice_getIdentity() == sf->ice_getIdentity();
    });
    
    if (it != stopFactories.end()) {
        std::cout << "unregistering stop factory: " << sf->ice_toString() << std::endl;
        stopFactories.erase(it);
    } else {
        std::cout << "stop factory not registered: " << sf->ice_toString() << std::endl;
    }
}