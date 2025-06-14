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

  Byte ReadByte(uint32_t &Cycles, Byte Address, Memory &memory) {
    Byte Data = memory[Address];
    Cycles--;
    return Data;
  }

  void Execute(uint32_t Cycles, Memory &memory) {
    while (Cycles > 0) {
      Byte Instruction = FetchByte(Cycles, memory);

      switch (Instruction) {

      case INS_LDA_IM: {
        Byte Value = FetchByte(Cycles, memory);
        A = Value;
        LDASetStatus();
      } break;

      case INS_LDA_ZP: {
        Byte ZeroPageAddress = FetchByte(Cycles, memory);
        A = ReadByte(Cycles, ZeroPageAddress, memory);
        LDASetStatus();
      } break;

      case INS_LDA_ZPX: {
        Byte ZeroPageAddress = FetchByte(Cycles, memory);
        ZeroPageAddress += X;
        Cycles--;
        A = ReadByte(Cycles, ZeroPageAddress, memory);
        LDASetStatus();
      } break;

      case INS_JSR: {
        Word SubroutineAddress = FetchWord(Cycles, memory);
        SP -= 2;
        memory.WriteWord(PC - 1, SP, Cycles);
        PC = SubroutineAddress;
        Cycles--;
      } break;

      default: {
        printf("Instruction not implemented or handled: 0x%X\n", Instruction);
      } break;
      }
    }
  }
};
