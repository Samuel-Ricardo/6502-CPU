#pragma once
#include "../global.h"

struct Flags {
  Byte A, X, Y;

  Byte C : 1;
  Byte Z : 1;
  Byte I : 1;
  Byte D : 1;
  Byte B : 1;
  Byte V : 1;
  Byte N : 1;
};
