#pragma once

#include <string>

#ifndef PARAMETER_HPP
#define PARAMETER_HPP

/// <summary>
/// Interface for easier management all parameters  
/// </summary>
struct Parameter
{
	virtual void mainFunc() = 0;
	virtual std::string getInformation() = 0;
};

#endif
