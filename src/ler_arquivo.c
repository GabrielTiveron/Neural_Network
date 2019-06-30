#include"../inc/ler_arquivo.h"


void montar_arquivo(char**arquivo, int index, char * base){
  sprintf(*arquivo, "%s%02d%s",base, index, ".txt\0");
}

void sortear_casos(int * arquivo_treino){

  srand(time(NULL));
  int r = rand() % 50 + 1;

  for (int i = 0; i < 25; i++) {
    arquivo_treino[i] = r;

    r = rand() % 50 + 1;
    int repetido = 1;
    while(repetido){
      for (int j = i; j >= 0; j--) {
        if(r == arquivo_treino[j]){
          r = rand() % 50 + 1;
          repetido = 1;
          break;
        }
        else{
          repetido = 0;
        }
      }
    }
  }
}

void gerar_vetores(int ** pixels, int index_teste, int opcao, double *resultado){
  char * arquivo;
  if (opcao == 0) {
    arquivo = (char*) calloc(30, sizeof(char));
    montar_arquivo(&arquivo,index_teste, BASE_GRAMA);
  }
  else{
    arquivo = (char*) calloc(33, sizeof(char));
    montar_arquivo(&arquivo, index_teste, BASE_ASFALTO);
  }

  double * ilbp = (double*)calloc(512, sizeof(double));
  double * glcm_teste = (double*)malloc(24*sizeof(double));
  double ** glcm_matrix = calloc(256, sizeof(double*));
  for(int i = 0; i < 256; i++){
	  glcm_matrix[i] = calloc(256, sizeof(double));
  } 
  if(ilbp == NULL || glcm_teste == NULL || glcm_matrix == NULL){
    printf("Não foi possível alocar memoria\n");
    exit(-1);
  }
  ler_imagens(arquivo, pixels);
  cada_pixel(pixels, ilbp);
  glcm(pixels, glcm_teste, glcm_matrix);

  concatenar(ilbp, glcm_teste, resultado);

  normaliza_vetor(resultado);

  free(arquivo);
  free(ilbp);
  free(glcm_teste);
  free(glcm_matrix[0]);
  free(glcm_matrix);

}


void ler_imagens( char * imagens, int ** pixels){
  FILE * imagem;
    printf("%s\n", imagens);
    imagem = fopen(imagens, "r");

   if(imagem == NULL){
     printf("Não foi possível abrir o arquivo: %s\n", imagens );
     exit(3);
   }

   int linha = 0;
   int coluna = 0;

   while (!feof(imagem)) {
     fscanf(imagem, "%d;", &pixels[linha][coluna]);

     coluna++;
     if(coluna == 1025){
       coluna = 0;
       linha++;
     }
     if(linha == 1024)break;
   }

   fclose(imagem);

}
