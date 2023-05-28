#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt
    
    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction));

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 9; //0, 1, 2, 3, 4, 5, 6, 7, 8
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}

Instruction* menu(){
    int op=0;

    printf("\nMENU\n");
    printf("1- SOMA\n2- SUBTRAÇÂO\n3- MULTIPLICAÇÃO\n4- DIVISÃO\n6- EXPONENCIAÇÃO\n5- FATORAÇÃO\n7- SEQUÊNCIA DE FIBONACCI\n8- RAIZ QUADRADA (APROXIMADA)");
    do {
      printf("\nInsira um número inteiro entre 1 e 8: \n");
      scanf("%d", &op);
      if(op<1||op>8)
        printf("\nNúmero Inválido!!\nDigite novamente!!");
    } while (op < 1 || op > 8);
    
    Instruction* instructions = (Instruction*) malloc(2 * sizeof(Instruction));

    instructions[0].opcode=op;
    instructions[0].info1=0;
    instructions[0].info2=1;
    instructions[0].info3=0;

    instructions[1].opcode =-1;
    instructions[1].info1 = -1;
    instructions[1].info2 = -1;
    instructions[1].info3 = -1;

    return instructions;
}