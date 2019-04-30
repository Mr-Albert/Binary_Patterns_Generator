/*
 * Randompatternsgenerator.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Mina
 */

#include "Randompatternsgenerator.h"

namespace PatternGeneratorNS
{
Random_patterns_generator::Random_patterns_generator(unsigned long long patternSize,unsigned short noThreads):PatternGenerator(patternSize,noThreads) {
	#ifdef _DebugMode
		std::cout<<"patternSize ="<<patternSize<<std::endl;
	#endif

	//open resources(file(s))
	// generating a psuedo unique file name               //#CR check if the file already exists
	std::experimental::filesystem::create_directories("randomFiles");
	fileName+=std::to_string((static_cast<long int> (time(NULL))))+".txt";
	outputFile.open(fileName);
	//seeding random number generator
	srand(static_cast<unsigned int>(clock()));
	#ifdef _DebugMode
	std::cout<<"fileName: "<<fileName<<std::endl;
	#endif
	//initializing rows
	previousRow.resize(patternSize,0);
    currentRow.resize(patternSize,0);
    //generate the first row
    //maybe use threads?
    randomPatternsThreadArray.resize(noThreads);
    partPerThread=patternSize/noThreads;
    for(unsigned short threadIdx=0;threadIdx<noThreads-1;threadIdx++)
    {
    	randomPatternsThreadArray[threadIdx]=std::thread(generate_random_row,previousRow,threadIdx*(partPerThread),(threadIdx+1)*(partPerThread));
    }
	randomPatternsThreadArray[noThreads-1]=std::thread(generate_random_row,previousRow,(noThreads-1)*(partPerThread),Random_patterns_generator::max((noThreads)*(partPerThread),patternSize));
    for(unsigned short threadIdx=0;threadIdx<noThreads-1;threadIdx++)
	{
		randomPatternsThreadArray[threadIdx].join();
	}
//    generate_random_row(previousRow,0,patternSize);
}
//
//Random_patterns_generator::~Random_patterns_generator() {
//	// TODO Auto-generated destructor stub
//}
inline bool Random_patterns_generator::singularity_checker(bool binaryInput,unsigned long long &currentRowPosition)
{
	//first element in row ,need to check the upper right corner only
	if(currentRowPosition==0)
		return binaryInput&(binaryInput ^(previousRow[currentRowPosition+1]));
	//last element in the row ;need to check upper left corner only
	if(currentRowPosition==previousRow.size()-1)
		return binaryInput&(binaryInput ^(previousRow[currentRowPosition+1]));
	//check two corners
	return binaryInput&(binaryInput ^(previousRow[currentRowPosition-1]|previousRow[currentRowPosition+1]));
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
	 for(unsigned long long rowIdx=1;rowIdx<patternSize;rowIdx++)
	 {
	  generate_random_row(currentRow,0,patternSize);
	  //save previos row into stream
	  savePattern();
	  // make current row the previous row O(1)
	for(unsigned long long int i=1;i<patternSize-1;i++)
	{
		if(currentRow[i]==1&&(previousRow[i-1]==1||previousRow[i+1]==1))
		{
			std::cout<<"error at rowidx = "<<rowIdx<<"and i ="<<i<<"\n";
			for(unsigned long long int ii=0;ii<patternSize;ii++)
				std::cout<<previousRow[ii]<<",";
			std::cout<<std::endl<<"current row\n";
			for(unsigned long long int ii=0;ii<patternSize;ii++)
				std::cout<<currentRow[ii]<<",";
			std::cout<<std::endl<<" finsisshed current row\n";
			std::cout<<"singu checker result"<<singularity_checker(currentRow[i],i)<<std::endl;

		}
	}
	  previousRow.swap(currentRow);
	 }
	return 1;


}
inline bool Random_patterns_generator::generate_random_pattern()
{
	//return a random 'binary' value
	return rand()%2;
}
bool Random_patterns_generator::savePattern()
{
	#ifdef _DebugMode
	std::cout<<"entering the save"<<std::endl;
	#endif
	unsigned long long fileInpurRowIdx=0;
	for(;fileInpurRowIdx<previousRow.size()-1;fileInpurRowIdx++)
	{
		outputFile<<previousRow[fileInpurRowIdx]<<",";
		#ifdef _DebugMode
		std::cout<<previousRow[fileInpurRowIdx]<<",";
        #endif
	}
	//output last element with a new line without a flush
	#ifdef _DebugMode
	std::cout<<previousRow[fileInpurRowIdx]<<"\n";
	#endif
	outputFile<<previousRow[fileInpurRowIdx]<<"\n";
	return 1;
}

inline unsigned long long Random_patterns_generator::max(unsigned long long frst,unsigned long long& secnd)
{
	return (frst>secnd)?frst:secnd;
	}
Random_patterns_generator::~Random_patterns_generator() {

	  //close open resources
	#ifdef _DebugMode
	  std::cout<<"closing resources"<<std::endl;
	#endif
	  outputFile.flush();
	  outputFile.close();

}

}
