/*
 * PatternGenerator.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "PatternGenerator.h"
namespace PatternGeneratorNS
{
PatternGenerator::PatternGenerator(unsigned long long &patternSize,unsigned short &noThreads):patternSize(patternSize),noThreads(noThreads)
{
//	initializeLogger();
}
PatternGenerator::~PatternGenerator()
{
}
//this logger lib keep failing
//void PatternGenerator::initializeLogger()
//{
//	    el::Configurations defaultConf;
//	    defaultConf.setToDefault();
//	    defaultConf.setGlobally(
//	                     el::ConfigurationType::Filename,"PatternGenerationLog.log");
//	    defaultConf.setGlobally(
//	                    el::ConfigurationType::ToFile,"true");
//	    defaultConf.setGlobally(
//	                    el::ConfigurationType::ToStandardOutput,"false");
//	    el::Loggers::reconfigureLogger("default", defaultConf);
//	//
//}

}
