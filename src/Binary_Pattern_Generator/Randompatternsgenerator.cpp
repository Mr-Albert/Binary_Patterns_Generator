/*
 * Randompatternsgenerator.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "Randompatternsgenerator.h"

namespace PatternGeneratorNS
{
Random_patterns_generator::Random_patterns_generator(unsigned long long patternSize,unsigned short noThreads,std::string director_path):PatternGenerator(patternSize,noThreads),fWriter(patternSize,"test",director_path)
 {
	try {
		/*
		 * //tightly coupled but faster writing,maybe reimplement it as fastRandomPatternGenerator class..no time tho
		 * previousRowChar=new char[patternSize*2];
		 * previousRowCharBuffer = new char [patternSize];
		 * //open resources(file(s))  and generating a pseudo unique file name               //#CR check if the file already exists
		 * std::experimental::filesystem::create_directories(directory_path);
		 * fileName=directory_path+"/"+fileName;
		 * fileName+=std::to_string((static_cast<long int> (time(NULL))))+".txt";
		 * #ifdef _DebugMode
		 * std::cout<<" , file name "<<fileName<<std::endl;
		 * #endif
		 * outputFile.open(fileName,std::ios::out );
		 * //LOG(INFO) << "starting patterns";
		 */
		//will be removed by the compiler on builds without the _debugMode
		#ifdef _DebugMode
			std::cout<<"patternSize ="<<patternSize<<", noOfthreads ="<<noThreads;
		#endif
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
	    //LOG(INFO)<<"Started a new random binary pattern generator with patternSize = "<<patternSize<<", noThread = "<<noThreads<<", row part per thread = "<<partPerThread<<"\n";
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
		std::cout<<"ERROR: "<<e.what()<<", in file: "<<__FILE__<<", and line: "<<__LINE__<<std::endl;
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
		/*
		 * //tightly coupled, fast writing impl
		 * //fixed for multiple threads
		 * unsigned long long commaOffset=rowStart*2;
		 */
		for(;rowStart<rowEnd;rowStart++)
		{
			destinationRow[rowStart]=singularity_checker(randomRow[rowStart],rowStart);
			/*
			 * //tightly coupled, fast writing impl
			 * previousRowChar[rowStart+(commaOffset++)]=charType[destinationRow[rowStart]];
			 * previousRowChar[rowStart+(commaOffset)]=charType[2];
			 */
		}
	}
	catch(const std::exception &e)
	{
		//		LOG(ERROR)<<e.what()<<" , for thread: "<<std::this_thread::get_id()<<std::endl;
		std::cout<<"ERROR: "<<e.what()<<" , for thread: "<<std::this_thread::get_id()<<", in file: "<<__FILE__<<", and line: "<<__LINE__<<std::endl;

	}
}

//called for pattern genenration;
bool Random_patterns_generator::generatePattern()
{
	/*
	 * The work horse that loops to generate all the required row by calling "generate_random_row()" among threads
	 */
	try {
		 // generate Current row
		 for(unsigned long long rowIdx=1;rowIdx<patternSize;rowIdx++)
		 {
			 //start a background thread to start writing to files
			 std::thread backGroundWriterThread=std::thread(&FileWriter::savePatterns,&fWriter,std::ref(previousRow));
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
			backGroundWriterThread.join();
			/*
			 * 	//tighlty coupled but faster impl
			 * for(unsigned long long i=0;i<patternSize;i++)
			 * {
			 *   previousRowCharBuffer[i]=charType[previousRow[i]];
			 * }
			 * fWriter.savePattern(previousRowCharBuffer,patternSize);
			 * fWriter.savePattern(previousRow);
			 */
		  // make current row the previous row O(1)
		  previousRow.swap(currentRow);
		 }
	}
	catch (const std::exception &e)
	{
		//		LOG(INFO)<<e.what()<<std::endl;
		std::cout<<"ERROR: "<<e.what()<<" , for thread: "<<std::this_thread::get_id()<<", in file: "<<__FILE__<<", and line: "<<__LINE__<<std::endl;

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

inline unsigned long long Random_patterns_generator::max(unsigned long long frst,unsigned long long& secnd)
{
	return (frst>secnd)?frst:secnd;
}
Random_patterns_generator::~Random_patterns_generator() {
	/*
	 * //tightly coupled but faster impl
	 * for(unsigned long long i=0;i<patternSize;i++)
	 * {
	 *   previousRowCharBuffer[i]=charType[previousRow[i]];
	 *   previousRowCharBuffer[i]=charType[3];
	 *  }
	 * fWriter.savePattern(previousRowCharBuffer,patternSize);
	 */
	//saving the last row
	fWriter.savePatterns(previousRow);
	//close open resources
	#ifdef _DebugMode
	  std::cout<<"closing resources"<<std::endl;
	#endif
	//LOG(INFO)<<"closing resources"<<std::endl;
	//outputFile.flush();
	//outputFile.close();
	}

}
