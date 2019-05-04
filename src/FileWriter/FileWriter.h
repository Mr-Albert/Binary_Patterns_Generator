/*
 * FileWriter.h
 *
 *  Created on: May 3, 2019
 *      Author: Mina
 */

#ifndef FILEWRITER_FILEWRITER_H_
#define FILEWRITER_FILEWRITER_H_
#include <fstream>
#include<string>
#include <experimental/filesystem>
#include <vector>
#include <iostream>
namespace PatternGeneratorNS {

class FileWriter {
private:
	std::ofstream outputFile;
	std::string currentFileName;
	unsigned long long outputBufferSize;
	unsigned int streamBufferSize;
	inline char serialize( const bool &inputBool);
	inline char serialize( const char* s);
	char *charBuffer;
	char *vecBuffer;
	std::string alphabet="01";

public:
	FileWriter(unsigned long long inputSize,std::string fileNamePrefix="file_",std::string directory="..",unsigned int streamBufferSize=2048*2048);
	bool savePatterns(std::vector<bool>& toBeWrittenVector);
	inline bool savePattern(char * toBeWrittenVector,unsigned long long &size);
	virtual ~FileWriter();
};

} /* namespace PatternGeneratorNS */

#endif /* FILEWRITER_FILEWRITER_H_ */
