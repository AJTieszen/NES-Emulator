
#include <iostream>
#include "CPU.h"
#include "MemMap.h"

using namespace std;

int main()
{
	CPU cpu;
	MemMap& mem = MemMap::getInstance();
	mem.write(3, 'e');

	cpu.debug_printStatus();
}
