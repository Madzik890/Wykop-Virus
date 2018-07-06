#pragma once
#include <Windows.h>
#include <thread>

#ifndef TIMER_HPP
#define TIMER_HPP

void CALLBACK TimerProcSender(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
UINT getTimerTickHour(UINT hour);

#endif