#ifndef REDE_NEURAL_H
#define REDE_NEURAL_H

#include<stdio.h>
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

void sortear_wb(Neuronio**,int,int);
void treinar_rede(double**,int);
void inserir_camada_entrada(double*, Neuronio**, int);
void inserir_dados(Neuronio*,Neuronio**,int,int);
void nucleo(Neuronio*, int);
double somatorio(Neuronio*, int);
double f(double);


#endif
