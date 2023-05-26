#include "cpu.h"
#include "ops.c"
#include "ops.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void start(Machine* machine, Instruction* instructions, int RAMSize) {
    machine->instructions = instructions;
    machine->RAM.items = (float*) malloc(sizeof(float) * RAMSize);
    machine->RAM.size = RAMSize;
    for (int i=0;i<RAMSize;i++)
        machine->RAM.items[i] = (float)rand() / RAND_MAX;
}

void stop(Machine* machine) {
    free(machine->instructions);
    free(machine->RAM.items);
}

void run(Machine* machine) { //                                                                                                   [FUNCAO ONDE O TUDO EH EXECUTADO]
    
    int opcode = 0;
    int PC = 0; // Program Counter - Contador de programa
    int address1;
    int address2;
    int address3;
    float raizes[15] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225};

    float value;
    float result;
    float RAMContent1;
    float RAMContent2;
    srand(time(NULL));

    while(opcode != -1) {
        Instruction instruction = machine->instructions[PC];
        opcode = instruction.opcode;
//      [ATRIBUICAO DOS VALORES AAS VARIAVEIS]
        address1 = instruction.info1;
        address2 = instruction.info2;
        address3 = instruction.info3;
        RAMContent1 = machine->RAM.items[address1];
        RAMContent2 = machine->RAM.items[address2];

        switch (opcode) {
            case -1:
                printf("  > Finalizando a execucao.\n");
                break;

            case 0: // [DONE]
                value = (float) instruction.info1;
                address1 = instruction.info2;
                machine->RAM.items[address1] = value;
                printf("  > Levando informacao (%f) para a RAM[%d].\n", value, address1);
                break;

            case 1: // [SOMA]
                result = soma(RAMContent1, RAMContent2);
                
                machine->RAM.items[address3] = result;
                printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 2: // [SUBTRACAO]
                result = sub(RAMContent1, RAMContent2);
                
                machine->RAM.items[address3] = result;
                printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", //
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 3: // multiplicando
                RAMContent1 = 36;
                RAMContent2 = rand() % 10 + 1;
                result = mult(RAMContent1, RAMContent2);
                machine->RAM.items[address3] = result;
                printf("  > Multiplicando RAM[%d] (%.2f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 4: // [DIVISAO]
                RAMContent1 = 36.0; 
                RAMContent2 = 9.0;
                result = div(RAMContent1, RAMContent2);
                machine->RAM.items[address3] = result;
                printf("  > Dividindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 5: // [FIBONACCI]
                RAMContent1 = rand() % 15 + 1;
                result = fibonacci(RAMContent1);
                machine->RAM.items[address3] = result;
                printf("  > Calculando a sequência de Fibonacci: RAM[%d] (%f) e salvando na RAM[%d] (%f).\n.",
                            address1, RAMContent1, address3, result);
                break;

            case 6: // [EXPONENCIAL]
                RAMContent1 = rand() % 20 + 1;
                RAMContent2 = rand() % 3 + 1;
                result = expo(RAMContent1, RAMContent2);
                machine->RAM.items[address3] = result;
                printf("  > Calculando o exponencial de RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address2, RAMContent2, address3, result);
                break; 

            case 7: // [FATORIAL]
                RAMContent1 = rand() % 10 + 1;
                result = fat(RAMContent1);
                machine->RAM.items[address3] = result;
                printf("  > Calculando o fatorial de RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address3, result);
                break;
            case 8: // [RAIZ]
                RAMContent1 = raizes[random() % 15 + 1];
                result = raiz(RAMContent1);
                machine->RAM.items[address3] = result;
                printf("  > Calculando a raiz quadrada de RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address3, result);
                break;
                // [MDC]
        }   
        PC++;
    }
}

void printRAM(Machine* machine) {
    printf("  > RAM");
    for (int i=0;i<machine->RAM.size;i++)
        printf("\t\t[%5d] : %f\n", i, machine->RAM.items[i]);
}