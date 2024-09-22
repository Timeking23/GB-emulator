#include "DMGCPU.h"



DMGCPU::DMGCPU()
{
    using a = DMGCPU;
	
	lookup = 
	{
		{"NOP", &a::NOP, 4},{"LD BC,u16", &a::LD_BC_u16, 12},{"LD (BC),A", &a::LD_BC_A, 8},{"BC", &a::BC, 8},
		{"INC B", &a::INC_B, 4},{"DEC B", &a::DEC_B, 4},{"LD B,u8", &a::LD_B_u8, 8},{"RLCA", &a::RLCA, 4},
        {},{},{},{},
        {},{},{},{},
        {}



    };
};
DMGCPU::~DMGCPU()
{
    //not needed for now
};

uint8_t DMGCPU::read(uint16_t a)
{
	// In normal operation "read only" is set to false. This may seem odd. Some
	// devices on the bus may change state when they are read from, and this 
	// is intentional under normal circumstances. However the disassembler will
	// want to read the data at an address without changing the state of the
	// devices on the bus
	return bus->read(a, false);
}

// Writes a byte to the bus at the specified address
void DMGCPU::write(uint16_t a, uint8_t d)
{
	bus->write(a, d);
}

void DMGCPU::reset()
{}

void DMGCPU::nmi()
{}

void DMGCPU::clock()
{}

uint8_t DMGCPU::GetFlag(ALUFlag f)
{}

void DMGCPU::SetFlag(ALUFlag f, bool v)
{}
