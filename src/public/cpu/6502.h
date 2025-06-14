#pragma once
#include "../components/memory.h"

#include "./instructions.h"
#include "./logger.h"
#include "flags.h"
#include "registers.h"

#include <stdio.h>

struct CPU : virtual public Flags,
             virtual public Registers,
             public INSTRUCTION,
             public Logger {};
