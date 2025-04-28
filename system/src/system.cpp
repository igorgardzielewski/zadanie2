//
// Created by Igor Gardzielewski on 27/04/2025.
//

#include "../includes/system.h"
#include "../includes/MPKImpl.h"
#include "../includes/DepoImpl.h"
#include "../includes/LineImpl.h"
#include "../includes/StopImpl.h"
#include "../../shared/SIP.h"
#include <Ice/Ice.h>
#include <iostream>

int main(int argc,char * argv[]) {
    int status=0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        //def interface on 10000
        Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SystemAdapter", "default -p 10000");
        SIP::MPKPtr mpk = new MPKImpl();
        SIP::DepoPtr depo = new DepoImpl("depo1");
        SIP::LinePtr line1 = new LineImpl("Line1");
        SIP::TramStopPtr stopA = new StopImpl("StopA");
        adapter->add(mpk, ic->stringToIdentity("MPK"));
        adapter->add(depo, ic->stringToIdentity("Depo"));
        adapter->add(line1, ic->stringToIdentity("Line1"));
        adapter->add(stopA, ic->stringToIdentity("StopA"));
        adapter->activate();
        std::cout << "System server started on port 10000..." << std::endl;
        ic->waitForShutdown();

    }catch (const Ice::Exception& e) {
        std::cerr << e << std::endl;
        status = 1;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        status = 1;
    }
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            std::cerr << e << std::endl;
            status = 1;
        }
    }
    return status;
}