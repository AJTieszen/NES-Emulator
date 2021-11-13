
#include <iostream>
using namespace std;

class CPU {
private:
	uint8_t a = 0, x = 0, y = 0, s = 0, sp = 0;	// Accumulator, X Index, Y Index, Status (flags), Stack Pointer
	uint16_t pc = 0;			// Program Counter
	int clock = 0;

	const int CARRY = 0, ZERO = 1, INTERRUPT = 2, DECIMAL = 3, BREAK = 4, UNUSED = 5, OVER = 6, NEGATIVE = 7; // flag bits

	// Intrernal Functions
	void setFlag (int bit) {
		s = s | 1 << bit;
	}

	void clearFlag(int bit) {
		s = s & (0xff - 1 << bit);
	}

public:
	void debug() {
		printf("A: %02x, X: %02x, Y: %02x, S: %02x, SP: %02x, PC: %0004x \n Clock Cycle: %d \n", a, x, y, s, sp, pc, clock);
	}

	// Immediate Mode Instructions:
	void adc_imm(uint8_t value) {	// Opcode 69
		// detect carry
		if (a + value > 0xff) setFlag(CARRY);

		// add value
		a += value;

		// Update cycle and PC
		clock += 2;
		pc += 2;
	}

	void and_imm(uint8_t value) {	// Opcode 29
		a = a & value;

		// Update cycle and PC
		clock += 2;
		pc += 2;
	}

	void cmp_imm(uint8_t value) { // Opcode c9
		if (a < value) {
			clearFlag(ZERO);
			clearFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}
		if (a = value) {
			clearFlag(NEGATIVE);
			setFlag(ZERO);
			setFlag(CARRY);
		}
		if (a > value) {
			clearFlag(ZERO);
			setFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}

		// Update cycle and PC
		clock += 2;
		pc += 2;
	}

	void cpx_imm(uint8_t value) { // Opcode c9
		if (x < value) {
			clearFlag(ZERO);
			clearFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}
		if (x = value) {
			clearFlag(NEGATIVE);
			setFlag(ZERO);
			setFlag(CARRY);
		}
		if (x > value) {
			clearFlag(ZERO);
			setFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}

		// Update cycle and PC
		clock += 2;
		pc += 2;
	}

	void cpy_imm(uint8_t value) { // Opcode c9
		if (y < value) {
			clearFlag(ZERO);
			clearFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}
		if (y = value) {
			clearFlag(NEGATIVE);
			setFlag(ZERO);
			setFlag(CARRY);
		}
		if (y > value) {
			clearFlag(ZERO);
			setFlag(CARRY);

			if ((a - value) > 0b01111111) setFlag(NEGATIVE);
			else clearFlag(NEGATIVE);
		}

		// Update cycle and PC
		clock += 2;
		pc += 2;
	}

	// Accumulator Mode Instructions

	void asl_acc() { // Opcode 0a
		// detect carry
		if (a << 1 > 0xff) setFlag(CARRY);

		// shift a
		a = a << 1;

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}

	// Implied Mode Instructions
	void clc_imp() { // Opcode 18
		clearFlag(CARRY);

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}

	void cli_imp() { // Opcode 58
		// Clear
		clearFlag(INTERRUPT);

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}
};

int main()
{
	CPU cpu;
}
