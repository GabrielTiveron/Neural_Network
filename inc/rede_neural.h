#ifndef REDE_NEURAL_H
#define REDE_NEURAL_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define T_A 0.5

typedef struct Neuronio{
  double* entrada;
  double saida;
  double* w;
  double b;
}Neuronio;

void sortear_wb(Neuronio**,int,int);
void treinar_rede(double**,int,Neuronio**,Neuronio**,Neuronio**);
void inserir_camada_entrada(double*, Neuronio**, int);
void inserir_dados(Neuronio**,Neuronio**,int,int);
void nucleo(Neuronio**, int);
double somatorio(Neuronio**, int,int);
double f(double);
void back_propagation(Neuronio**,Neuronio**,Neuronio**,double,int,int,double*);
void altera_sinapses_vieses(Neuronio**,Neuronio**,int,int,double*);
double somatorio_oculta(double*,Neuronio**,int,int);
double f_linha(double);
void testar_rede(double**,int,Neuronio**,Neuronio**,Neuronio**);

#endif
