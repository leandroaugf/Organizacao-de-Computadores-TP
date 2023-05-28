#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

void start(Machine* machine, Instruction* instructions, int RAMSize) {
    machine->instructions = instructions;
    machine->RAM.items = (float*) malloc(sizeof(float) * RAMSize);
    machine->RAM.size = RAMSize;
    for (int i=0;i<RAMSize;i++)
        machine->RAM.items[i] = rand()%10;
}

void stop(Machine* machine) {
    free(machine->instructions);
    free(machine->RAM.items);
}

float soma(float a, float b){

    float result;
    result = a + b;
    return result;

}

float sub(float a, float b){

    float result;
    result = a-+ b;
    return result;
}

float multi(float a, float b){

    float result = 0;
    int confere_negativo = 0;

    if((a < 0 && b > 0) || (a > 0 && b < 0)){
        confere_negativo = 1;
    }

    if(a < 0){
        a = -a;
    }

    if(b < 0){
        b = -b;
    }

    for(int i = 0; i < b; i++){
        result += a;
    }

    if(confere_negativo){
        result = -result;
    }

    return result;
}

float divi(float a, float b){   //a = dividendo  b = divisor

    float result = 0;
    int aux_divisao = b;
    int confere_negativo = 0;

    if((a < 0 && b > 0) || (a > 0 && b < 0)){
        confere_negativo = 1;
    }

    if(a < 0){
        a = -a;
    }

    if(b < 0){
        b = -b;
    }

    while(a >= b){
        b += aux_divisao;
        result++;
    }

    if(confere_negativo){
        result = - result;
    }

    return result;

}



void run(Machine* machine) {
    // Registradores
    int PC = 0; // Program Counter - Contador de programa
    int opcode = 0;
    int address1;
    int address2;
    float value;
    float result;
    float RAMContent1;
    float RAMContent2;
    int address3;
    while(opcode != -1) {
        Instruction instruction = machine->instructions[PC];
        opcode = instruction.opcode;
        switch (opcode) {
            case -1:
                printf("  > Finalizando a execucao.\n");
                break;
            case 0: // Levando informação para a RAM
                value = (float) instruction.info1;
                address1 = instruction.info2;
                machine->RAM.items[address1] = value;
                printf("  > Levando informacao (%f) para a RAM[%d].\n", value, address1);
                break;
            case 1: // Somando
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = soma(RAMContent1, RAMContent2);
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 2: // Subtraindo
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = sub(RAMContent1, RAMContent2);
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 3: // Multiplicando
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = multi(RAMContent1, RAMContent2);
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Multiplicando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 4:  // Dividindo
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = divi(RAMContent1, RAMContent2);
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Dividindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

        }
        PC++;
    }
}

void printRAM(Machine* machine) {
    printf("  > RAM");
    for (int i=0;i<machine->RAM.size;i++)
        printf("\t\t[%5d] : %f\n", i, machine->RAM.items[i]);
}
