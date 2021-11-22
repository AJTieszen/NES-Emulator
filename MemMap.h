#pragma once

class MemMap {
private:
	uint8_t ram [0x0800]; // 2k RAM
	uint8_t ppu [0x0008]; // PPU (video chip) control registers
	uint8_t apu [0x0020]; // APU (sound chip) and IO registers
	uint8_t crt [0xbfe0]; // Cartridge ROM, RAM, and memory mappers

public:
	uint8_t readMem(uint16_t addr) {
		if (addr <= 0x0fff) return ram[addr % 0x0800];
		else if (addr <= 0x3fff) return ppu[(addr - 0x2000) % 0x0008];
		else if (addr <= 0x401f) return apu[addr - 0x4000];
		//else return crt[addr - 0x4020];
	}

	void writeMem(uint16_t addr, uint8_t value) {
		if (addr <= 0x0fff) ram[addr % 0x0800] = value;
		else if (addr <= 0x3fff) ppu[(addr - 0x2000) % 0x0008] = value;
		else if (addr <= 0x401f) apu[addr - 0x4000] = value;
		//else crt[addr - 0x4020] = value;
	}
};