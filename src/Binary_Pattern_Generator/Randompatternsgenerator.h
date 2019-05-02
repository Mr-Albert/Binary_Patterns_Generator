/*
 * Randompatternsgenerator.h
 *
 *  Created on: Apr 22, 2019
 *      Author: Mina
 */

#ifndef RANDOMPATTERNSGENERATOR_H_
#define RANDOMPATTERNSGENERATOR_H_
#include "PatternGenerator.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include<iostream>
#include <fstream>
#include<string>
#include <time.h>
#include <iostream>
#include <experimental/filesystem>
#include <thread>
#include <stdexcept>

namespace PatternGeneratorNS
{
class Random_patterns_generator : public  PatternGenerator {
protected:
	//threads array
	std::vector<std::thread> randomPatternsThreadArray;
	//<shared memory>currentRow vector is the currently row being generated
	//<shared memory>previousRow is the last completed row that was generated,needed for validation
	//<shared memory> thread-shared random row-data
	std::vector<bool> previousRow,currentRow,randomRow;
	//resultant file and path
    std::ofstream outputFile;
    std::string fileName="randomFiles/randomPatternsFile_";
	//how many items each thread should work on
    unsigned int partPerThread;
    //pattern generator worker
	bool generatePatternWorker();
	//generate random binary inside shared mem randomRow
	inline void generate_random_pattern();
	//generate random row of binaries
	void generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd);
	inline unsigned long long max(unsigned long long frst,unsigned long long& secnd);
	//saves rows into the resultant file
	bool savePattern();
	//checks for singularitys
	inline bool singularity_checker(const bool &binaryInput,unsigned long long &currentRowPosition);

public:
	Random_patterns_generator(unsigned long long patternSize=1,unsigned short noThreads=1);
	//entry point for pattern generation
	bool generatePattern();
	virtual ~Random_patterns_generator();
};
}
#endif /* RANDOMPATTERNSGENERATOR_H_ */
