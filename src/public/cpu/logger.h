#pragma once
#include <stdio.h>

#include "flags.h"
#include "registers.h"

struct Logger : virtual public Registers, virtual public Flags {
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
