#include "Bus.h"



Bus::Bus()
{
	ram.resize(65536);
	cpu.ConnectBus(this);

	// Clear RAM contents, just in case :P
	for (auto& i : ram) i = 0x00;
}


Bus::~Bus()
{
}

void Bus::write(uint16_t addr, uint8_t data)
{
	if ((addr >= 0x0000 && addr < 0xC000) || (addr >= 0xE000 && addr <= 0xFFFF))
		ram[addr] = data;
	else
		terminal.write(addr, data);
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly)
{
	if ((addr >= 0x0000 && addr < 0xC000) || (addr >= 0xE000 && addr <= 0xFFFF))
		return ram[addr];
	else
		return terminal.read(addr);
}

void Bus::LoadRom(uint16_t nOffset, const char* file)
{
	std::ifstream rom(file, std::ios::binary);

	if (rom.fail()) { printf("Failed To Open File\n");}

	rom >> std::noskipws;
	uint16_t resetVector = nOffset;
	int count = 0;
	printf("Loading ROM - '%s' ", file);
	
	for (int i = 0; i < ram.size(); i++) {
		ram[i] = 0;
	}

	while (!rom.eof())
	{
		rom >> ram[nOffset++];
		count += 1;

		if (count % 4 == 0) {
			printf(".");
		}
	}
	printf(" - Done\n");

	ram[RESET_ADDR_LOW] = resetVector & 0xFF;
	ram[RESET_ADDR_HI] = resetVector >> 8;

	
}
