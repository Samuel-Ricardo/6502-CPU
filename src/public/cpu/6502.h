#pragma once
#include "../components/memory.h"

#include "./instructions.h"
#include "./logger.h"
#include "flags.h"
#include "registers.h"

#include <stdio.h>

struct CPU : virtual public Flags,
             virtual public Registers,
             public INSTRUCTION,
             public Logger {

  void Reset(Memory &memory) {
    PC = 0xFFFC;
    SP = 0x0100;

    resetFlags();
    memory.initialize();
  }

  Byte FetchByte(uint32_t &Cycles, Memory &memory) {
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
  }

  Word FetchWord(uint32_t &Cycles, Memory &memory) {
    Word Data = memory[PC];
    PC++;
    Data |= (memory[PC] << 8);
    PC++;
    Cycles -= 2;
    return Data;
  }
};
