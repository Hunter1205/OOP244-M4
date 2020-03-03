// TODO: add file header comments here
//Milestone 2
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/11/2019

#include <iostream>

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

namespace ama{
	class ErrorState{
		
		const char* messages; //address of the message

	public:
		//should not allow copying of any ErrorState object
		ErrorState(const ErrorState& other) = delete;
		//does not allow copy assignment
		ErrorState& operator=(const ErrorState& other) = delete;
		//stores a copy the text received in the parameter
		ErrorState& operator=(const char* pText);

		//deallocates memory that has been dynamically allocated by the current object
		~ErrorState();

		explicit ErrorState(const char* messages = nullptr);
		
		//stores a copy the text received in the parameter
		void message(const char* pText);
		//returns address of the message stored in current object
		const char* message() const;
		//Sets the message of the current object if valid
		void isValid(const char* valid);
		//returns true/false if message object is empty
		operator bool() const;
	};
	//displays the message stored in message object
	std::ostream& operator<<(std::ostream& os, const ErrorState& es);
}
#endif