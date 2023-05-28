#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateRandomInstructions(int);
Instruction* generateMultiplicationInstructions(int, int);
Instruction* readInstructions(char*, int*);
Instruction* menu();

#endif // !GENERATOR_H