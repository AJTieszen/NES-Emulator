
#include <iostream>
using namespace std;

class CPU {
private:
	uint8_t a, x, y, s, sp;	// Accumulator, X Index, Y Index, Status (flags), Stack Pointer
	uint16_t pc;			// Program Counter

public:
	void debug() {
		printf("A: %02x, X: %02x, Y: %02x, S: %02x, SP: %02x, PC: %0004x", a, x, y, s, sp, pc);
	}
};

int main()
{
	CPU cpu;

	cpu.debug();
}
