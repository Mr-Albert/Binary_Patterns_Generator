/*
 * RandomGeneratorTester.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "RandomGeneratorTester.h"
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <ios>
//#include <limits>
//#include<cstdlib>
namespace PatternGeneratorTester {

RandomGeneratorTester::RandomGeneratorTester(unsigned short generatorType,std::string directory_path):generatorType(generatorType),directory_path(directory_path) {
	// TODO Auto-generated constructor stub
	srand(static_cast<unsigned int>(clock()));
	std::experimental::filesystem::create_directories(directory_path);
	std::experimental::filesystem::create_directories("statisics/"+directory_path);



}

bool RandomGeneratorTester::testThreadsSpeed(unsigned short threadRange,unsigned short patternRange) {
	// TODO Auto-generated constructor stub

	//e7m
	vec<vec<vector_of_unsigned_long>> statistics_matrix
		(threadRange,
		 vec<vector_of_unsigned_long> (patternRange,vector_of_unsigned_long(0)));
	for(unsigned short int testNo=1;testNo<1000;testNo++)
	{
		unsigned int gridWidth=rand()%patternRange+1;
		unsigned short noThreads=rand()%threadRange+1;

		auto start = std::chrono::high_resolution_clock::now();
		generator =
				PatternGeneratorNS::GeneratorFactory::
				make_generator(static_cast <PatternGeneratorNS::GeneratorFactory::generator_type> (generatorType)
				,gridWidth,noThreads,directory_path);
			//generating the patterns
		generator->generatePattern();
		auto end = std::chrono::high_resolution_clock::now();
		statistics_matrix[noThreads-1][gridWidth-1].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
		delete generator;
	}
	std::experimental::filesystem::remove_all(directory_path);
	return 1;
}
//RandomGeneratorTester::RNGTester(unsigned short patternRange=10000) {
//	// TODO Auto-generated constructor stub
//
//
//}
//RandomGeneratorTester::patternRandomnessTester(unsigned short patternRange=10000) {
//	// TODO Auto-generated constructor stub
//
//
//}
//RandomGeneratorTester::patternCorrectnessTester(unsigned short patternRange=10000) {
//	// TODO Auto-generated constructor stub
//
//
//}

RandomGeneratorTester::~RandomGeneratorTester() {
	// TODO Auto-generated destructor stub
	delete generator;

}

} /* namespace PatternGeneratorTester */
