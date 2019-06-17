#include"../inc/rede_neural.h"

void treinar_rede(double**entradas, int nmr_neuronio){
  Neuronio *camada_entrada, *camada_oculta, *camada_saida;

  camada_entrada = (Neuronio*)calloc(536, sizeof(Neuronio));
  camada_oculta  = (Neuronio*)calloc(nmr_neuronio, sizeof(Neuronio));
  camada_saida   = (Neuronio*)calloc(1, sizeof(Neuronio));
  //instanciar dados da camada de entrada
  for(int i = 0; i < 50; i++){
    inserir_dados(entradas[i], &camada_entrada);
  }
  //Epocas TODO
  for(int i = 0; i < 1000; i++){
    
  }
}

void inserir_dados(double*entradas, Neuronio** camada_entrada){
  for(int i = 0; i < 536; i++){
    for(int j = 0; j < sizeof(entradas[i])/sizeof(double); j++)
      (*camada_entrada+i)->w[i] = rand() % 10;
    (*camada_entrada+i)->b = rand() % 10;
    (*camada_entrada+i)->entrada = &entradas[i];
    nucleo((*camada_entrada+i));
  }

}

void nucleo(Neuronio*neuronio){
  int size;
  size = sizeof(neuronio->entrada) / sizeof(double);
  for(int i = 0; i < size; i++){
    (neuronio+i)->saida = f(somatorio((neuronio+i), size)+(neuronio+i)->b);
  }
}

double somatorio(Neuronio*entradas, int size){
  double soma = 0;
  for(int i = 0; i < size; i ++){
    soma += entradas->entrada[i] * entradas->w[i];
  }
  
  return soma;
}

double f(double n){
  double saida;
  saida = 1/(1+pow(M_E,-1*n));
  return saida;
}
