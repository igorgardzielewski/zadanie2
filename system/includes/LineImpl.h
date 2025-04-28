//
// Created by Igor Gardzielewski on 27/04/2025.
//

#ifndef LINEIMPL_H
#define LINEIMPL_H
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include <vector>

#include "../../shared/SIP.h"

class LineImpl : virtual public SIP::Line {
private:
    std::string name;
    SIP::TramList trams;
    SIP::StopList stops;
    std::mutex mutex;
public:
    explicit LineImpl(const std::string &name);
    virtual ~LineImpl() override;
    virtual SIP::TramList getTrams(const Ice::Current &current) override;
    virtual SIP::StopList getStops(const Ice::Current &current) override;
    virtual void registerTram(const SIP::TramPrx &tram, const Ice::Current &current) override;
    virtual void unregisterTram(const SIP::TramPrx &tram, const Ice::Current &current) override;
    virtual void setStops(const SIP::StopList &sl, const Ice::Current &current) override;
    virtual std::string getName(const Ice::Current& current) override;
};
#endif //LINEIMPL_H
