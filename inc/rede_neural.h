#ifndef REDE_NEURAL_H
#define REDE_NEURAL_H

#include<stdlib.h>
#include<math.h>
#define ENTRADA 0
#define OCULTA 1
#define SAIDA 2

typedef struct Neuronio{
  double* entrada;
  double saida;
  int* w;
  int b;
}Neuronio;

void treinar_rede(double**,int);
void inserir_dados(double*, Neuronio**);
void nucleo(Neuronio*);
double somatorio(Neuronio*, int);
double f(double);


#endif
