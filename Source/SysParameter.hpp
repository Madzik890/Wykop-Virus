#pragma once
#include "Parameter.hpp"
#include <Windows.h>

#ifndef SYSPARAMETER_HPP
#define SYSPARAMETER_HPP

class SysParameter
	:public Parameter
{
public:

	void mainFunc();
	std::string getInformation();
private:

	//foreground windows 
	std::string ch_ForeGroundWindows;
	void getForegroundInfo();

	//cpu
	std::string ch_ProcessorArchitecture;
	std::string getProcessorBrand(WORD processorArchitecture);
	std::string ch_ProcessorType;	
	std::string getProcessorType(DWORD processorType);
	void getProcessorInfo();

	//user
	std::string ch_UserName;	
	void getUserInfo();

	//RAM
	float f_RamSize;
	void getRamInfo();
};

#endif