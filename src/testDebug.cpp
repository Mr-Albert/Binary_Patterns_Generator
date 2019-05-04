//============================================================================
// Name        : PatternTester.cpp
// Author      : Mina_albert
// Version     :

//============================================================================
//#define _DebugMode replaced with the compiler flag

#include "Binary_pattern_generator/GeneratorFactory.h"
#include <iostream>
#include <sstream>
#include <string>
#include <ios>
#include <limits>
#include<cstdlib>
#include <experimental/filesystem>
#include "userInputClass/userInput.h"
//#include "easyLogger/easylogging++.h"
////#define ELPP_THREAD_SAFE
//INITIALIZE_EASYLOGGINGPP
//logger library keeps break, ;;ditching

bool valid(const std::vector<unsigned short *> &argList)
{
	/*
	 *
	 * validator function that can be used by the user/programmer
	 *  to validate agains the user input through the UserInput class interface
	 *
	 */
	//if the first parameter is not equal to either of the 2nd or the 3rd param return false
	if((*argList[0])!=(*argList[1])&&(*argList[0])!=(*argList[2]))
		return false;
	return true;
}
int main() {
	try{
//		initializeLogger();
//		LOG(INFO) << "starting main";
		unsigned long long gridWidth;
		unsigned long long noThreads;
		//declaring a new scope to destroy the variable after i get what i want with them
		{
			//new user input class obj to get the  gridWidth and number of threads
			userInput<unsigned long long,unsigned short *> inputObj;
			inputObj.getInput(gridWidth,"Please input the grid Width");
			inputObj.getInput(noThreads,"Input the number of desired threads");
		}
		//to determine which derived(type of generator ) class to instantiate
		unsigned short inputMethod;
		{
			//options
			unsigned short option1=1,option2=2;
			// new user input class with specific validation
			userInput<unsigned short,unsigned short *> inputObj;
			//initializing the callback(funcPointer) input parameters
			std::vector<unsigned short *> argList={&inputMethod,&option1,&option2};
			//getting user input while passing callback function with its params
			inputObj.getInput(inputMethod,"Input the Pattern generator Method,'1' for Random , and '2' for All possible patterns : ",argList,valid);
		}

		//getting the generator
		PatternGeneratorNS::PatternGenerator  *generator =
			PatternGeneratorNS::GeneratorFactory::
			make_generator(static_cast <PatternGeneratorNS::GeneratorFactory::generator_type> (inputMethod)
			,gridWidth,noThreads,"PatternFiles");
		//generating the patterns
		generator->generatePattern();
		//#CR give it to the factory's terminator function
//		delete generator;
		PatternGeneratorNS::GeneratorFactory::destory_generator(generator);
		std::cin.get();
		std::cin.get();
	}
	catch (const std::exception& e)
	{
		//		LOG(ERROR) <<e.what();
		std::cout<<" ERROR "<<e.what();
	}
	return 0;
}

