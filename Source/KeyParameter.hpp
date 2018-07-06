#pragma once
#include "Parameter.hpp"
#include <Windows.h>

#ifndef KEYPARAMETER_HPP
#define KEYPARAMETER_HPP

class KeyParameter
	:public Parameter
{
public:
	void mainFunc();
	std::string getInformation();
private:
	int u_PressedKeys;//count of the pressed keys
	void getLastEvent();

	void blinkKeyLed();//blink the keyboard light
};

#endif
