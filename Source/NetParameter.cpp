#include "NetParameter.hpp"
#include <Windows.h>
#include <wininet.h>
//#include <winsock2.h>
#include <iphlpapi.h>

#define IPADDRESS_WEBSITE "http://myexternalip.com/raw"

void NetParameter::mainFunc()
{
	getIpAddress();//get a public IP address
	getAdapterInfo();//get the names installed network adapters
}

/// <summary>
/// Gets the information.
/// </summary>
/// <returns></returns>
std::string NetParameter::getInformation()
{
	std::string text; 
	text += "\n [Parametry sieciowe] \n";
	text += "Numer IP: " + ch_IpAddress;
	text += "Kary siecowe: " + ch_AdapterName;
	text += "[/Parametry sieciowe] \n";
	return text;
}

/// <summary>
/// Gets the network adapter information via PIP_ADAPTER_INFO
/// </summary>
void NetParameter::getAdapterInfo()
{
	IP_ADAPTER_INFO  *pAdapterInfo;
	ULONG            ulOutBufLen;
	DWORD            dwRetVal;

	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
		ch_AdapterName = "Error, cannot get AdaptersInfo"; //error
	}

	PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
	while (pAdapter) {

		ch_AdapterName += pAdapter->Description;//get title 
		ch_AdapterName += "\n";//next line
		pAdapter = pAdapter->Next;//get a next adapter
	}

	if (pAdapterInfo)
		free(pAdapterInfo);//release memory
}

/// <summary>
/// Gets the IP address using a external website.
/// Use a WINAPI solution.
/// </summary>
void NetParameter::getIpAddress()
{
	HINTERNET net = InternetOpen("IP retriever",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	HINTERNET conn = InternetOpenUrl(net,
		IPADDRESS_WEBSITE,
		NULL,
		0,
		INTERNET_FLAG_RELOAD,
		0);

	char buffer[4096];
	DWORD read;

	InternetReadFile(conn, buffer, sizeof(buffer) / sizeof(buffer[0]), &read);//read HTML code 
	InternetCloseHandle(net);

	ch_IpAddress = std::string(buffer, read);
}
