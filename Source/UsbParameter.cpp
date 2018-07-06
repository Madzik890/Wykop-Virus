#include "UsbParameter.hpp"
#include <Windows.h>


void UsbParameter::mainFunc()
{
	getDeviceList();
}

std::string UsbParameter::getInformation()
{
	std::string text;
	text += "\n [Parametry USB] \n";
	text += "Liczba podlaczonych urzadzen: " + std::to_string(u_connectedDevices) + "\n";
	text += "[/Parametry USB] \n";
	return text;
}

bool UsbParameter::getDeviceList()
{
	UINT nDevices = 0;
	GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

	// Got Any?
	if (nDevices < 1)
		return false;// Exit

	// Allocate Memory For Device List
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];

	// Got Memory?
	if (pRawInputDeviceList == NULL)
		return false;// Error

	// Fill Device List Buffer
	int nResult;
	nResult = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

	// Got Device List?
	if (nResult < 0)
	{
		// Clean Up
		delete[] pRawInputDeviceList;

		return false;// Error
	}

	// Loop Through Device List
	u_connectedDevices = nDevices;

	// Clean Up - Free Memory
	delete[] pRawInputDeviceList;
}

