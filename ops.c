#include <stdio.h>
#include <stdlib.h>
#include "ops.h"

float soma(float content1, float content2) {
  return content1 + content2;
}

float sub(float content1, float content2) {
  return content1 - content2;
}

float mult(float content1, float content2) {
  int flag = 0;
  float result = 0;

  if(content1 < 0) {
    content1 = -content1;
    flag++;
  }
  if (content2 < 0) {
    content2 = -content2;
    flag++;
  }

  for (int i = 0; i < content2; i++) 
    result += content1;
  
  if(flag == 1) {
    result = -result;
  }
  return result;
}

float div(float a, float b) {
  int flag = 0;
  float result = 0;
  if(a < 0) {
    a = -a;
    flag++;
  }
  if(b < 0) {
    b = -b;
    flag++;
  }
  int aux = b;
  while(a >= b){ 
      b += aux;
      result++;
  }
  if (flag == 1)
    result = -result;

  return result;
}

float fibonacci(int n) {
  int i = 1, k;
  float result = 0; 
  for (k = 1; k <= n; k++) {
    result += i;
    i = result - i;
  }
  
  return result;
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

float raiz(int num) {
  float sqroot = 0;
  
  
  return sqroot;
}
