/*
 * PatternGenerator.h
 *
 *  Created on: Apr 22, 2019
 *      Author: Mina
 */

#ifndef PATTERNGENERATOR_H_
#define PATTERNGENERATOR_H_
//#include "Allpatternsgenerator.h"
#include<vector>
//#ifndef ELPP_THREAD_SAFE
//#include "../easyLogger/easylogging++.h"
//#define ELPP_THREAD_SAFE
//INITIALIZE_EASYLOGGINGPP
//#endif
//#ifndef ELPP_THREAD_SAFE
//#include "../easyLogger/easylogging++.h"
//#define ELPP_THREAD_SAFE
//INITIALIZE_EASYLOGGINGPP
//#endif
namespace PatternGeneratorNS
{
class PatternGenerator {
public:
	PatternGenerator(unsigned long long &patternSize,unsigned short &noThreads);
	unsigned long long patternSize;
	unsigned short noThreads;
protected:

//	virtual bool savePattern();

public:
	inline bool singularity_checker(bool binaryInput,std::vector <bool> &toBecheckedRow);
//	inline void initializeLogger();

//	static PatternGenerator * make_generator(generator_type GeneratorType);
	virtual bool generatePattern(void)=0;
	virtual ~PatternGenerator();
};
}
#endif /* PATTERNGENERATOR_H_ */
