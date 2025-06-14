#include "../public/main.h"
#include <iostream>

int main() {
  Memory mem;
  CPU cpu;
  cpu.Reset(mem);

  // INFO: Start a inline program || Machine Code [Virtual] || Cartridge ||

  // Exemplos alternativos (comentados):
  // mem[0xFFFC] = CPU::INS_LDA_IM;
  // mem[0xFFFD] = 0x42;

  // mem[0xFFFC] = CPU::INS_LDA_ZP;
  // mem[0xFFFD] = 0x42;
  // mem[0x0042] = 0x84;

  // INFO: Inline subroutine
  mem[0xFFFC] = CPU::INS_JSR;
  mem[0xFFFD] = 0x42;
  mem[0xFFFE] = 0x42;
  mem[0x4242] = CPU::INS_LDA_IM;
  mem[0x4243] = 0x84;

  cpu.LogState();
  cpu.Execute(9, mem);
  cpu.LogState();

  std::cout << "Hello, World! :D" << std::endl;
  return 0;
}
