//
// Created by Igor Gardzielewski on 27/04/2025.
//
#ifndef MPKIMPL_H
#define MPKIMPL_H

#include <Ice/Ice.h>
#include <stdio.h>
#include <Ice/Current.h> // <<< Dodaj tę linię
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include "../../shared/SIP.h"

class MPKImpl : public SIP::MPK {
public:
    MPKImpl();
    virtual ~MPKImpl() override;
    virtual SIP::TramStopPrx getTramStop(const std::string &name, const Ice::Current& current) override;
    virtual void registerDepo(const SIP::DepoPrx& depo,const Ice::Current& current) override;
    virtual void unregisterDepo(const SIP::DepoPrx& depo,const Ice::Current& current) override;
    virtual SIP::DepoPrx getDepo(const std::string &name, const Ice::Current& current) override;
    virtual SIP::DepoList getDepos(const Ice::Current &current) override;
    virtual SIP::LineList getLines(const Ice::Current &current) override;
    virtual void registerLineFactory(const SIP::LineFactoryPrx &lf, const Ice::Current &current) override;
    virtual void unregisterLineFactory(const SIP::LineFactoryPrx &lf, const Ice::Current &current) override;
    virtual void registerStopFactory(const SIP::StopFactoryPrx &sf, const Ice::Current &current) override;
    virtual void unregisterStopFactory(const SIP::StopFactoryPrx &sf, const Ice::Current &current) override;
private:
    //nazwij typy
    SIP::DepoList depos;
    SIP::LineList lines;
    SIP::StopList stops;
    std::vector<SIP::LineFactoryPrx> lineFactories;
    std::vector<SIP::StopFactoryPrx> stopFactories;
    std::mutex mutex;

};



#endif //MPKIMPL_H
