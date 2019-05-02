//============================================================================
// Name        : lightWeightLogger.cpp
// Author      : Mina_albert
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "easylogging++.h"
#define ELPP_THREAD_SAFE
INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(
                     el::ConfigurationType::Filename,"easylogging.log");
    defaultConf.setGlobally(
                    el::ConfigurationType::ToFile,"true");
    defaultConf.setGlobally(
                    el::ConfigurationType::ToStandardOutput,"false");
    el::Loggers::reconfigureLogger("default", defaultConf);


   LOG(INFO) << "My first info log using default logger";
   return 0;
}
