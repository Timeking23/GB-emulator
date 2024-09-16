//  Main RAM: 8K Byte
//  Video RAM: 8K Byte
//  Resolution: 160x144 (20x18 tiles)
//  Max # of Sprites: 40
//  Max # of Sprites/line: 10
//  Clock speed: 4.194304 MHz
#include <cstdint>


struct Registers
{
    uint8_t A; uint16_t BC;
    uint8_t B; uint16_t DE;
    uint8_t C; uint16_t HL;
    uint8_t D; uint16_t SP; //Stack Pointer
    uint8_t E; uint16_t AF; //
    uint8_t F; uint16_t PC; //Program Counter/Pointer
    uint8_t H;
    uint8_t L;
};  
//As shown above, most registers can be accessed 
//either as one 16-bit register, or as two separate 8-bit registers.

struct Flags // these are less than 8 bits fyi.
{
    uint8_t z; //Zero flag          [7-bits]
    uint8_t n; //Subtraction flah   [6-bits]
    uint8_t h; //Half Carry flag    [5-bits]
    uint8_t c; //Carry flag         [4-bits]
};
//Contains information about the result of the most recent instruction
//that has affected flags.


