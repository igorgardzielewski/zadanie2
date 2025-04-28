//
// Created by Igor Gardzielewski on 28/04/2025.
//

#ifndef PASSENGERIMPL_H
#define PASSENGERIMPL_H
#include <Ice/Current.h>
#include <mutex>
#include <string>
#include <vector>

#include "../../shared/SIP.h"
class PassengerImpl : virtual public SIP::Passenger {
private:
    std::mutex mutex;
public:
    PassengerImpl();
    virtual ~PassengerImpl() override;
    virtual void updateTramInfo(const SIP::TramPrx& tram, const SIP::StopList& stops, const Ice::Current& current) override;
    virtual void updateStopInfo(const SIP::StopPrx& stop, const SIP::TramList& trams, const Ice::Current& current) override;

};
#endif //PASSENGERIMPL_H
