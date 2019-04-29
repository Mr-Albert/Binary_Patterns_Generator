/*
 * userInput.h
 *
 *  Created on: Apr 29, 2019
 *      Author: Mina
 */

#ifndef USERINPUTCLASS_USERINPUT_H_
#define USERINPUTCLASS_USERINPUT_H_
#include<string>
template  <class  inputTemplateType>
class userInput {
private:
	userInput();
	virtual ~userInput();
public:
	static bool getInput(inputTemplateType &inputVariable,std::string inputPrompt);
};

#endif /* USERINPUTCLASS_USERINPUT_H_ */
