#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {
    
    srand(time(NULL));   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 3 && ( strcmp(argv[1], "menu")==0 && (argc > 2) )) {
        printf("Numero de argumentos invalidos! Sao 3.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES]\n");
        printf("\tExemplo 1 de execucao: ./exe random 10\n");
        printf("\tExemplo 3 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        printf("\tExemplo 1 de execucao: ./exe menu\n");
        return 0;
    }

    int ramSize;
    Machine machine;
    Instruction *instructions;
    int modo;

    if (strcmp(argv[1], "random") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRandomInstructions(ramSize);
        modo = 1;
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], &ramSize);
        modo = 1;
    } 
    else if (strcmp(argv[1], "menu") == 0) {
        instructions = menu();
        ramSize=2;
        modo = 2;
    }
    else {
        printf("Opcao invalida.\n");
        return 0;
    }
    
    printf("Iniciando a maquina...\n");
    start(&machine, instructions, ramSize);
    printRAM(&machine, 1);
    run(&machine);
    printRAM(&machine, modo);
    stop(&machine);
    printf("Finalizando a maquina...\n");

    return 0;
}