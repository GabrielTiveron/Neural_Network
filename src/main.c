#include<stdio.h>
#include<stdlib.h>
#include"../inc/ler_arquivo.h"
#include"../inc/rede_neural.h"
#define ASFALTO 1
#define GRAMA 0


void alocar_vetor_int(int **, int);
void alocar_vetor_double(double **, int);

int main(int argc, char const **argv) {
  if(argc != 2){
    printf("\nNecessário o número de neuronios da camada oculta\n");
    return 0;
  }
  int nmr_neuronios = atoi(argv[1]);

  int casos_treino[25], index_treino = 0, opcao;
  int **pixels = (int**) malloc(1024 * sizeof(int*));
  double**resultado = (double**)calloc(50, sizeof(double*));

  alocar_vetor_int(pixels, 1024);
  alocar_vetor_double(resultado, 536);

  if(pixels == NULL || resultado == NULL){
    printf("Não foi possível alocar memória\n");
    exit(-1);
  }
  
  printf("Sorteando casos de treino\n");
  sortear_casos(casos_treino);
  printf("\t\t\tCriando dados de Treino\n");
  printf("===================================================================\n");
  for (int i = 0; i < 50; i++) {
    if(i % 2 == 0){
      opcao = GRAMA;
      if(i != 0)index_treino++;
    }
    else{opcao = ASFALTO;}
    gerar_vetores(pixels, casos_treino[index_treino], opcao, resultado[i]);
  }

  printf("\t\t\tCalibrando Rede Neural\n");
  printf("===================================================================\n");

  treinar_rede(resultado, nmr_neuronios);

  printf("\t\t\tRede Neural Calibrada\n");
  printf("===================================================================\n");

  return 0;
}

void alocar_vetor_int(int **vetor, int tamanho){
  for (int i = 0; i < tamanho; i++) {
    *(vetor+i) = (int*)malloc(tamanho*sizeof(int));
  }
}
void alocar_vetor_double(double **vetor, int tamanho){
  for (int i = 0; i < tamanho; i++) {
    *(vetor+i) = (double*)malloc(tamanho*sizeof(double));
  }
}
