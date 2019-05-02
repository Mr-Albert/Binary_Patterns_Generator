/*
 * GeneratorFactory.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: Mina
 */

#include "GeneratorFactory.h"
namespace PatternGeneratorNS {

PatternGenerator * GeneratorFactory::  make_generator(GeneratorFactory::generator_type GeneratorType,const unsigned long long &patternSize,const long long unsigned int noThreads,std::string director_path)
{
	switch (GeneratorType)
	{
	//	LOG(INFO) <<"Instantiating logger ="<<GeneratorType;
	case GeneratorFactory::random_pattern_generator:
		return new Random_patterns_generator(patternSize,noThreads,director_path);
	break;
	case GeneratorFactory::all_patterns_generator:
	//	return new All_patterns_generator(patternSize,noThreads);
	break;

	}
	return nullptr;
}

} /* namespace PatternGenerator */
