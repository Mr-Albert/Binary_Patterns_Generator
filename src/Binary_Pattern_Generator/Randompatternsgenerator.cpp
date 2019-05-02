/*
 * Randompatternsgenerator.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "Randompatternsgenerator.h"

namespace PatternGeneratorNS
{
Random_patterns_generator::Random_patterns_generator(unsigned long long patternSize,unsigned short noThreads,std::string director_path):PatternGenerator(patternSize,noThreads) {
	try {
		//		LOG(INFO) << "starting patterns";
		//will be removed by the compiler on builds without the _debugMode
		#ifdef _DebugMode
			std::cout<<"patternSize ="<<patternSize<<", noOfthreads ="<<noThreads;
		#endif
		//enabling fstream exceptions
		outputFile.exceptions ( std::ios_base::failbit |
						std::ios_base::badbit );
		if(director_path!="")
		{
			directory_path=director_path;
		}
		//open resources(file(s))  and generating a pseudo unique file name               //#CR check if the file already exists
		std::experimental::filesystem::create_directories(directory_path);
		fileName=directory_path+"/"+fileName;
		fileName+=std::to_string((static_cast<long int> (time(NULL))))+".txt";
		#ifdef _DebugMode
			std::cout<<" , file name "<<fileName<<std::endl;
		#endif
		outputFile.open(fileName);
		//seeding random number generator
		srand(static_cast<unsigned int>(clock()));
		//initializing rows
		previousRow.resize(patternSize,0);
		currentRow.resize(patternSize,0);
		randomRow.resize(patternSize,0);
		//resizing the thread vector to accommodate for all the threads
		randomPatternsThreadArray.resize(noThreads);
	    partPerThread=patternSize/noThreads;
	    generate_random_pattern();
	    //	   LOG(INFO)<<"Started a new random binary pattern generator with patternSize = "<<patternSize<<", noThread = "<<noThreads<<", row part per thread = "<<partPerThread<<"\n";
		//generate the first row
	    for(unsigned short threadIdx=0;threadIdx<noThreads-1;threadIdx++)
	    {
	    	randomPatternsThreadArray[threadIdx]=std::thread(generate_random_row,this,std::ref(previousRow),threadIdx*(partPerThread),(threadIdx+1)*(partPerThread));
	    }
		randomPatternsThreadArray[noThreads-1]=std::thread(generate_random_row,this,std::ref(previousRow),(noThreads-1)*(partPerThread),Random_patterns_generator::max((noThreads)*(partPerThread),patternSize));
	    //join
		for(unsigned short threadIdx=0;threadIdx<noThreads;threadIdx++)
		{
			randomPatternsThreadArray[threadIdx].join();
		}
		#ifdef _DebugMode
			std::cout<<"constructor finished ,with row parts per thread"<<partPerThread<<std::endl;
		#endif
	}
	catch (const std::exception& e)
	{
		//	LOG(ERROR)<<e.what()<<std::endl;
	}
}

inline bool Random_patterns_generator::singularity_checker(const bool & binaryInput,unsigned long long &currentRowPosition)
{
	/*
	 *
	 * re-coded..almost the same number of assembly instructions as the previous more confusing version
	 * if it is a 1 i.e cell should be filled
	 *
	 */
	if(binaryInput)
	{
		//if upper left is filled or upper right is filled
		if((currentRowPosition>0 && previousRow[currentRowPosition-1]) ||(currentRowPosition<previousRow.size()-1 && previousRow[currentRowPosition+1]) )
			return 0;
		//else we can make it filled
		else
			return 1;
	}
	return 0;

	/*
	 *
	 *  //confusing
	 *  //first element in row ,need to check the upper right corner only
	 *	if(currentRowPosition==0)
	 *		return binaryInput&(binaryInput ^(previousRow[currentRowPosition+1]));
	 *	//last element in the row ;need to check upper left corner only
	 *	if(currentRowPosition==previousRow.size()-1)
	 *	return binaryInput&(binaryInput ^(previousRow[currentRowPosition+1]));
	 *	//check two corners
	 *	return binaryInput&(binaryInput ^(previousRow[currentRowPosition-1]|previousRow[currentRowPosition+1]));
	 *
	 */
}
void Random_patterns_generator::generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd)
{
	/*
	 *
	 * destinationRow: row to write result at;
	 * rowStart=the start index for the part in the row the executing thread is responsible for
	 * rowEnd=the exclusive end index for the part in the row the executing thread is responsible for
	 * ---------
	 * generating random row splitted on the threads avaiable and checked against previous(upper ) row
	 * ---------
	 * customized for mutlithreading since there is an open shot for parallelism,
	 * the diminishing returns principle seems to be playing a role here as the number of threads
	 * are slowing it down (thread should be around core numbers?!)...need to find optimum number
	 *
	 */
	try {
		#ifdef _DebugMode
			std::cout<<"Thread ID: "<<std::this_thread::get_id()<<" with params (rowStart = "<<rowStart<<", rowEnd = "<<rowEnd<<" )\n";
		#endif
		for(;rowStart<rowEnd;rowStart++)
		{
			destinationRow[rowStart]=singularity_checker(randomRow[rowStart],rowStart);
		}
	}
	catch(const std::exception &e)
	{
		//		LOG(ERROR)<<e.what()<<" , for thread: "<<std::this_thread::get_id()<<std::endl;
	}
}

