/*
 * RandomGeneratorTester.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "RandomGeneratorTester.h"

namespace PatternGeneratorTesterNS {

RandomGeneratorTester::RandomGeneratorTester(unsigned short generatorType,std::string directory_path):generatorType(generatorType),directory_path(directory_path)
{
	try{
		srand(static_cast<unsigned int>(clock()));
		std::experimental::filesystem::create_directories(directory_path);
		std::experimental::filesystem::create_directories("statisics/"+directory_path);
		std::cout<<"created directories\n";

	}
	catch(const std::exception &e)
	{
		std::cout<<"exception,"<<e.what()<<"\n";
	}
}

bool RandomGeneratorTester::testThreadsSpeed(unsigned short threadRange,unsigned short patternRange) {
	//e7m
	try {
		vec<vec<vector_of_unsigned_long>> statistics_matrix
			(threadRange,
			 vec<vector_of_unsigned_long> (patternRange,vector_of_unsigned_long(0)));

		std::string statfileName="statisics/"+directory_path+"/threadsVSPattern_stats_"+std::to_string((static_cast<long int> (time(NULL))))+".txt";
		std::ofstream statoutputFile;
		statoutputFile.open(statfileName);
		std::cout<<statfileName<<std::endl;
		statoutputFile<<"threads(no),pattern width,time(ns)\n";
		std::cout<<"starting tests"<<std::endl;

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
			std::cout<<"finsihed a test"<<std::endl;
			statistics_matrix[noThreads-1][gridWidth-1].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
			delete generator;
		}
		std::experimental::filesystem::remove_all(directory_path);
		std::cout<<"starting statwriting\n";

		//writing statistics to file
		for(unsigned short threadIdx=0;threadIdx<statistics_matrix.size();threadIdx++)
		{
			for(unsigned long long patternIdx=0;patternIdx<statistics_matrix[threadIdx].size();patternIdx++)
				{
					if(statistics_matrix[threadIdx][patternIdx].size()>0)
					{
						double average=0;
						for(unsigned long long repeatedTestIdx=0;repeatedTestIdx<statistics_matrix[threadIdx][patternIdx].size();repeatedTestIdx++)
							average+=statistics_matrix[threadIdx][patternIdx][repeatedTestIdx];
						average=average/statistics_matrix[threadIdx][patternIdx].size();
						statoutputFile<<std::fixed<<threadIdx+1<<","<<patternIdx+1<<","<<average<<"\n";
					}
				}

		}
		std::cout<<"closing resources\n";
		statoutputFile.close();
	}
	catch(...)
		{
			std::cout<<"\nexception,"<<std::endl;
		}
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
RandomGeneratorTester::patternCorrectnessTester(unsigned short patternRange=10000) {
//generate lots of files
	try {
			std::string statfileName="tempTests/"+directory_path+"/";
			for(unsigned short int testNo=1;testNo<1000;testNo++)
			{
				unsigned int gridWidth=rand()%patternRange+1;
				unsigned short noThreads=rand()%threadRange+1;
				generator =
						PatternGeneratorNS::GeneratorFactory::
						make_generator(static_cast <PatternGeneratorNS::GeneratorFactory::generator_type> (generatorType)
						,gridWidth,noThreads,directory_path);
					//generating the patterns
				generator->generatePattern();
				std::cout<<"finsihed a test"<<std::endl;
				delete generator;
			}

			//read files to test for correctness
			//for each file
			{

				do
				{
					bool cell;
				    istringstream iss(str);
				    getline(iss, cell, ',');
				    do{
				    currentRow.push_back(cell);
				    }while (getline(iss, cell, ','));
				    //check current row with previous row

				    //swap current with previous

				}while (getline(data, str));
			}
//			std::experimental::filesystem::remove_all(directory_path);
		}
		catch(...)
			{
				std::cout<<"\nexception,"<<std::endl;
			}




//delete test directory


}

RandomGeneratorTester::~RandomGeneratorTester() {
	// TODO Auto-generated destructor stub
//	if(generator!=nullptr)
//		delete generator;

}

} /* namespace PatternGeneratorTester */
