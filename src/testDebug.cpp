//============================================================================
// Name        : PatternTester.cpp
// Author      : Mina_albert
// Version     :

//============================================================================
//#define _DebugMode replaced with the compiler flag

#include "Binary_pattern_generator/GeneratorFactory.h"
#include <iostream>
#include <ios>
#include <limits>
#include<cstdlib>
#include <experimental/filesystem>
#include "easyLogger/easylogging++.h"
#include "userInputClass/userInput.h"


#define ELPP_THREAD_SAFE
INITIALIZE_EASYLOGGINGPP

bool valid(std::vector<unsigned short *> argList)
{
	std::cout<<"i entered the function,with params:"<<(*argList[0])<<(*argList[1])<<(*argList[2])<<"\n";
	if((*argList[0])!=(*argList[1])&&(*argList[0])!=(*argList[2]))
		return false;
	return true;
}
int main() {

 	unsigned long long gridWidth;
	unsigned long long noThreads;
	{
		userInput<unsigned long long,unsigned short *> inputObj;
		inputObj.getInput(gridWidth,"Please input the grid Width");
		inputObj.getInput(noThreads,"Input the number of desired threads");
	}
	unsigned short inputMethod;
	unsigned short option1=1,option2=2;
	{
		userInput<unsigned short,unsigned short *> inputObj;
		std::vector<unsigned short *> argList={&inputMethod,&option1,&option2};
		bool (*fcnPtr)(std::vector<unsigned short *>)=valid;
		std::cout<<" function address "<<fcnPtr<<"\n";
		inputObj.getInput(inputMethod,"Input the Pattern generator Method,'1' for Random , and '2' for All possible patterns : ",argList,fcnPtr);
	}
		std::cout<<gridWidth<<noThreads<<inputMethod<<std::endl;
	//	PatternGeneratorNS::PatternGenerator  *generator =
//					PatternGeneratorNS::GeneratorFactory::
//					make_generator(PatternGeneratorNS::GeneratorFactory::random_pattern_generator,gridWidth,noThreads);
//			generator->generatePattern();
}
