//
// Created by Igor Gardzielewski on 27/04/2025.
//

#ifndef DEPOIMPL_H
#define DEPOIMPL_H
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include <algorithm>
#include "../../shared/SIP.h"

class DepoImpl : virtual public SIP::Depo {
private:
    std::string name;
    std::vector<SIP::TramPrx> trams;
    std::mutex mutex;
public:
    explicit DepoImpl(const std::string& name);
    virtual ~DepoImpl() override;
    virtual void TramOnline(const SIP::TramPrx &t, const Ice::Current &current) override;
    virtual void TramOffline(const SIP::TramPrx &t, const Ice::Current &current) override;
    virtual std::string getName(const Ice::Current& current) override;
};
#endif //DEPOIMPL_H
