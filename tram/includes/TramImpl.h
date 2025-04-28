//
// Created by Igor Gardzielewski on 28/04/2025.
//

#ifndef TRAMIMPL_H
#define TRAMIMPL_H
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include <vector>

#include "../../shared/SIP.h"
class TramImpl : virtual public SIP::Tram {
private:
    std::string number;
    SIP::TramStopPrx currentStop;
    SIP::LinePrx currentLine;
    std::mutex mutex;
    SIP::StopList nextStops;
    std::set<SIP::PassengerPrx> passengers;
public:
    TramImpl(const std::string &number);
    virtual ~TramImpl() override;
    virtual SIP::TramStopPrx getLocation(const Ice::Current &current) override;
    virtual SIP::LinePrx getLine(const Ice::Current &current) override;
    virtual void setLine(const SIP::LinePrx &line, const Ice::Current &current) override;
    virtual SIP::StopList getNextStops(Ice::Int howMany, const Ice::Current &current) override;
    virtual void RegisterPassenger(const SIP::PassengerPrx &p, const Ice::Current &current) override;
    virtual void UnregisterPassenger(const SIP::PassengerPrx &p, const Ice::Current &current) override;
    virtual std::string getStockNumber(const Ice::Current &current) override;

};
#endif //TRAMIMPL_H
