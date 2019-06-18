#include"../inc/rede_neural.h"

void treinar_rede(double**entradas, int nmr_neuronio){
  Neuronio *camada_entrada, *camada_oculta, *camada_saida;
  camada_entrada = (Neuronio*)calloc(536, sizeof(Neuronio));
  camada_oculta  = (Neuronio*)calloc(nmr_neuronio, sizeof(Neuronio));
  camada_saida   = (Neuronio*)calloc(1, sizeof(Neuronio));
  //instanciar dados da camada de entrada
  sortear_wb(&camada_entrada, 536);
  sortear_wb(&camada_entrada, nmr_neuronio);
  sortear_wb(&camada_entrada, 1);
  printf("\t\t\tPrimeira camada instanciada\n");
  printf("===================================================================\n");
  //Epocas TODO
  printf("\t\t\tCalibrando Rede Neural\n");
  printf("===================================================================\n");
  int e = 0;
  for(int epoca = 0; epoca < 1000; epoca++){
    for(int i = 0; i < 50; i++){
      inserir_dados(entradas[i], &camada_entrada);
      inserir_dados(&camada_entrada->saida, &camada_oculta);  
    }  
  }
}

void sortear_wb(Neuronio** neuronio, int nmr_entradas){
  int size_neuronio = sizeof((*neuronio)) / sizeof(Neuronio);
  for(int j = 0; j < size_neuronio; j++){
    (*neuronio)->w = (int*)malloc(nmr_entradas*sizeof(int));
    int size = sizeof((*neuronio)->w)/sizeof(int);
    for(int i = 0; i < size; i++){
      (*neuronio)->w[i] = rand()%10;
    }
    (*neuronio)->b = rand()%10;
  }
}

void inserir_dados(double*entradas, Neuronio** camada){
  int size = sizeof(*camada) / sizeof(Neuronio);
  for(int i = 0; i < size; i++){
    (*camada+i)->entrada = &entradas[i];
    nucleo((*camada+i));
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
