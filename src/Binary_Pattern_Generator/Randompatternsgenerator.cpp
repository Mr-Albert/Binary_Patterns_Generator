/*
 * Randompatternsgenerator.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Mina
 */

#include "Randompatternsgenerator.h"
#include <time.h>       /* time_t, time, ctime */

#include <iostream>
namespace PatternGeneratorNS
{
Random_patterns_generator::Random_patterns_generator(unsigned long long patternSize):PatternGenerator(patternSize) {
	  //open resources(file(s))
	  //+std::tmpnam+
	  // generating a psuedo unique file name               //#CR check if the file already exists
	  fileName+=std::to_string((static_cast<long int> (time(NULL))))+".txt";
	  outputFile.open(fileName);
	  //seeding random number generator
	  srand(static_cast<unsigned int>(clock()));
		std::cout<<"size "<<patternSize<<std::endl;
	  previousRow.resize(patternSize,0);
		std::cout<<"size "<<previousRow.size()-1<<std::endl;

	  currentRow.resize(patternSize,0);
	  //generate the first row
	  //maybe use threads?
	  generate_random_row(previousRow,0,patternSize);
}
//
//Random_patterns_generator::~Random_patterns_generator() {
//	// TODO Auto-generated destructor stub
//}
inline bool Random_patterns_generator::singularity_checker(bool binaryInput,unsigned long long &currentRowPosition)
{
	//first element in row ,need to check the upper right corner only
	if(currentRowPosition==0)
		return binaryInput ^(previousRow[currentRowPosition+1]);
	//last element in the row ;need to check upper left corner only
	if(currentRowPosition==previousRow.size()-1)
		return binaryInput ^(previousRow[currentRowPosition+1]);
	//check two corners
	return binaryInput ^(previousRow[currentRowPosition-1]|previousRow[currentRowPosition+1]);
}

inline void Random_patterns_generator::generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd)
{
	for(;rowStart<rowEnd;rowStart++)
	{
		destinationRow[rowStart]=singularity_checker(generate_random_pattern(),rowStart);
	}
}

//called for pattern genenration;
bool Random_patterns_generator::generatePattern()
{
	//maybe use Threads?
	  // generate Current row
	  generate_random_row(currentRow,0,patternSize);
	  //save previos row into stream
	  savePattern();
	  // make current row the previous row O(1)
	  previousRow.swap(currentRow);
	return 1;

	for(unsigned long long i=0;i<patternSize;i++)
	{
		std::cout<<generate_random_pattern()<<" ";
	}
}
inline bool Random_patterns_generator::generate_random_pattern()
{
	//return a random 'binary' value
	return rand()%2;
}
bool Random_patterns_generator::savePattern()
{
	std::cout<<"entering the save"<<std::endl;
	unsigned long long fileInpurRowIdx=0;
	for(;fileInpurRowIdx<previousRow.size()-1;fileInpurRowIdx++)
	{
		outputFile<<previousRow[fileInpurRowIdx]<<",";
		std::cout<<previousRow[fileInpurRowIdx]<<",";

	}
	//output last element with a new line without a flush
	std::cout<<previousRow[fileInpurRowIdx]<<"\n";
	outputFile<<previousRow[fileInpurRowIdx]<<"\n";
	return 1;
}

Random_patterns_generator::~Random_patterns_generator() {

	  //close open resources
	  std::cout<<"closing resources"<<std::endl;
	  outputFile.flush();
	  outputFile.close();

}

}
