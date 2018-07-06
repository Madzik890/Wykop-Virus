#include <Windows.h>
#include <stdio.h>
#include "WykopSDK.h"
#include "Information.hpp"
#include "Timer.hpp"
#include <fstream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

const LPCSTR g_ClassName = "Wykop Class";
MSG g_Msg;//global instance of event object

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);
	
	Information::createParameteres();

	UINT TimerSend = SetTimer(NULL, 1, getTimerTickHour(1), &TimerProcSender);

	while (1)
	{
		if (PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_Msg);
			DispatchMessage(&g_Msg);
		}
		Sleep(1);
	}

	KillTimer(NULL, 1);
	Information::clearParameteres();
	return g_Msg.wParam;
}

//events handling
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}