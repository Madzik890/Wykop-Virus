#pragma once
#include <string>
#include <list>
#include "Parameter.hpp"

#ifndef INFORMATION_HPP
#define INFORMATION_HPP

class Information
{
public:
	static std::list<Parameter*>parameters;
	static std::string getSummaryInfo();

	static void createParameteres();
	static void clearParameteres();
private:
	Information();
	Information(Information &);
};

#endif