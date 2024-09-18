//  Main RAM: 8K Byte
//  Video RAM: 8K(8192) Byte
//  Resolution: 160x144 (20x18 tiles)
//  Max # of Sprites: 40
//  Max # of Sprites/line: 10
//  Clock speed: 4.194304 MHz
#include <cstdint>

struct DMGCPU
{
public:
    DMGCPU();
    ~DMGCPU();
public:
    enum ALUFlag : uint8_t //(Arithmetic Logic Unit) part of Register F
    {//flag = (1 byte, 7th position) pos stars with 0-7, to make 8bytes ex.below
        z = (1 << 7), //Zero flag          [7-bits] 0b10000000 
        n = (1 << 6), //Subtraction flah   [6-bits] 0b01000000
        h = (1 << 5), //Half Carry flag    [5-bits] 0b00100000
        c = (1 << 4) //Carry flag          [4-bits] 0b00010000
    };
    //Contains information about the result of the most recent instruction
    //that has affected flags.

};
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

private:
    Bus     *bus = nullptr;
    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);
};
//As shown above, most registers can be accessed 
//either as one 16-bit register, or as two separate 8-bit registers.

enum ALUFlag : uint8_t //(Arithmetic Logic Unit) part of Register F
{//flag = (1 byte, 7th position) pos stars with 0-7, to make 8bytes ex.below
    z = (1 << 7), //Zero flag          [7-bits] 0b10000000 
    n = (1 << 6), //Subtraction flah   [6-bits] 0b01000000
    h = (1 << 5), //Half Carry flag    [5-bits] 0b00100000
    c = (1 << 4) //Carry flag          [4-bits] 0b00010000
};
//Contains information about the result of the most recent instruction
//that has affected flags.


