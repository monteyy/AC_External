#include <Windows.h>      
#include <TlHelp32.h>     
#include <iostream>
#include <cstring>
#include "Header.h"


int main()
{
	DWORD pid = 0;
	HWND hwnd = FindWindowA(nullptr, "AssaultCube");


	if (hwnd) std::cout << "[\033[1;32m+\033[0m] Window found" << "\n";
	else std::cout << "[\033[1;31m-\033[0m] Window not found" << "\n";

	GetWindowThreadProcessId(hwnd, &pid);

	uintptr_t moduleBase = memory::GetModuleBaseAddress(pid, L"ac_client.exe");

	if (!pid) std::cout << "[\033[1;31m-\033[0m] PID not found" << "\n";
	else std::cout << "[\033[1;32m+\033[0m] PID found: " << pid << "\n";
	Sleep(2222);
	system("cls");

	HANDLE hProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, FALSE, pid);



	int newAmmoValue;
	int newHPValue;
	int chc;

	uintptr_t AmmoOffset = 0x140;
	uintptr_t HPoffset = 0xEC;
	uintptr_t hpaddr = moduleBase + HPoffset;

	uintptr_t playerPointer;
	ReadProcessMemory(hProc, (LPCVOID)(moduleBase + 0x0017E0A8), &playerPointer, sizeof(playerPointer), nullptr);

	uintptr_t R_muniaddr = playerPointer + AmmoOffset;
	uintptr_t R_hpaddr = playerPointer + HPoffset;

	while (true) {
		system("cls");
		std::cout << "\033[1;32m1\033[0m. Ammo" << "\n";
		std::cout << "\033[1;32m2\033[0m. HP" << "\n";
		std::cout << "\n> ";
		std::cin >> chc;


		if (chc == 1) {
			int newAmmoValue;
			std::cout << "New ammo value \033[1;32m>\033[0m ";
			std::cin >> newAmmoValue;
			memory::Write(hProc, newAmmoValue, R_muniaddr);
		}
		else if (chc == 2) {
			std::cout << "New HP value \033[1;32m>\033[0m ";
			std::cin >> newHPValue;
			memory::Write(hProc, newHPValue, R_hpaddr);
		}
	}
	CloseHandle(hProc);
}
