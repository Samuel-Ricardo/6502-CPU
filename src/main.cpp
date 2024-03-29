#include <iostream>

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

  using Byte = unsigned char;
  using Word = unsigned short;

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
};

int main() {
  std::cout << "Hello, World! :D" << std::endl;
  return 0;
}
