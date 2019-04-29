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
namespace PatternGeneratorNS
{
class Random_patterns_generator : public  PatternGenerator {
private:
	//currentRow vector is the currently row being generated
	//previousRow is the last completed row that was generated,needed for validation
	std::vector<bool> previousRow,currentRow;
    std::ofstream outputFile;
    std::string fileName="randomPatternsFile_";
	bool generatePatternWorker();
	inline bool generate_random_pattern();
	inline void generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd);

public:
	Random_patterns_generator(unsigned long long patternSize=1);
	inline bool singularity_checker(bool binaryInput,unsigned long long &currentRowPosition);
	bool generatePattern();
	bool savePattern();

	virtual ~Random_patterns_generator();
};
}
#endif /* RANDOMPATTERNSGENERATOR_H_ */
