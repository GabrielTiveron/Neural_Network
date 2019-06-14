#include"../inc/ler_arquivo.h"


// char ** montar_arquivos(int * index, char * base){
//   char ** arquivo = (char**) calloc(25, sizeof(char*));
//
//   for (int i = 0; i < 25; i++) {
//     if(strcmp(base, BASE_GRAMA) == 0){
//       arquivo[i] = (char*) calloc(24, sizeof(char));
//     }else{
//       arquivo[i] = (char*) calloc(25, sizeof(char));
//     }
//   }
//
//   for (int i = 0; i < 25; i++) {
//     sprintf(arquivo[i], "%s%02d%s",base, index[i], ".txt");
//
//   }
//
//   return arquivo;
//
// }
char * montar_arquivo(int index, char * base){
  char * arquivo = (char*) calloc(25, sizeof(char));

  sprintf(arquivo, "%s%02d%s",base, index, ".txt");


  return arquivo;

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
    arquivo = (char*) calloc(29, sizeof(char));
    arquivo = montar_arquivo(index_teste, BASE_GRAMA);
  }
  else{
    arquivo = (char*) calloc(32, sizeof(char));
    arquivo = montar_arquivo(index_teste, BASE_ASFALTO);
  }

  double * ilbp = (double*)calloc(512, sizeof(double));
  double * glcm_teste = (double*)malloc(24*sizeof(double));
  if(ilbp == NULL || glcm_teste == NULL){
    printf("Não foi possível alocar memoria\n");
    exit(-1);
  }
  ler_imagens(arquivo, pixels);
  printf("To aqui\n");
  cada_pixel(pixels, ilbp);
  printf("To aqui depois ilbp\n");
  glcm(pixels, glcm_teste);
  printf("To aqui depois glcm\n");

  concatenar(ilbp, glcm_teste, resultado);

  normaliza_vetor(resultado);

  free(arquivo);
  free(ilbp);
  free(glcm_teste);

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
