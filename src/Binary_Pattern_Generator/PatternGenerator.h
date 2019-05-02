/*
 * PatternGenerator.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#ifndef PATTERNGENERATOR_H_
#define PATTERNGENERATOR_H_
#include<vector>

namespace PatternGeneratorNS
{
class PatternGenerator {
public:
	PatternGenerator(unsigned long long &patternSize,unsigned short &noThreads);
	unsigned long long patternSize;
	unsigned short noThreads;
	inline bool singularity_checker(bool binaryInput,std::vector <bool> &toBecheckedRow);
	virtual bool generatePattern(void)=0;
	virtual ~PatternGenerator();
};
}
#endif /* PATTERNGENERATOR_H_ */
