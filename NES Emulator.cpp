
#include <iostream>
#include "CPU.h"
#include "MemMap.h"

using namespace std;

static MemMap* mem = new MemMap; // creates mem on heap

int main()
{
	CPU cpu;

	cpu.debug_printStatus();

	delete mem;
}
