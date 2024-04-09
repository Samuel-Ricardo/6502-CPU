#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

using Byte = unsigned char;
using Word = unsigned short;

struct Mem {

  // 64 KB //
  static constexpr uint32_t MAX_MEM = 1024 * 64;
  Byte Data[MAX_MEM];

  void initialize() {
    for (uint32_t i = 0; i < MAX_MEM; i++) {
      Data[i] = 0;
    }
  }

  // INFO: READ 1 BYTE //
  Byte operator[](uint32_t index) const { return Data[index]; }

  // INFO: WRITE 1 BYTE //
  Byte &operator[](uint32_t index) { return Data[index]; }
};

struct CPU {

  /* Program Counter - [16 bytes register] *
   *
   * Point to the Next Instruction to be executed
   *
   * Stack Pointer - [8 bytes register] *
   *
   * Point to the top of the stack, Fixed 256 bytes
   * No verify stack overfow, so if it happens may cause a program crash
   *
   *
   * Accumulator - [8 bytes register] *
   *
   * Used for all arithmetic and logical operations
   * Except by increment and decrement
   *
   * Your content can be stored and retrieved from memory or stack
   *
   * Index Register X - [8 bytes register] *
   *
   * Commonly Used to hold counters or offsets of
   * accessing memory, can be used to get a copy of
   * the stack pointer or change its value
   *
   * Index Register Y - [8 bytes register] *
   *
   * Commonly Used to hold counters or offsets of
   * accessing memory, can be used to get a copy of
   * the stack pointer or change its value
   *
   * Supprts set of memory load, save and compare
   * operations as wells as increments and decrements
   */

  // Program Counter
  Word PC;

  // Stack Pointer
  Word SP;

  // Acumulator & X & Y Index Registers
  Byte A, X, Y;

  /*
   * Processor Status *
   *
   * One Byte Flag that represents the state of the processor
   */
  Byte C : 1; // Carry Flag
  Byte Z : 1; // Zero Flag
  Byte I : 1; // Interrupt Disable
  Byte D : 1; // Decimal Mode
  Byte B : 1; // Break Command
  Byte V : 1; // Overflow Flag
  Byte N : 1; // Negative Flag

  void Reset(Mem &memory) {

    PC = 0xFFFC;
    SP = 0x0100;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;

    memory.initialize();
  }

  Byte FetchByte(uint32_t &Cycles, Mem &memory) {
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
  }

  // NOTE: OPCODES

  // NOTE: INSTRUCIONT LOAD ACCUMULATOR IMMEDIATLY
  static constexpr Byte INS_LDA_IM = 0xA9;

  void Execute(uint32_t Cycles, Mem &memory) {
    while (Cycles > 0) {
      Byte Instruction = FetchByte(Cycles, memory);

      switch (Instruction) {

      case INS_LDA_IM: {
        Byte Value = FetchByte(Cycles, memory);

        A = Value;
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
      } break;

      default: {
        printf("Instruction not implemented or handled: 0x%X\n", Instruction);
      } break;
      }
    };
  };
};

int main() {

  Mem mem;
  CPU cpu;
  cpu.Reset(mem);

  std::cout << "Hello, World! :D" << std::endl;
  return 0;
}
