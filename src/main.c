#include<stdio.h>
#include<stdlib.h>
#include"../inc/ler_arquivo.h"
#include"../inc/rede_neural.h"
#define ASFALTO 1
#define GRAMA 0


void alocar_vetor_int(int **, int);
void alocar_vetor_double(double **, int);
void free_array(double**, int,int);

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
  
  printf("\t\t\tSorteando casos de treino\n");
  printf("===================================================================\n");
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
  Neuronio *camada_entrada, *camada_oculta, *camada_saida;
  camada_entrada = (Neuronio*)malloc(536*sizeof(Neuronio));
  camada_oculta  = (Neuronio*)malloc(nmr_neuronios*sizeof(Neuronio));
  camada_saida   = (Neuronio*)malloc(1*sizeof(Neuronio));
  treinar_rede(resultado, nmr_neuronios, &camada_entrada, &camada_oculta, &camada_saida);
  
  for(int i = 0; i < 50; i++){
    free(*(resultado+i));
  }
  free(resultado);

  printf("\t\t\tRede Neural Calibrada\n");
  printf("===================================================================\n");

  printf("\t\t\tCriando dados de Teste\n");
  printf("===================================================================\n");
  double **resultado_teste = (double**)calloc(50, sizeof(double*));
  
  alocar_vetor_double(resultado_teste, 536);
  
  int caso_teste[25], index_teste = 0, treino = 0;

  for(int i = 1; i <= 50; i++){
    treino = 0;
    for(int j = 0; j < 25; j++){
      if(casos_treino[j] == i) treino = 1;
    }
    if(!treino){
      caso_teste[index_teste] = i;
      index_teste++;
    }
  }

  index_teste = 0;

  for(int i = 0; i < 50; i++){
     if(i % 2 == 0){
        opcao = GRAMA;
        if(i != 0)index_teste++;
      }
      else{
        opcao = ASFALTO;
      }
      gerar_vetores(pixels, caso_teste[index_teste], opcao, resultado_teste[i]);
  }
  
  printf("Aqui\n");
  
  testar_rede(resultado_teste, nmr_neuronios, &camada_entrada, &camada_oculta, &camada_saida);
  free_array(resultado_teste, 50, 536);
  
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

void free_array(double **array, int linha, int coluna){
  for(int i = 0; i < 50; i++){
    free(*(array+i));
  }
  free(array);
}
