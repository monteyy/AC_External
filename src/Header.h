#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <gdiplus.h>
#include <math.h>
#include <iostream>
#include <TlHelp32.h>
using namespace std;

namespace memory {
	DWORD GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
	{
		DWORD modBaseAddr = 0;
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 modEntry;
			modEntry.dwSize = sizeof(modEntry);

			if (Module32First(hSnap, &modEntry))
			{
				do
				{
					if (!_wcsicmp(modEntry.szModule, modName))
					{
						modBaseAddr = (DWORD)modEntry.modBaseAddr;

						break;
					}
				} while (Module32Next(hSnap, &modEntry));
			}
		}

		CloseHandle(hSnap);
		return modBaseAddr;
	}

	void Write(HANDLE hProc, int newValue, uintptr_t R_muniaddr) {
		if (WriteProcessMemory(hProc, (LPVOID)R_muniaddr, &newValue, sizeof(newValue), nullptr)) {
			std::cout << "[\033[1;32m+\033[0m] New ammo value: " << newValue << "\n";
		}
		else {
			std::cout << "[\033[1;31m+\033[0m] Error while writing.";
		}
		Sleep(2222);
	}
	

		void Read(HANDLE hProc, uintptr_t addr, int buffer) {
			if (ReadProcessMemory(hProc, (LPVOID)addr, &buffer, sizeof(buffer), nullptr)) {
				std::cout << "[\033[1;32m+\033[0m] Memory read: " << buffer << "\n";
			}
			else {
				std::cout << "[\033[1;31m+\033[0m] Error while reading memory." << "\n";
			}
		}
}
