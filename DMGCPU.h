//  Main RAM: 8K Byte
//  Video RAM: 8K(8192) Byte
//  Resolution: 160x144 (20x18 tiles)
//  Max # of Sprites: 40
//  Max # of Sprites/line: 10
//  Clock speed: 4.194304 MHz
#pragma once
#include <cstdint>
#include "Bus.h"
#include <string>
#include <vector>

// Forward declaration of generic communications bus class to
// prevent circular inclusions
class Bus;
struct DMGCPU
{
public:
    DMGCPU();
    ~DMGCPU();
public:
    enum ALUFlag : uint8_t //(Arithmetic Logic Unit) part of Register F
    {//flag = (1 byte, 7th position) pos stars with 0-7, to make 8bytes ex.below
        z = (1 << 7), //Zero flag          [7-bits] 0b10000000 
        n = (1 << 6), //Subtraction flag  [6-bits] 0b01000000
        h = (1 << 5), //Half Carry flag    [5-bits] 0b00100000
        c = (1 << 4) //Carry flag          [4-bits] 0b00010000
    };
    //Contains information about the result of the most recent instruction
    //that has affected flags.

    void reset();     // Reset CPU state
    void irq();       // Interrupt Request
    void nmi();       // Non-Maskable Interrupt Request
    void clock();     // Execute one clock cycle
    bool complete();  // Check if current instruction is complete

    // Link this CPU to a communications bus
	void ConnectBus(Bus *n) { bus = n; }

public:
    struct Registers
    {
    uint8_t A = 0x00;   // Accumulator
    uint8_t F = 0x00;   // Flags
    uint16_t AF = 0x0000; // AF register pair

    uint8_t B = 0x00;
    uint8_t C = 0x00;
    uint16_t BC = 0x0000; // BC register pair

    uint8_t D = 0x00;
    uint8_t E = 0x00;
    uint16_t DE = 0x0000; // DE register pair

    uint8_t H = 0x00;
    uint8_t L = 0x00;
    uint16_t HL = 0x0000; // HL register pair

    uint16_t SP = 0x00; // Stack Pointer
    uint16_t PC = 0x00; // Program Counter/Pointer

    uint8_t status = 0x00;  // 0x00 reset to 0 aka initalize to 0 
    };
//As shown above, most registers can be accessed 
//either as one 16-bit register, or as two separate 8-bit registers.

private:
    uint8_t GetFlag(ALUFlag f);
    void SetFlag(ALUFlag f, bool v);
	
	// Assisstive variables to facilitate emulation
	uint8_t  fetched     = 0x00;   // Represents the working input value to the ALU
	uint16_t temp        = 0x0000; // A convenience variable used everywhere
	uint16_t addr_abs    = 0x0000; // All used memory addresses end up in here
	uint16_t addr_rel    = 0x00;   // Represents absolute address following a branch
	uint8_t  opcode      = 0x00;   // Is the instruction byte
	uint8_t  cycles      = 0;	   // Counts how many cycles the instruction has remaining
	uint32_t clock_count = 0;	   // A global accumulation of the number of clocks

	// Linkage to the communications bus
	Bus     *bus = nullptr;
	uint8_t read(uint16_t a);
	void    write(uint16_t a, uint8_t d);


    struct INSTRUCTION {
    std::string name;
    uint16_t (DMGCPU::*operate)(); // Pointer to the operation
    uint8_t cycles; // Number of cycles
    };

    	std::vector<INSTRUCTION> lookup;
    

private:
    // Opcodes ======================================================
    uint16_t NOP(); uint16_t LD_BC_u16(); uint16_t LD_BC_A(); uint16_t BC();
    uint16_t INC_B(); uint16_t DEC_B(); uint16_t LD_B_u8(); uint16_t RLCA();
    uint16_t RLA(); uint16_t JR0(); uint16_t RRA(); uint16_t DAA();
    uint16_t CPL(); uint16_t CFF(); uint16_t HAT(); uint16_t ADC();
    uint16_t SUB(); uint16_t SBC(); uint16_t AND(); uint16_t XOR();
    uint16_t OR0(); uint16_t CP0(); uint16_t RET(); uint16_t POP();
    uint16_t CAL(); uint16_t JP0(); uint16_t PUH(); uint16_t RST();
    uint16_t PRE(); uint16_t REI(); uint16_t DI0(); uint16_t EI0();

};
