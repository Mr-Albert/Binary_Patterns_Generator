/*
 * GeneratorFactory.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Mina
 */

#ifndef GENERATORFACTORY_H_
#define GENERATORFACTORY_H_
#include "Randompatternsgenerator.h"
#include "allpatternsgenerator.h"

namespace PatternGeneratorNS {

class GeneratorFactory {

private:
	GeneratorFactory();
	~GeneratorFactory();
public:
	enum generator_type{random_pattern_generator,all_patterns_generator};
	static PatternGenerator * make_generator(generator_type GeneratorType,unsigned long long &patternSize,long long unsigned int noThreads=3);
	static bool destory_generator(PatternGenerator *Generator);
	static bool test();


};

} /* namespace PatternGenerator */

#endif /* GENERATORFACTORY_H_ */
