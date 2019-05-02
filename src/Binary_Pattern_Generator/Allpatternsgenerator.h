///*
// * Allpatternsgenerator.h
// *
// *  Created on: Apr 26, 2019
// *      Author: Mina
// */
//
//#ifndef ALLPATTERNSGENERATOR_H_
//#define ALLPATTERNSGENERATOR_H_
//#include "PatternGenerator.h"
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include<iostream>
//#include <fstream>
//#include<string>
//#include <time.h>
//#include <iostream>
//#include <experimental/filesystem>
//#include <thread>
//#include <stdexcept>
//namespace PatternGeneratorNS
//{
//// the field of combinatorics : matrices rotation ,reflection,etc
////should be looked at for large grids for this generation mode
//class All_patterns_generator:public PatternGenerator {
//		//threads array //maybe should be moved up in the classes inh tree
//		std::vector<std::thread> PatternsThreadArray;
//		//un ordered map with a key : the hash value of the first row in any file with const size=(2^pattern_size):infeasible......
//		//and a value of all the file pointer that point to a file that starts with that row
//		// food for thought...i think too many file pointer might cause too many file descriptors open error, maybe store with file names?
//		unordered_map<vector<bool>,vector<std::string>> allTheGeneneratedFiles;
//		//resultant file and path
//	    std::ofstream outputFile;
//	    std::string directory_path="randomFiles";
//	    std::string fileName="randomPatternsFile_";
//		//how many items each thread should work on
//	    unsigned int partPerThread;
//	    //pattern generator worker
//		bool generatePatternWorker();
//		//generate random binary inside shared mem randomRow
//		inline void generate_random_pattern();
//		//generate random row of binaries
//		void generate_random_row(std::vector<bool> &destinationRow,unsigned long long rowStart,unsigned long long rowEnd);
//		inline unsigned long long max(unsigned long long frst,unsigned long long& secnd);
//		//saves rows into the resultant file
//		bool savePattern();
//		//checks for singularitys
//		inline bool singularity_checker(const bool &binaryInput,unsigned long long &currentRowPosition);
//
//	public:
//		All_patterns_generator(unsigned long long patternSize=1,unsigned short noThreads=1,std::string directory_path="");
//		//entry point for pattern generation
//		bool generatePattern();
//		virtual ~Random_patterns_generator();
//};
//
//#endif /* ALLPATTERNSGENERATOR_H_ */
//}
