#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

using Byte = unsigned char;
using Word = unsigned short;

struct Memory {

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

  // INFO: WRITE 1 WORD | 2 BYTES //
  void WriteWord(Word Value, uint32_t Address, uint32_t Cycles) {
    Data[Address] = Value & 0xFF;
    Data[Address + 1] = (Value >> 8) & 0xFF;
    Cycles -= 2;
  }
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

  void Reset(Memory &memory) {

    PC = 0xFFFC;
    SP = 0x0100;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;

    memory.initialize();
  }

  Byte FetchByte(uint32_t &Cycles, Memory &memory) {
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
  }

  Word FetchWord(uint32_t &Cycles, Memory &memory) {

    // INFO: 6502 IS LITTLE ENDIAN
    Word Data = memory[PC];
    PC++;

    Data |= (memory[PC] << 8);
    PC++;

    Cycles -= 2;

    // INFO: IF YOU WANT TO HANDLE ENDIANNESS
    // YOU WOULD HAVE TO SWAP BYTES HERE
    // if ( PLATFORM_LITTLE_ENDIAN )
    // {
    //    SwapBytesInWord( Data );
    //    ?Data = (Data << 8) | (Data >> 8);?
    // }

    return Data;
  }

  Byte ReadByte(uint32_t &Cycles, Byte Address, Memory &memory) {
    Byte Data = memory[Address];
    Cycles--;
    return Data;
  }

  void LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
  }

  // INFO: OPCODES: ADDRESSING MODES

  // NOTE: INSTRUCIONT LOAD ACCUMULATOR IMMEDIATE
  static constexpr Byte INS_LDA_IM = 0xA9;

  // NOTE: INSTRUCTION LOAD ACCUMULATOR ZERO PAGE
  static constexpr Byte INS_LDA_ZP = 0xA5;

  // NOTE: INSTRUCTION LOAD ACCUMULATOR ZERO PAGE X
  static constexpr Byte INS_LDA_ZPX = 0xB5;

  // NOTE: INSTRUCTION JUMP TO SUBROUTINE
  static constexpr Byte INS_JSR = 0x20;

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
        Cycles--; // INFO: 4 Clocks

        A = ReadByte(Cycles, ZeroPageAddress, memory);
        LDASetStatus();
      } break;

      case INS_JSR: { // INFO: 6 Cycles / Clocks
        Word SubroutineAddress = FetchWord(Cycles, memory);

        // INFO: PUSH SUBROUTINE ADDRESS TO STACK
        SP -= 2;
        memory.WriteWord(PC - 1, SP, Cycles);

        PC = SubroutineAddress;
        Cycles--;

      } break;

      default: {
        printf("Instruction not implemented or handled: 0x%X\n", Instruction);
      } break;
      }
    };
  };

  void LogState() {

    printf("Register A: %02X\n", A);
    printf("Register X: %02X\n", X);
    printf("Register Y: %02X\n", Y);
    printf("Register C: %02X\n", C);
    printf("Register Z: %02X\n", Z);
    printf("Register I: %02X\n", I);
    printf("Register D: %02X\n", D);
    printf("Register B: %02X\n", B);
    printf("Register V: %02X\n", V);
    printf("Register N: %02X\n", N);

    printf("Program Counter: %04X\n", PC);
    printf("Stack Pointer: %04X\n", SP);
  }
};

int main() {

  Memory mem;
  CPU cpu;
  cpu.Reset(mem);

  // INFO: Start a inline program || Machine Code [Virtual] || Cartridge||

  //  mem[0xFFFC] = CPU::INS_LDA_IM;
  //  mem[0xFFFD] = 0x42;

  //  mem[0xFFFC] = CPU::INS_LDA_ZP; // Instruction
  //  mem[0xFFFD] = 0x42;            // Set Zero Page Address
  //  mem[0x0042] = 0x84;            // Set a Value in Zero Page Address

  // INFO: SECOND PHASE

  mem[0xFFFC] = CPU::INS_JSR;
  mem[0xFFFD] = 0x42;
  mem[0xFFFE] = 0x42;
  mem[0x4242] = CPU::INS_LDA_IM;
  mem[0x4243] = 0x84;

  // INFO: End a inline little program

  cpu.LogState();
  cpu.Execute(9, mem);
  cpu.LogState();

  std::cout << "Hello, World! :D" << std::endl;
  return 0;
}
