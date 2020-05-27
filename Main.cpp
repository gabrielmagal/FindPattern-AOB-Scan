#include <Windows.h>
#include <iostream>


DWORD FindPatternStartAddress(const char pattern[], const char mask[], DWORD startAddress, DWORD endAddress) {
	UINT Found = NULL;
	for (int i = 0; i < (endAddress - startAddress); i++) {
		if (*(BYTE*)(startAddress + i) == pattern[Found] || mask[Found] == '?') {
			if (mask[Found+1] == '\0')
				return ((startAddress + i) - (strlen(mask) - 1));
			Found++;
		}
		else
			Found = NULL;
	}
	return 0;
}


DWORD FindPatternStartAddressPos(const char pattern[], const char mask[], DWORD startAddress, DWORD endAddress, UINT posScan) {
	UINT AddList = 0;
	UINT Found = NULL;
	for (int i = 0; i < (endAddress - startAddress); i++) {
		if (*(BYTE*)(startAddress + i) == pattern[Found] || mask[Found] == '?')  {
			if (mask[Found + 1] == '\0') {
				if (AddList == (posScan - 1))
					return (startAddress + i) - (strlen(mask) - 1);
				AddList++;
				Found = NULL;
			}
			else
				Found++;
		}
		else
			Found = NULL;
	}
	return 0;
}


void Test()
{
	FindPatternStartAddress("\x44\x33\x44\x39", "xxxx", 0x00400000, 0x00500000); // Primeiro valor da lista
	FindPatternStartAddressPos("\x44\x33\x44\x39", "xxxx", 0x00400000, 0x00500000, 1); // O ultimo valor é a posição em que o Scan vai encontrar
}
