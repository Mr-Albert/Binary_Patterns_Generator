/*
 * userInput.h
 *
 *  Created on: Apr 29, 2019
 *      Author: Mina
 */

#ifndef USERINPUTCLASS_USERINPUT_H_
#define USERINPUTCLASS_USERINPUT_H_
#include<string>
#include <iostream>
#include <ios>
#include <limits>
#include<vector>
template  <typename  inputTemplateType,typename  argsTemp=unsigned short>
class userInput {
public:
	bool getInput(inputTemplateType &inputVariable,const std::string inputPrompt,std::vector<argsTemp> argList={},bool (* validationFuncion)(std::vector<argsTemp>)=nullptr);
	bool test();
//	inputTemplateType test;
};

/*
 * userInput.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: Mina
 */

template <typename  inputTemplateType, typename argsTemp>
bool userInput<inputTemplateType,argsTemp>::getInput(inputTemplateType &inputVariable,const std::string inputPrompt,std::vector<argsTemp> argList,bool (* validationFuncion)(std::vector<argsTemp>))
{
		bool validInput=false;
		do
		{
			std::cout <<inputPrompt<<"\n";
			std::cin >> inputVariable;
			if (!std::cin.good()||(validationFuncion!=nullptr && !(*validationFuncion)(argList)))
			{
				//something went wrong, we reset the buffer's state to good
				std::cin.clear();
				//and empty it using the max number of allowable input
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout << "Invalid input; please re-enter." << std::endl;

			}
			else
			{
				  //everything went well, we'll get out of the loop and return the value
				  validInput = true;
			}
		    }while (!validInput);
		return 1;
}




#endif /* USERINPUTCLASS_USERINPUT_H_ */
