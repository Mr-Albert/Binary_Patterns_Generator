//
//#include "FileWriter.h"
//#include <vector>
//#include <iostream>
//#include <chrono>
//
//int main() {
//	unsigned long long buffSize=5;
////	PatternGeneratorNS::FileWriter writerTest(buffSize,"test","speedncorrectness");
//
//	unsigned long long size=10000;
//	unsigned long long tsize;
//	PatternGeneratorNS::FileWriter writerTest(size,"test","speedncorrectness",buffSize);
//	unsigned long long x=1;
//	tsize=size;
//	std::vector<bool>stressVector(size,1);
//	char * charBuffer=new char[size];
//	char * charBufferNewLine=new char[x];
//	charBufferNewLine[0]=std::string("\n")[0];
//	std::string alpha="01";
//	for(unsigned long long i=0 ;i<stressVector.size();i++)
//	{
//		charBuffer[i]=alpha[stressVector[i]];
//	}
//	auto start = std::chrono::high_resolution_clock::now();
//
//	for(;size>0;size--){
//		stressVector[size-1]=0;
//		charBuffer[size-1]=std::string("0")[0];
//		writerTest.savePattern(charBuffer,tsize);
//		writerTest.savePattern(charBufferNewLine,x);
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	std::cout<<"time taken to process vector of size: "<<tsize<<" and buffer of size: "<<buffSize<< " is: "
//			<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/1000000000.0<<std::endl;
//
//	return 0;
//}
