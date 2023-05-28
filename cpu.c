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

float mult(float RAMContent1, float RAMContent2){
    int flag = 0;
    float result = 0;

    if(RAMContent1 < 0) {
        RAMContent1 = -RAMContent1;
        flag++;
    }
    if (RAMContent2 < 0) {
        RAMContent2 = -RAMContent2;
        flag++;
    }

    for (int i = 0; i < RAMContent2; i++) 
        result += RAMContent1;
    if(flag == 1) 
        result = -result;

    return result;
}

float divis(float RAMContent1, float RAMContent2) {
  int flag = 0;
  float result = 0;
  if(RAMContent1 < 0) {
    RAMContent1 = -RAMContent1;
    flag++;
  }
  if(RAMContent2 < 0) {
    RAMContent2 = -RAMContent2;
    flag++;
  }
  int aux = RAMContent2;
  while(RAMContent1 >= RAMContent2) { 
    RAMContent2 += aux;
    result++;
  }
  if (flag == 1)
    result = -result;

  return result;
}

float fibonacci(int num) {
    if(num == 0)
        return 0; 
    if(num == 1)
        return 1;
    
    return fibonacci(num - 1) + fibonacci(num - 2);
}

float exponencial(float RAMContent1, float RAMContent2) {
    float aux = RAMContent1;
    float result = RAMContent1;
    // 10 3
    if(RAMContent1 < 0 || RAMContent2 < 0)
        result = -1; //           [ERRO: NUMERO NEGATIVO]
    if (RAMContent1 > 64)
        result = -2; //            [ERRO: NUMERO > LIMITE]
    for (int i = 0; i < RAMContent2; i++) 
        result = mult(result, aux);

    return result;
}

float fatorial(float RAMContent1) {
    float result = RAMContent1;
    if (RAMContent1 < 0)
        return -1; //           [ERRO: NUMERO NEGATIVO]
    for (int i = RAMContent1; i > 1; i--) 
        result = mult(result, i - 1);

    return result;
}

float raiz(float RAMContent1) {

  float result = 0;
  float valorprox;
  float valormax = RAMContent1;
  
  int raizaux = RAMContent1;

  for (int i=2;;i++) {
      raizaux = divis(RAMContent1,i); 

      if (exponencial(raizaux, 2) == RAMContent1)
      return raizaux;
      else if (exponencial(raizaux, 2) < RAMContent1) { 
          for (int i = raizaux; i <= valormax; i++) {
          result = exponencial(i, 2);
          if(result >= RAMContent1) {
              valorprox = valorprox - RAMContent1;
              result = result - RAMContent1;
              result = (result < 0)? -result : result;
              valorprox = (valorprox < 0)? -valorprox : valorprox;
              if (valorprox < result)
                  return i - 1;
              return i;
          }
          valorprox = result;
          }
      }
      else 
        valormax=raizaux;
  }

  return result;
}

void run(Machine* machine) {
    // Registradores
    int PC = 0;
    int address1;
    int address2;
    int address3;
    int opcode = 0;
    
    float value;
    float result;
    float RAMContent1;
    float RAMContent2;
    float raizes[15] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225};

    while(opcode != -1) {
        Instruction instruction = machine->instructions[PC];
        opcode = instruction.opcode;
        // [ATRIBUICAO DE VALORES]
        address1 = instruction.info1;
        address2 = instruction.info2;
        address3 = instruction.info3;
        RAMContent1 = machine->RAM.items[address1];
        RAMContent2 = machine->RAM.items[address2];

        switch (opcode) {
            case -1:
                printf("  > Finalizando a execucao.\n");
                break;

            case 0:
                value = (float) instruction.info1;
                address1 = instruction.info2;
                machine->RAM.items[address1] = value;
                printf("  > Levando informacao (%f) para a RAM[%d].\n", value, address1);
                break;

            case 1: // [SOMA]
                result = RAMContent1 + RAMContent2;
                
                machine->RAM.items[address3] = result;
                printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 2: // [SUBTRACAO]
                result = RAMContent1 - RAMContent2;
                
                machine->RAM.items[address3] = result;
                printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", //
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 3: // [MULTIPLICACAO]
                result = 0;
                RAMContent1 = 36;
                RAMContent2 = rand() % 4 + 1;

                result = mult(RAMContent1, RAMContent2);
                machine->RAM.items[address3] = result;
                printf("  > Multiplicando RAM[%d] (%.2f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 4: // [DIVISAO]
                result = 0;
                RAMContent1 = 36; 
                RAMContent2 = 9;
                
                result = divis(RAMContent1, RAMContent2);
                machine->RAM.items[address3] = result;
                printf("  > Dividindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address2, RAMContent2, address3, result);
                break;

            case 5: // [FIBONACCI]
                result = 0;
                RAMContent1 = rand() % 15 + 1;

                result = fibonacci(RAMContent1);
                machine->RAM.items[address3] = result;
                printf("  > Calculando a sequência de Fibonacci: RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address3, result);
                break;

            case 6: // [EXPONENCIAL]
                result = 0;
                RAMContent1 = rand() % 20 + 1;
                RAMContent2 = rand() % 3 + 1;

                machine->RAM.items[address3] = result;
                printf("  > Calculando o exponencial de RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n",
                            address1, RAMContent1, address2, RAMContent2, address3, result);
                break; 

            case 7: // [FATORIAL]
                RAMContent1 = rand() % 10 + 1;

                result = fatorial(RAMContent1);
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
        }
        PC++;
    }
}

void printRAM(Machine* machine, int modo) {
    printf("  > RAM");
    for (int i = 0; i < machine->RAM.size; i++)
      printf("\t\t[%5d] : %f\n", i, machine->RAM.items[i]);
}