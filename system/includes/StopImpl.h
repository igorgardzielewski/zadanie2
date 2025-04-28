//
// Created by Igor Gardzielewski on 27/04/2025.
//

#ifndef STOPIMPL_H
#define STOPIMPL_H
#include <Ice/Ice.h>
#include <mutex>

#include "Ice/Current.h"
#include <string>
#include "../../shared/SIP.h"
class StopImpl : virtual public SIP::TramStop {
private:
    std::string name;
    std::vector<SIP::PassengerPrx> passengers;
    SIP::TramList upcomingTrams;
    std::mutex mutex;
public:
    StopImpl(const std::string &name);
    virtual ~StopImpl();
    virtual std::string getName(const Ice::Current& current) override;
    virtual SIP::TramList getNextTrams(int howMany, const Ice::Current &current) override;
    virtual void RegisterPassenger(const SIP::PassengerPrx& p, const Ice::Current &current) override;
    virtual void UnregisterPassenger(const SIP::PassengerPrx& p, const Ice::Current &current) override;
    virtual void UpdateTramInfo(const SIP::TramPrx& tram, const SIP::Time &time, const Ice::Current &current) override;
};
#endif //STOPIMPL_H
