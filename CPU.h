#pragma once
#include "MemMap.h"

class CPU {
private:
	// Registers
	uint8_t a = 0, x = 0, y = 0, s = 0, sp = 0;	// Accumulator, X Index, Y Index, Status (flags), Stack Pointer
	uint16_t pc = 0;							// Program Counter

	// Memory Access
	MemMap& mem = MemMap::getInstance();

	// Will be used to synchronize with other components
	unsigned int clock = 0;

	const int CARRY = 0, ZERO = 1, INTERRUPT = 2, DECIMAL = 3, BREAK = 4, UNUSED = 5, OVER = 6, NEGATIVE = 7; // flag bits

	// Intrernal Functions
	void setFlag(int bit) {
		s = s | 1 << bit;
	}

	void clearFlag(int bit) {
		s = s & (0xff - (1 << bit));
	}

	int readFlag(int bit) {
		if ((s & (1 << bit)) != 0) return 1;
		else return 0;
	}

public:
	void debug_printStatus() {
		printf("A: %02x, X: %02x, Y: %02x, S: %02x, SP: %02x, PC: %0004x \n Clock Cycle: %d \n", a, x, y, s, sp, pc, clock);
		std::cout << mem.read(3) << "\n";
	}

	// Memory Instructions:
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

	void eor_imm(uint8_t value) { // Opcode 49
		a = a ^ value;

		pc += 2;
		clock += 2;
	}

	void lda_imm(uint8_t value) { // Opcode a9
		a = value;

		pc += 2;
		clock += 2;
	}

	void ldx_imm(uint8_t value) { // Opcode a2
		x = value;

		pc += 2;
		clock += 2;
	}

	void ldy_imm(uint8_t value) { // Opcode a0
		y = value;

		pc += 2;
		clock += 2;
	}

	void ora_imm(uint8_t value) { // Opcode 09
		a = a | value;

		pc += 2;
		clock += 2;
	}

	void sbc_imm(uint8_t value) { // Opcode e9
		if (a - value < 0) clearFlag(CARRY);
		else setFlag(CARRY);

		a -= value;

		pc += 2;
		clock += 2;
	}

	// Accumulator Instructions

	void asl_acc() { // Opcode 0a
		// detect carry
		if (a << 1 > 0xff) setFlag(CARRY);

		// shift a
		a = a << 1;

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}

	void lsr_acc() { // opcode 4a
		if ((a & 0b00000001) == 1) setFlag(CARRY);

		a = a >> 1;

		pc++;
		clock += 2;
	}

	void rol_acc() { // Opcode 2a
		if (a > 0b01111111) setFlag(CARRY);
		else clearFlag(CARRY);

		a = a << 1 | readFlag(CARRY);
	}

	void ror_acc() { // Opcode 6a
		if (a % 2 == 1) setFlag(CARRY);
		else clearFlag(CARRY);

		a = (a >> 1) | readFlag(CARRY) << 7;

		pc++;
		clock += 2;
	}

	// Register Instructions
	void clc_reg() { // Opcode 18
		clearFlag(CARRY);

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}

	void cli_reg() { // Opcode 58
		// Clear
		clearFlag(INTERRUPT);

		// Update cycle and PC
		clock += 2;
		pc += 1;
	}

	void dex_reg() { // Opcode ca
		x--;

		pc++;
		clock += 2;
	}

	void dey_reg() { // Opcode ca
		y--;

		pc++;
		clock += 2;
	}

	void inx_reg() { // Opcode e8
		x++;

		pc++;
		clock += 2;
	}

	void iny_reg() { // Opcode c8
		y++;

		pc++;
		clock += 2;
	}

	void nop_reg() { // Opcode ea
		pc++;
		clock += 2;
	}

	void sec_reg() { // Opcode 38
		setFlag(CARRY);

		pc++;
		clock += 2;
	}

	void sei_reg() { // Opcode 38
		setFlag(INTERRUPT);

		pc++;
		clock += 2;
	}

	void tax_reg() { // Opcode aa
		x = a;

		pc++;
		clock += 2;
	}

	void tay_reg() { // Opcode a8
		y = a;

		pc++;
		clock += 2;
	}

	void tsx_reg() { // Opcode ba
		x = s;

		pc++;
		clock += 2;
	}

	void txa_reg() { // Opcode 8a
		a = x;

		pc++;
		clock += 2;
	}

	void txs_reg() { // Opcode 9a
		s = x;

		pc++;
		clock += 2;
	}

	void tya_reg() { // Opcode 98
		a = y;

		pc++;
		clock += 2;
	}
};