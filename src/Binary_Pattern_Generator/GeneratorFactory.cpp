/*
 * GeneratorFactory.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: Mina
 */

#include "GeneratorFactory.h"

namespace PatternGeneratorNS {

PatternGenerator * GeneratorFactory::  make_generator(GeneratorFactory::generator_type GeneratorType,unsigned long long &patternSize,long long unsigned int noThreads)
{
	switch (GeneratorType)
	{
	case GeneratorFactory::random_pattern_generator:
		return new Random_patterns_generator(patternSize);
	break;
	case GeneratorFactory::all_patterns_generator:
//		return new All_patterns_generator(patternSize);
	break;

	}
	return nullptr;
}


bool GeneratorFactory::test()
{
	std::cout<<"s";
return 0;
}

} /* namespace PatternGenerator */
