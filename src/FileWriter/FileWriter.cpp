/*
 * FileWriter.cpp
 *
 *  Created on: May 3, 2019
 *      Author: Mina
 */

#include "FileWriter.h"
#include <bitset>

namespace PatternGeneratorNS {
//may be make it a tempelate for extendability
inline char FileWriter::serialize( const bool &inputBool)
{
	return alphabet[inputBool];
}
inline char FileWriter::serialize(const char *s)
{
	return std::string(s)[0];
}

//a faster implementation than the abandoned manual buffer
//blazing fast!!..kinda
FileWriter::FileWriter(unsigned long long inputSize,std::string fileNamePrefix,std::string directory,unsigned int streamBufferSize):outputBufferSize(inputSize*2),streamBufferSize(streamBufferSize) {
	/*
	 * inputSize: size of vector/array input , fileNamePrefix, directory :directory to save the file in, streamBufferSize: file stream desired buffer size
	 * reserving the buffer vecBuffer to be used as file buffer
	 * and char buffer to convert vector<bool> to chars ...as vector<bool> is not really a container..can't be used
	 * then setting the file buffer to vecBuffer to speed up wrriting
	 * then creating a unique file name
	 * and opening resources(file(s))                //#CR check if the file already exists
	 * then enabling the file exceptions mechanism
	 * then opening the file
	 */
	vecBuffer= new char [streamBufferSize];
	charBuffer= new char [this->outputBufferSize];
	outputFile.rdbuf()->pubsetbuf(vecBuffer, streamBufferSize);
	std::experimental::filesystem::create_directories(directory);
	fileNamePrefix=directory+"/"+fileNamePrefix;
	fileNamePrefix+=std::to_string((static_cast<long int> (time(NULL))))+".txt";
	currentFileName=fileNamePrefix;
	outputFile.exceptions( std::ios_base::failbit |std::ios_base::badbit );
	outputFile.open(currentFileName,std::ios::out );
	std::cout<<"writing to file: "<<currentFileName<<std::endl;


}
//blazing fast!!..kinda
inline bool FileWriter::savePattern(char * toBeWrittenVector,unsigned long long &size)
{
	/*
	 * this function save the input as is
	 * ---done--->this funcntion should be made in its own class (pattern generator should only generate patterns and not responsible for saving them)
	 * ---missing--->and taking a stream & as parameter for better extensibility (closed for mod ,open for extension principle )
	 *
	 */
		#ifdef _TestMode
			auto savePatternStart = std::chrono::high_resolution_clock::now();
		#endif
	try{
		outputFile.write(toBeWrittenVector,size);
	}
	catch (const std::exception &e)
	{
		std::cout<<e.what()<<", savePattern(char * toBeWrittenVector,unsigned long long &size) :="<<size<<std::endl;
	}
		#ifdef _TestMode
			auto savePatternEnd = std::chrono::high_resolution_clock::now();
			auto saveTime+=std::chrono::duration_cast<std::chrono::nanoseconds>(savePatternEnd - savePatternStart).count();
		#endif

	return 1;
}


bool FileWriter::savePatterns(std::vector<bool>& toBeWrittenVector)
{
	/*
	 * takes (the non-container) vector <bool> ,parse it into a char array and pass it to the actual file writer inline function  savePattern(char *,ull &size)
	 */
	try{
		unsigned long long i=0,j=0;
		for(i=0,j=0;j<outputBufferSize/2-1&&i<outputBufferSize-1;i++,j++)
		{
			charBuffer[i]=serialize(toBeWrittenVector[j]);
			charBuffer[++i]=serialize(",");
		}
		charBuffer[i]=serialize(toBeWrittenVector[j]);
		charBuffer[++i]=serialize("\n");
		savePattern(charBuffer,outputBufferSize);
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<", while saving vector<bool> at file: "<<__FILE__<<", line = "<<__LINE__<<std::endl;

	}
	return 0;
}

bool FileWriter::savePatterns(std::vector<unsigned long long>& toBeWrittenVector)
{

	try{
 		unsigned long long input_indx=0,buffer_indx=0;
		for(;input_indx<toBeWrittenVector.size()-1&&buffer_indx<outputBufferSize-2;input_indx++,buffer_indx)
		{
			for(unsigned short bits=63;bits>=0&&buffer_indx<outputBufferSize-2;bits--)
			{
				charBuffer[buffer_indx++]=(toBeWrittenVector[input_indx]>>bits & 1)?'1':'0';
				charBuffer[buffer_indx++]=',';
			}
		}
		unsigned short bits=63;
		for(;bits>0&&buffer_indx<outputBufferSize-2;bits--)
		{
			auto tmp=toBeWrittenVector[input_indx]>>bits;
			charBuffer[buffer_indx++]=
					(tmp & 1!=0)?
							'1':'0';
			charBuffer[buffer_indx++]=',';
		}
		charBuffer[buffer_indx++]=(toBeWrittenVector[input_indx]>>bits & 1)?'1':'0';
		charBuffer[buffer_indx++]='\n';
//		std::cout<<std::bitset<64>(toBeWrittenVector[input_indx])<<std::endl;
		savePattern(charBuffer,outputBufferSize);
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<", while saving vector<bool> at file: "<<__FILE__<<", line = "<<__LINE__<<std::endl;

	}
	return 0;
}

FileWriter::~FileWriter() {
	std::cout<<"closing fileWriter"<<std::endl;
	outputFile.flush();
	delete []vecBuffer;
	delete []charBuffer;
}

} /* namespace PatternGeneratorNS */