//called for pattern genenration;
bool Random_patterns_generator::generatePattern()
{
	/*
	 *
	 * The work horse that loops to generate all the required row by calling "generate_random_row()" among threads
	 *
	 */
	try {
		 // generate Current row
		 for(unsigned long long rowIdx=1;rowIdx<patternSize;rowIdx++)
		 {
			 generate_random_pattern();
			 for(unsigned short threadIdx=0;threadIdx<noThreads-1;threadIdx++)
			{
				randomPatternsThreadArray[threadIdx]=std::thread(generate_random_row,this,std::ref(currentRow),threadIdx*(partPerThread),(threadIdx+1)*(partPerThread));
			}
			randomPatternsThreadArray[noThreads-1]=std::thread(generate_random_row,this,std::ref(currentRow),(noThreads-1)*(partPerThread),Random_patterns_generator::max((noThreads)*(partPerThread),patternSize));
			//join
			for(unsigned short threadIdx=0;threadIdx<noThreads;threadIdx++)
			{
				randomPatternsThreadArray[threadIdx].join();
			}
		  savePattern();
		  // make current row the previous row O(1)
		  previousRow.swap(currentRow);
		 }
	}
	catch (const std::exception &e)
	{
		//		LOG(INFO)<<e.what()<<std::endl;
	}
	return 1;


}
//not thread safe,making it a critical section might hamper performance
//will generate rows of random data in a shared memory before entering the threads
inline void Random_patterns_generator::generate_random_pattern()
{
	/*
	 *
	 * not thread safe,making it a critical section might hamper performance
	 * will generate rows of random data in a shared memory before entering the threads
	 *
	 */
	for(unsigned long long int randomIdx=0;randomIdx<patternSize;randomIdx++)
	{
		randomRow[randomIdx]=rand()%2;
	}
}
bool Random_patterns_generator::savePattern()
{
	/*
	 *
	 * this funcntion should be made in its own class
	 * (pattern generator should only generate patterns and not responsible for saving them)
	 * and taking a stream & as parameter for better extendibility
	 * (closed for mod ,open for extend principle )
	 *
	 */
	#ifdef _DebugMode
	std::cout<<"entering the save previous row function"<<std::endl;
	#endif
	try{
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
	}
	catch (const std::exception &e)
	{
		//		LOG(INFO)<<e.what()<<std::endl;
	}
	return 1;
}

inline unsigned long long Random_patterns_generator::max(unsigned long long frst,unsigned long long& secnd)
{
	return (frst>secnd)?frst:secnd;
}
Random_patterns_generator::~Random_patterns_generator() {

	//saving the last row
	savePattern();
	  //close open resources
	#ifdef _DebugMode
	  std::cout<<"closing resources"<<std::endl;
	#endif
	  //	  LOG(INFO)<<"closing resources"<<std::endl;
	  outputFile.flush();
	  outputFile.close();

}

}
