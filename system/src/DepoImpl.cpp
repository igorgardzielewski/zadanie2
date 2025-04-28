//
// Created by Igor Gardzielewski on 27/04/2025.

#include "../includes/DepoImpl.h"
#include <algorithm>
#include <vector>
#include <mutex>
#include <iostream>
#include <Ice/Ice.h>
#include "../../shared/SIP.h"

DepoImpl::DepoImpl(const std::string &name) : name(name) {
    std::cout << "created depo" << name << std::endl;
};
DepoImpl::~DepoImpl() {
    std::cout << "destroyed depo"<< name << std::endl;
}
void DepoImpl::TramOnline(const SIP::TramPrx &t, const Ice::Current &current) {
    std::lock_guard lock(mutex);
    std::cout << "making train online" << std::endl;
    if (t) {
        if (std::ranges::find(trams, t) == trams.end()) {
            std::cout << "adding train" << std::endl;
            trams.push_back(t);
        }
        else {
            std::cout << "train already online" << std::endl;
        }
    }
}
void DepoImpl::TramOffline(const SIP::TramPrx &t, const Ice::Current &current) {
    std::lock_guard lock(mutex);
    std::cout << "making train offline" << std::endl;
    if (t) {
        if (std::erase(trams, t) > 0) {
            std::cout << "removing train" << std::endl;
        } else {
            std::cout << "train already offline or not found" << std::endl;
        }
    }
}