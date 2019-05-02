////============================================================================
//// Name        : PatternTester.cpp
//// Author      : Mina_albert
//// Version     :
//
////============================================================================
////#define _DebugMode replaced with the compiler flag
//
//#include "Binary_pattern_generator/GeneratorFactory.h"
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <ios>
//#include <limits>
//#include<cstdlib>
//#include <experimental/filesystem>
//#include "easyLogger/easylogging++.h"
//#include "userInputClass/userInput.h"
////
////
//#define ELPP_THREAD_SAFE
//INITIALIZE_EASYLOGGINGPP
////inline void initializeLogger()
////{
////	    el::Configurations defaultConf;
////	    defaultConf.setToDefault();
////	    defaultConf.setGlobally(
////	                     el::ConfigurationType::Filename,"PatternGenerationLog.log");
////	    defaultConf.setGlobally(
////	                    el::ConfigurationType::ToFile,"true");
////	    defaultConf.setGlobally(
////	                    el::ConfigurationType::ToStandardOutput,"false");
////	    el::Loggers::reconfigureLogger("default", defaultConf);
////	//
////}
//
//bool valid(const std::vector<unsigned short *> &argList)
//{
//	//if the first parameter is not equal to either of the 2nd or the 3rd param return false
//	if((*argList[0])!=(*argList[1])&&(*argList[0])!=(*argList[2]))
//		return false;
//	return true;
//}
//int main() {
//	try{
////		initializeLogger();
//		unsigned long long gridWidth;
//		unsigned long long noThreads;
//		//declaring a new scope to destroy the variable after i get what i want with them
//		{
//			//new user input class obj to get the  gridWidth and number of threads
//			userInput<unsigned long long,unsigned short *> inputObj;
//			inputObj.getInput(gridWidth,"Please input the grid Width");
//			inputObj.getInput(noThreads,"Input the number of desired threads");
//		}
//		//to determine which derived(type of generator ) class to instantiate
//		unsigned short inputMethod;
//		{
//			//options
//			unsigned short option1=1,option2=2;
//			// new user input class with specific validation
//			userInput<unsigned short,unsigned short *> inputObj;
//			//initializing the callback(funcPointer) input parameters
//			std::vector<unsigned short *> argList={&inputMethod,&option1,&option2};
//			//getting user input while passing callback function with its params
//			inputObj.getInput(inputMethod,"Input the Pattern generator Method,'1' for Random , and '2' for All possible patterns : ",argList,valid);
//		}
//
//		//getting the generator
//		PatternGeneratorNS::PatternGenerator  *generator =
//			PatternGeneratorNS::GeneratorFactory::
//			make_generator(static_cast <PatternGeneratorNS::GeneratorFactory::generator_type> (inputMethod)
//			,gridWidth,noThreads);
//		//generating the patterns
//		generator->generatePattern();
//		delete generator;
//	}
//	catch (const std::exception& e)
//	{
////		LOG(ERROR) <<e.what();
//	}
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//////============================================================================
////// Name        : PatternTester.cpp
////// Author      : Mina_albert
////// Version     :
////
//////============================================================================
////
////#include "Binary_pattern_generator/GeneratorFactory.h"
////#include <iostream>
////#include <ios>
////#include <limits>
////#include<cstdlib>
////#include <experimental/filesystem>
//////#include "easyLogger/easylogging++.h"
//////#define ELPP_THREAD_SAFE
//////INITIALIZE_EASYLOGGINGPP
////int main() {
//// 	unsigned long long gridWidth;
////	unsigned long long testLoops,noThreads;
////	  srand(static_cast<unsigned int>(clock()));
////	  std::cout<<"enter number of test loops:\n";
////	  	std::cin>>testLoops;
////	  std::cout<<"enter number of threads:\n";
////		std::cin>>noThreads;
////
////	for(;testLoops>0;testLoops--)
////	{
//////		std::cout<<"loop number "<<testLoops<<std::endl;
////		gridWidth=rand()%1000 +1;
////		//get pattern generator depending on the user input
////		PatternGeneratorNS::PatternGenerator  *generator =
////				PatternGeneratorNS::GeneratorFactory::
////				make_generator(PatternGeneratorNS::GeneratorFactory::random_pattern_generator,gridWidth,noThreads);
////		generator->generatePattern();
////
////		delete generator;
////
////	}
//////	auto it=std::experimental::filesystem::current_path();
////    for(auto& p: std::experimental::filesystem::directory_iterator("randomFiles"))
////        std::cout << p.path() << '\n';
////	return 0;
////}
