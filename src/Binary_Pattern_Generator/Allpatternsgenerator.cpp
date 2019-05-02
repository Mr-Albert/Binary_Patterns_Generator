/*
 * Allpatternsgenerator.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: Mina
 */

#include "Allpatternsgenerator.h"
namespace PatternGeneratorNS
{
All_patterns_generator::All_patterns_generator(unsigned long long patternSize,unsigned short noThreads,std::string directory_path)
{
	/*
	 *
	 * generate all possible first rows and put their file pointers in the map
	 *
	 */
	vector<bool>  currentRow(patternSize,0);
	do
	{
		//save the current row in a file and in map
		fileName="AllPatterns_"+stoi(hashBVector(currentRow))+stoi(allTheGeneneratedFiles[currentRow].size());
		allTheGeneneratedFiles[currentRow].push_back(fileName);
	}while(increaseRow(currentRow));
	//generate second row for each first row and connect them to their corresponding file
	vector<bool>  seconedRow(patternSize,0);
	do
	{
		//for each initial allTheGeneneratedFiles first row ,check if the current row can be the one under it
		//if yes create new file with the first row and append current 2nd row,also vector[prevRow].push(prevRow)
		//save the current row in a file and in map
	}while(increaseRow(currentRow));
}

bool All_patterns_generator::generatPattern()
{
	/*
	 *
	 * All possible first two rows are now generated and connected together
	 * for each file check size,if not complete ;check last row,
	 * see how many patterns can be appended to it(already calculated)
	 * access every file that starts with these rows (already exists)
	 * concat current file contents with the connected file for each possible allowed pattern
	 * (excluding the first row) in a new file
	 *
	 */
	for(unsigned long long rowIdx=0;rowIdx<rowToBeIncreased.size();rowIdx++)
	{
		if(rowToBeIncreased[rowIdx]==0)
		{
			rowToBeIncreased[rowIdx]=1;
			return true;
		}
		else
		{
			rowToBeIncreased[rowIdx]=0;
		}

	}
	return false;
}
}















inline bool All_patterns_generator::increaseRow(vector<bool> & rowToBeIncreased)
{
	/*
	 *
	 * generate all possible first rows and put their file pointers in the map
	 * N.B: LSB is on the left
	 * iterate till you find a zero,flip it and every lesser significant bit == rowAsNum+1
	 *
	 */
	for(unsigned long long rowIdx=0;rowIdx<rowToBeIncreased.size();rowIdx++)
	{
		if(rowToBeIncreased[rowIdx]==0)
		{
			rowToBeIncreased[rowIdx]=1;
			return true;
		}
		else
		{
			rowToBeIncreased[rowIdx]=0;
		}

	}

	return false;
}
}
