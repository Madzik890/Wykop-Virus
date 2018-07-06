#include "KeyParameter.hpp"
#include <Windows.h>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

void KeyParameter::mainFunc()
{
	getLastEvent();
	//blinkKeyLed();
}

std::string KeyParameter::getInformation()
{
	std::string text;
	text += "\n [Parametry klawiatury] \n";
	text += "Liczba wcisnietych klawiszy: " + std::to_string(u_PressedKeys) + "\n";
	text += "[/Parametry klawiatury] \n";

	return text;
}

void KeyParameter::getLastEvent()
{
	unsigned int pressedkeys = 0;
	for (int i = 0; i < 256; i++)
	{
		if(GetKeyState(i) & 0x8000)
		{
			u_PressedKeys++;
		}
	}
	u_PressedKeys = pressedkeys;
}

void KeyParameter::blinkKeyLed()
{
	keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	// Simulate a key release
	keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);         // this turns num off

	//capslock
	keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	// Simulate a key release
	keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

	//scrolllock
	keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	// Simulate a key release
	keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

}
																											   