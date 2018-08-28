#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

DWORD pId;

int main()
{
	HWND hWnd = FindWindowA(NULL, ("AssaultCube"));

	GetWindowThreadProcessId(hWnd, &pId);

	HANDLE procH = OpenProcess(PROCESS_ALL_ACCESS, NULL, pId);//

	DWORD pLocalPlayer = 0x509B74;  //local player pointer
	DWORD playerObjectAddress = 0x0;			//local player address
	DWORD health = 0x0;            //health address
	DWORD yCor = 0x0;
	int healthValue = 999;        //health value 
	int fly = 15;

	cout << "Procid: " << pId << endl;

	ReadProcessMemory(procH, (LPCVOID)pLocalPlayer, &playerObjectAddress, sizeof(health), NULL); //scans for our local player address or player object address
	health = playerObjectAddress + 0xF8;
	/*
	ReadProcessMemory(procH, (LPCVOID)health, &healthValue, sizeof(healthValue), NULL);   //read health address and store results in healthValue
	std::cout << "your health is: " << healthValue << endl;;
	healthValue = 1200;*/
	yCor = playerObjectAddress + 0x3C;

	while (1)
	{
		WriteProcessMemory(procH, (LPVOID)yCor, &fly, sizeof(fly), NULL);
		WriteProcessMemory(procH, (LPVOID)health, &healthValue, sizeof(healthValue), NULL);
	}
	system("Pause");
}