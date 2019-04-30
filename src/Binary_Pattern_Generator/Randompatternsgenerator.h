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
#include <time.h>       /* time_t, time, ctime */
#include <iostream>
#include <experimental/filesystem>
#include <thread>

namespace PatternGeneratorNS
{
class Random_patterns_generator : public  PatternGenerator {
private:
	//threads array
	std::vector<std::thread> randomPatternsThreadArray;
	//currentRow vector is the currently row being generated
	//previousRow is the last completed row that was generated,needed for validation
	std::vector<bool> previousRow,currentRow;
	//resultant file
    std::ofstream outputFile;
    //path
    std::string fileName="randomFiles/randomPatternsFile_";
    //pattern generator worker
	bool generatePatternWorker();
	//generate random binary
	inline bool generate_random_pattern();
	//generate random row of binaries
	inline void generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd);

public:
	unsigned int partPerThread;
	Random_patterns_generator(unsigned long long patternSize=1,unsigned short noThreads=1);
	//checks for singularity
	inline bool singularity_checker(bool binaryInput,unsigned long long &currentRowPosition);
	//entry point for pattern generation
	bool generatePattern();
	//saves rows into the resultant file
	bool savePattern();
	inline unsigned long long max(unsigned long long frst,unsigned long long& secnd);


	virtual ~Random_patterns_generator();
};
}
#endif /* RANDOMPATTERNSGENERATOR_H_ */
