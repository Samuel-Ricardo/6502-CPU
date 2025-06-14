#pragma once
#include "./register/16bits.h"
#include "./register/8bits.h"

struct Registers : public Registers8BIts, public Register16btis {};
