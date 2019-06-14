#include "../inc/ilbp.h"


void cada_pixel(int ** pixels, double * ilbp){

  for (int linha = 1; linha < 1024; linha++) {
    for (int coluna = 1; coluna < 1024; coluna++) {
      ilbp[media_vizinhos(pixels, linha, coluna)] += 1.0;
    }
  }

}

int media_vizinhos(int ** pixels, int linha, int coluna){
  // printf("entrei vizinhos\n");
  int media = 0;
  int vizinhos[9];
  vizinhos[0] = pixels[linha][coluna];
  vizinhos[1] = pixels[linha - 1][coluna];
  vizinhos[2] = pixels[linha + 1][coluna];
  vizinhos[3] = pixels[linha][coluna - 1];
  vizinhos[4] = pixels[linha][coluna + 1];
  vizinhos[5] = pixels[linha - 1][coluna - 1];
  vizinhos[6] = pixels[linha - 1][coluna + 1];
  vizinhos[7] = pixels[linha + 1][coluna - 1];
  vizinhos[8] = pixels[linha + 1][coluna + 1];
  media =  vizinhos[0] + vizinhos[1] + vizinhos[2] + vizinhos[3] + vizinhos[4] + vizinhos[5] + vizinhos[6] + vizinhos[7] + vizinhos[8];
  media /= 9;
  return gera_matriz_normalizada(vizinhos, media);
}

int gera_matriz_normalizada(int * vizinhos, int media){
  // printf("entrei matrix\n");
  for (int i = 0; i < 9; i++) {
    vizinhos[i] = vizinhos[i] > media;
  }
 return reconhecer_ordens(vizinhos);
}

int reconhecer_ordens(int vizinhos[9]){
  // printf("entrei ordens\n");
  int decimal = 0;
  int menor = 513;
  int temp;
  int terminou = 0;
  while(terminou != 8){
    decimal = 0;
    for(int i = 0; i < 9; i++){
      decimal += pow(2, i) * vizinhos[i];
    }
    if(decimal < menor){
      menor = decimal;
    }
    temp = vizinhos[8];
    for (int j = 8; j > 0; j--) {
      vizinhos[j] = vizinhos[j-1];
    }
    vizinhos[0] = temp;
    terminou++;
  }
  return menor;
}
