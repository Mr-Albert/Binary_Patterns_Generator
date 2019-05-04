/*
 * GeneratorFactory.h
 *
 *  Created on: Apr 27, 2019
 *      Author: Mina
 */

#ifndef GENERATORFACTORY_H_
#define GENERATORFACTORY_H_
#include "Randompatternsgenerator.h"
//#include "FastRandompatternsgenerator.h"
#include "allpatternsgenerator.h"
namespace PatternGeneratorNS {
class GeneratorFactory {
private:
	GeneratorFactory();
	~GeneratorFactory();
public:
	enum generator_type{random_pattern_generator=1,all_patterns_generator=2,fast_random_patterns_generator=3};
	static PatternGenerator * make_generator(generator_type GeneratorType,const unsigned long long &patternSize,const long long unsigned int noThreads=1,std::string director_path="..");
	//factories destroy what factories created
	static bool destory_generator(PatternGenerator *Generator);
};

} /* namespace PatternGenerator */

#endif /* GENERATORFACTORY_H_ */
