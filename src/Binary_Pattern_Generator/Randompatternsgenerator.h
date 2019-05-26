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
#include "../FileWriter/FileWriter.h"

namespace PatternGeneratorNS
{
/*
 *
 * This class generates two valid rows and writes into the file each row....#CR allow for multiple buffered rows instead of one row?
 *
 * Another approach than the one taken here is to generate all rows
 * (write them to desk if they are too large)
 * and then detect the "singularity" pattern using a 2D (or reduce to 1D) none-square..
 * ..pattern matching algorithm for binary alphabet and then remove those occurrences
 * (but i don't think it will allow for parallelism nor more read/write efficiency)...needs testing
 *
 */
class Random_patterns_generator : public  PatternGenerator {

//after removing the save responsibility from this class,the created writer class was made into a friend class(to access the prev row)
friend FileWriter;
FileWriter fWriter;
struct m_first_row_tag {} m_first_row_tag_dispatcher;
protected:
	/*
	 * <shared memory>currentRow vector is the currently row being generated
	 * <shared memory>previousRow is the last completed row that was generated,needed for validation
	 * <shared memory> thread-shared random row-data
	 * randomPatternsThreadArray : threads holder
	 * ..vector<bool> is problematic..
	 */
	std::vector<bool> previousRow,currentRow,randomRow;
	std::vector<std::thread> randomPatternsThreadArray;

	/*
	 * //this was used for writing but was tightly coupled with the class but provided faster writing speed
	 * char * previousRowChar;
	 * char *charBuffer;
	 * std::string charType="01,";
	 * char *previousRowCharBuffer;
	 */
	//how many items each thread should work on
    unsigned long long partPerThread;
    //pattern generator worker
	bool generatePatternWorker();
	//generate random binary inside shared mem randomRow
	inline void generate_random_pattern();
	//generate random row of binaries
	void generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd);
	inline unsigned long long max(unsigned long long frst,unsigned long long& secnd);
	//checks for singularities
	inline bool singularity_checker(const bool &binaryInput,unsigned long long &currentRowPosition);

public:
	Random_patterns_generator(unsigned long long patternSize=1,unsigned short noThreads=1,std::string director_path="");
	//entry point for pattern generation
	bool generatePattern();
	virtual ~Random_patterns_generator();
};
}
#endif /* RANDOMPATTERNSGENERATOR_H_ */
