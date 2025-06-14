/*
  PROGRAM OVERVIEW:
  -----------------
  This program emulates a minimal 6502 CPU environment and executes a small
  inline program directly loaded into virtual memory ("cartridge").

  INSTRUCTION FLOW:
  -----------------
  1. The CPU is reset, initializing registers, flags, and memory.
     - PC is set to 0xFFFC (reset vector).
     - Stack Pointer (SP) is set to 0x0100.
     - All flags and registers are cleared.

  2. The cartridge (memory) is manually populated with a small program:
     - Address 0xFFFC: JSR (Jump to SubRoutine) instruction (opcode 0x20)
       - Jumps to subroutine located at address 0x4242.
     - Address 0xFFFD-0xFFFE: Low and high bytes of subroutine address (0x42,
  0x42)
     - Address 0x4242: LDA immediate instruction (opcode 0xA9)
       - Loads the value 0x84 into register A.
     - Address 0x4243: The immediate value 0x84.

  3. CPU execution begins with 9 cycles available.

  EXECUTION RESULT:
  -----------------
  - Instruction JSR consumes 6 cycles.
    - Pushes return address to the stack (SP = 0x00FE).
    - Jumps to address 0x4242.

  - Instruction LDA #$84 consumes 2 cycles.
    - Loads A = 0x84.
    - Updates flags:
      - Z (Zero) = 0 (since A ≠ 0)
      - N (Negative) = 1 (since highest bit of A is 1)

  - After execution:
    - Register A = 0x84
    - PC = 0x4244 (next instruction)
    - SP = 0x00FE
    - Flags reflect correct result.

  NOTES:
  ------
  - Only 8 cycles are consumed; remaining cycle leads to fetch of 0x00
  (undefined instruction).
  - To avoid “Instruction not implemented” error, use exact cycle count or
  insert a halt (e.g., BRK).
*/

#include "../../src/public/main.h"
#include <cstdio>

int main() {

  Memory cartridge;
  CPU cpu;

  cpu.Reset(cartridge);

  cpu.LogState();

  // INFO: Start a inline program || Machine Code [Virtual] || Cartridge||
  cartridge[0xFFFC] = CPU::INS_JSR;
  cartridge[0xFFFD] = 0x42;
  cartridge[0xFFFE] = 0x42;
  cartridge[0x4242] = CPU::INS_LDA_IM;
  cartridge[0x4243] = 0x84;
  // INFO: End a inline little program

  cpu.Execute(8, cartridge);

  printf("\n");
  cpu.LogState();

  return 0;
}
