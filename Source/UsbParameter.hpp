#pragma once
#include "Parameter.hpp"
#include <list>

#ifndef USBPARAMETER_HPP
#define USBPARAMETER_HPP


class UsbParameter
	:public Parameter
{
public:
	void mainFunc();
	std::string getInformation();
private:

	bool getDeviceList();
	int u_connectedDevices = 0;
};


#endif
