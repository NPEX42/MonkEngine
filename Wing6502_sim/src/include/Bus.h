#pragma once
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include "stdio.h"

#include "olc6502.h"
#include "TTY.h"

class Bus
{
public:
	Bus();
	~Bus();

public: // Devices on bus
	olc6502 cpu;

	Terminal terminal;

	// Fake RAM for this part of the series
	std::vector<uint8_t> ram;


public: // Bus Read & Write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);

	void LoadRom(uint16_t nOffset, const char* file);
};

