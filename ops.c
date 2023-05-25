#include <stdio.h>
#include <stdlib.h>
#include "ops.h"

//
float soma(float content1, float content2) {
  return content1 + content2;
}

float sub(float content1, float content2) {
  return content1 - content2;
}

float mult(float content1, float content2) {
  float result = 0;
  int isnegative = 0;
  if(content1 < 0) 
    content1 = -content1;
  if (content2 < 0)
    content2 = -content2;

  for (int i = 0; i < content2; i++) 
    result += content1;

  return result;
}

float div(float a, float b) {
  float result = 0;
  int aux_divisao = b; 

  while(a >= b){
      b += aux_divisao;
      result++;
  }

  return result;
}

float fibonacci(int n) {
  float *result;
  result = malloc(n * sizeof(float));
  result[0] = 0; result[1] = 1;

  for (int i = 2; i < n; i++) {
    result[i] = result[i - 1] + result[i - 2];
  }
  if(n == 0)
    return result[n];
  
  return result[n - 1];
}

float expo(float n1, float n2) {
  float expo = 0;
  if(n1 < 0 || n2 < 0)
    return -1; //           [ERRO: NUMERO NEGATIVO]
  if (n1 > 64)
    return -2; //            [ERRO: NUMERO > LIMITE]
  
  for (int i = 0; i < n2; i++) 
    expo += mult(n1, n1);

  return expo;
}

float fat(int num) {
  float fact = num;
  if (num < 0)
    return -1; //           [ERRO: NUMERO NEGATIVO]
  for (int i = num; i > 1; i--) 
    fact = mult(fact, i - 1);

  return fact;
} 

float raiz() {
  float sqroot = 0;

  

}
