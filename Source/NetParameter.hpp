#pragma once
#include "Parameter.hpp"

#ifndef NETPARAMETER_HPP
#define NETPARAMETER_HPP

class NetParameter
	:public Parameter
{
public:
	void mainFunc();
	std::string getInformation();
private:
	std::string ch_IpAddress = "127.0.0.0";
	std::string ch_AdapterName;
	void getAdapterInfo();
	void getIpAddress();
};

#endif