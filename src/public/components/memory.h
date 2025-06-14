#include "../global.h"
#include <cstdint>

struct Memory {

  static constexpr uint32_t MAX_MEM = 1024 * 64;
  Byte Data[MAX_MEM];

  void initialize() {
    for (uint32_t i = 0; i < MAX_MEM; i++) {
      Data[i] = 0;
    }
  }

  Byte operator[](uint32_t index) const { return Data[index]; }

  Byte &operator[](uint32_t index) { return Data[index]; }

  void WriteWord(Word Value, uint32_t Address, uint32_t &Cycles) {
    Data[Address] = Value & 0xFF;
    Data[Address + 1] = (Value >> 8) & 0xFF;
    Cycles -= 2;
  }
};
