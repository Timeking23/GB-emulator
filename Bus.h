#pragma once
#include <cstdint>
#include <array>
#include "DMGCPU.h"
#include <iostream>
using namespace std;

class Bus
{
public:
	Bus();
	~Bus();

public: // Devices on bus
	DMGCPU cpu;	//DMGCPU
	array<uint8_t, 64 * 1024> ram; //64KB of ram


public: // Bus Read & Write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};
