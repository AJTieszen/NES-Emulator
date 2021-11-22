
#include <iostream>
#include "CPU.h"
#include "MemMap.h"

using namespace std;

int main()
{
	CPU cpu;
	MemMap mem;

	cpu.debug_printStatus();
}
