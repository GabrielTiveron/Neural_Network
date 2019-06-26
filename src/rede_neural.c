#include"../inc/rede_neural.h"

void treinar_rede(double**entradas, int nmr_neuronio){
  Neuronio *camada_entrada, *camada_oculta, *camada_saida;
  camada_entrada = (Neuronio*)calloc(536, sizeof(Neuronio));
  camada_oculta  = (Neuronio*)calloc(nmr_neuronio, sizeof(Neuronio));
  camada_saida   = (Neuronio*)calloc(1, sizeof(Neuronio));
  //instanciar dados da camada de entrada
  sortear_wb(&camada_entrada, 536, 536);
  sortear_wb(&camada_oculta, nmr_neuronio, 536);
  sortear_wb(&camada_saida, 1, nmr_neuronio);
  printf("\t\t\tPrimeira camada instanciada\n");
  printf("===================================================================\n");
  printf("Camada_E=%d\tCamada_O=%d\tCamada_S=%d\n", (camada_entrada)->w[10], camada_oculta->w[11], camada_saida->w[15]);
  printf("\t\t\tCalibrando Rede Neural\n");
  printf("===================================================================\n");
  double e = 0;
  for(int epoca = 0; epoca < 1000; epoca++){
    e = 0;
    for(int i = 0; i < 50; i++){
      inserir_camada_entrada(entradas[i], &camada_entrada, 536);
      printf("Primeira camada\n");
      inserir_dados(camada_entrada, &camada_oculta, nmr_neuronio, 536);
      printf("Camada oculta\n");
      inserir_dados(camada_oculta, &camada_saida, 1, nmr_neuronio);
      printf("Camada saia\n");
      if(i%2 == 0){
        e+=0.0-camada_saida->saida;
      }else{
        e+=1.0-camada_saida->saida;
      }
    }
    printf("e = %.10lf\n", e);
    if(e/50.0 < 0.2)break;  
    //TODO: BackPropagation
  }
}

void sortear_wb(Neuronio** neuronio, int nmr_entradas, int nmr_w){
  for(int j = 0; j < nmr_entradas; j++){
    (*neuronio+j)->w = (int*)malloc(nmr_w*sizeof(int));
    for(int i = 0; i < nmr_w; i++){
      (*neuronio+j)->w[i] = rand()%1000;
    }
    (*neuronio+j)->b = rand()%1000;
  }
}

void inserir_camada_entrada(double*entradas, Neuronio** camada, int size_camada){
  for(int i = 0; i < size_camada; i++){
    printf("Entrada - %d=%lf\n",i,entradas[i]);
    (*camada+i)->entrada = (double*)malloc(536*sizeof(double));
    for(int j = 0; j < 536; j++){
      (*camada+i)->entrada[j] = entradas[j];
    }
    printf("Sai for\n");
    nucleo((*camada+i), 536);
  }

}

void inserir_dados(Neuronio*saidas, Neuronio**camada, int size_camada, int size_saida){
  for(int i = 0; i < size_camada; i++){
    (*camada+i)->entrada = (double*)malloc(size_saida*sizeof(double));
    for(int j = 0; j < size_saida; j++){
      (*camada+i)->entrada[j] = saidas[j].saida;
    }
    nucleo((*camada+i), size_saida);
  }  


}

void nucleo(Neuronio*neuronio, int size){
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
