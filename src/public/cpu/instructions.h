#pragma once
#include "../global.h"
#include "flags.h"

struct INSTRUCTION : virtual public Flags {
  static constexpr Byte INS_LDA_IM = 0xA9;
  static constexpr Byte INS_LDA_ZP = 0xA5;
  static constexpr Byte INS_LDA_ZPX = 0xB5;
  static constexpr Byte INS_JSR = 0x20;
};
