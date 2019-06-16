#include "../inc/glcm.h"

void glcm(int ** pixels, double *glcm_vector, double **glcm_matrix){
  double homogeneidade = 0;
  double energia = 0;
  double contraste = 0;
  int i = 0, j = 0;
  for(i; i < 256; i++){
    for(j = 0; j < 256; j++){
      glcm_matrix[i][j] = 0;
    }
  }

  for (int i = 0; i < 8; i++){
    build_glcm_matrix(pixels, glcm_matrix, i);
    calcular_homogeneidade(glcm_matrix, &homogeneidade, glcm_vector, i);
    calcular_energia(glcm_matrix, &energia, glcm_vector, i);
    calcular_contraste(glcm_matrix, &contraste, glcm_vector, i);
  }


}


void build_glcm_matrix(int ** file, double **glcm_matrix, int num){
  int current_value = 0, aux_value = 0;

  for (int i = 0; i < 1024; i++){
    for (int j = 0; j < 1024; j++){
      current_value = *(*(file+i)+j);


      // LATERAL DIREITO
      if( j < 1022 && num == 0){
        aux_value = *(*(file+i)+j+1);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois direta\n");
      // DIAGONAL DIREITA SUPERIOR
      if( j < 1022 && i > 0 && num == 1){
        aux_value = *(*(file+i-1)+j+1);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois direta sup\n");


      // SUPERIOR
      if( i > 0 && num == 2){
        aux_value = *(*(file+i-1)+j);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois sup\n");


      // DIAGONAL ESQUERDA SUPERIOR
      if( i > 0 && j > 0 && num == 3){
        aux_value = *(*(file+i-1)+j-1);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois esquerda sup\n");


      // LATERAL ESQUERDA
      if( j > 0 && num == 4){
        aux_value = *(*(file+i)+j-1);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois esquerda\n");

      // DIAGONAL ESQUERDA INFERIOR
      if( j > 0 && i < 1023 && num == 5){
        aux_value = file[i+1][j-1];
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois esquerda inf\n");

      // INFERIOR
      if( i < 1022 && num == 6){
        aux_value = *(*(file+i+1)+j);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois inf\n");

      // DIAGONAL DIREITA INFERIOR
      if( i < 1022 && j < 1022 && num == 7){
        aux_value = *(*(file+i+1)+j+1);
        glcm_matrix[current_value][aux_value]+=1;
      }
      //printf("Depois direta inf:  i = %d, j = %d\n", i, j);

    }
  }
}

void calcular_homogeneidade(double **glcm_matrix, double *homogeneidade, double *glcm_vector, int num){

  *homogeneidade = 0;
  for (int i = 0; i < 256; i++){
    for (int j = 0;j < 256; j++){
      *homogeneidade += glcm_matrix[i][j]/(1.0+abs(i-j));
    }
  }
  *homogeneidade/=1047552;
  if(sizeof(glcm_vector)/sizeof(int) > num*3)
  glcm_vector[num*3] = *homogeneidade;

//printf("Final Homogeneidade\n");
}

void calcular_energia(double **glcm_matrix, double *energia, double *glcm_vector, int num){

  for (int i = 0; i < 256; i++){
    for (int j = 0;j < 256; j++){
      *energia += pow(glcm_matrix[i][j], 2);
    }
  }
  *energia/=pow(1047552,2);
  if(sizeof(glcm_vector)/sizeof(int) > num*3+1)
  *(glcm_vector + (num*3) + 1) = *energia;


//printf("Final Energia\n");
}

void calcular_contraste(double **glcm_matrix, double *contraste, double *glcm_vector, int num){

  for (int i = 0; i < 256; i++){
    for (int j = 0;j < 256; j++){
      *contraste += (i - j)*(i - j)*glcm_matrix[i][j];
    }
  }
  *contraste/=1047552;
  if(sizeof(glcm_vector)/sizeof(int) > num*3+2)
  *(glcm_vector + (num*3) + 2) = *contraste;

//printf("Final Contraste\n");
}
