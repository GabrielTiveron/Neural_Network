#include"../inc/auxiliar.h"

double distancia(double * a, double * b){
  double soma = 0, sub;
  for (int i = 0; i < 536; i++) {
    sub = a[i] - b[i];
    soma += (sub*sub);
  }
  double distancia = sqrt(soma);
  return distancia;
}

void concatenar(double ilbp[512], double glcm[24], double *resultado){
  for (int i = 0; i < 512; i++) {
    resultado[i] = ilbp[i];
  }
  for(int i = 512; i < 536; i++){
    resultado[i] = glcm[i-512];
  }
}

void normaliza_vetor(double * vetor){
  int min = 1024*1024+1, max = 0;
  for (int i = 0; i < 536; i++) {
    if (vetor[i] > max) {
      max = vetor[i];
    }
    if (vetor[i] < min) {
      max = vetor[i];
    }
  }
  for (int i = 0; i < 536; i++) {
    vetor[i] = (vetor[i] - min) / (max - min);
  }
}
