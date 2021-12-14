
#include <iostream>
#include "CPU.h"
#include "MemMap.h"

using namespace std;

int main()
{
	CPU cpu;
	MemMap* mem = new MemMap; // creates mem on heap

	cpu.debug_printStatus();
}
