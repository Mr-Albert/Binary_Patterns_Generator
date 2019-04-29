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
namespace PatternGeneratorNS
{
class PatternGenerator {
public:
	PatternGenerator(unsigned long long &patternSize);
	unsigned long long patternSize;
protected:

//	virtual bool savePattern();

public:
	inline bool singularity_checker(bool binaryInput,std::vector <bool> &toBecheckedRow);

//	static PatternGenerator * make_generator(generator_type GeneratorType);
	virtual bool generatePattern(void)=0;
	virtual ~PatternGenerator();
};
}
#endif /* PATTERNGENERATOR_H_ */
