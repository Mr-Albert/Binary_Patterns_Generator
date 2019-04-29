////============================================================================
//// Name        : PatternTester.cpp
//// Author      : Mina_albert
//// Version     :
//
////============================================================================
//
//#include "Binary_pattern_generator/GeneratorFactory.h"
//#include <iostream>
//#include <ios>
//#include <limits>
//#include<cstdlib>
//#include <experimental/filesystem>
////#include "easyLogger/easylogging++.h"
////#define ELPP_THREAD_SAFE
////INITIALIZE_EASYLOGGINGPP
//int main() {
// 	unsigned long long gridWidth;
//	unsigned long long testLoops,noThreads;
//	  srand(static_cast<unsigned int>(clock()));
//	  std::cout<<"enter number of test loops:\n";
//	  	std::cin>>testLoops;
//	  std::cout<<"enter number of threads:\n";
//		std::cin>>noThreads;
//
//	for(;testLoops>0;testLoops--)
//	{
////		std::cout<<"loop number "<<testLoops<<std::endl;
//		gridWidth=rand()%1000 +1;
//		//get pattern generator depending on the user input
//		PatternGeneratorNS::PatternGenerator  *generator =
//				PatternGeneratorNS::GeneratorFactory::
//				make_generator(PatternGeneratorNS::GeneratorFactory::random_pattern_generator,gridWidth,noThreads);
//		generator->generatePattern();
//
//		delete generator;
//
//	}
////	auto it=std::experimental::filesystem::current_path();
//    for(auto& p: std::experimental::filesystem::directory_iterator("randomFiles"))
//        std::cout << p.path() << '\n';
//	return 0;
//}
