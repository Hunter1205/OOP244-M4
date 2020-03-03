// TODO: add file header comments here
//Milestone 2
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/11/2019

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#include "ErrorState.h"

namespace ama{
	ErrorState::ErrorState(const char* errorStateMessage){
		//places object into a safe empty state if the address is nullptr
		isValid(errorStateMessage);
	}

	ErrorState::~ErrorState(){
		//deallocates memory that has been dynamically allocated by the current object
		//delete messages;
	}

	ErrorState::operator bool() const{
		bool valid;
		//returns true/false if message object is empty
		if(messages != '\0'){
			valid = true;
		}
		return valid;
	}

	void ErrorState::message(const char* pText){
		isValid(pText);
	}

	ErrorState& ErrorState::operator=(const char* pText){
		//stores a copy the text received in the parameter
		isValid(pText);
		return *this;
	}

	const char* ErrorState::message() const{
		//returns address of the message stored in current object
		return messages;
	}

	//Sets the message of the current object if valid
	void ErrorState::isValid(const char* valid){
		if(valid == '\0'){
			messages = nullptr;
		}else if(valid[0] == '\0'){
			messages = nullptr;
		}else{
			//stores a copy the text received in the parameter
			messages = valid;
		}
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& es){
		if(es != '\0'){
			//displays messages stored in message object
			os << es.message();
		}
		return os;
	}
}