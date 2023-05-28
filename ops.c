#include "ops.h"
#include <stdio.h>
#include <stdlib.h>

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