#pragma once
#include "../global.h"
#include "flags.h"

struct INSTRUCTION : virtual public Flags {
  // NOTE: LOAD ACCUMULATOR IMEDIATE
  static constexpr Byte INS_LDA_IM = 0xA9;
  // NOTE: LOAD ACCUMULATOR ZERO PAGE
  static constexpr Byte INS_LDA_ZP = 0xA5;
  // NOTE: LOAD ACCUMULATOR ZERO PAGE, X
  static constexpr Byte INS_LDA_ZPX = 0xB5;
  // NOTE: JUMP SUBROUTINE
  static constexpr Byte INS_JSR = 0x20;

  void LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
  }
};
