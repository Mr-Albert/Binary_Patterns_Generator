/*
 * RandomGeneratorTester.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#ifndef RANDOMGENERATORTESTER_H_
#define RANDOMGENERATORTESTER_H_
#define ull unsigned long long
#define vec std::vector
#define vector_of_unsigned_long vec<ull>

#include "../Binary_pattern_generator/GeneratorFactory.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <sstream>
#include <string>
#include <ios>
#include <limits>
#include<cstdlib>
#include <fstream>

namespace PatternGeneratorTesterNS {

class RandomGeneratorTester {
	PatternGeneratorNS::PatternGenerator  *generator=nullptr ;
	unsigned short generatorType;
	std::string directory_path;

public:
	RandomGeneratorTester(unsigned short generatorType,std::string directory_path);
	bool testThreadsSpeed(unsigned short threadRange=4,unsigned short patternRange=10000);

   ~RandomGeneratorTester();
};

} /* namespace PatternGeneratorTester */

#endif /* RANDOMGENERATORTESTER_H_ */
