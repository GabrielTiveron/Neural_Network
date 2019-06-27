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
  printf("\t\t\tCalibrando Rede Neural\n");
  printf("===================================================================\n");
  double e = 0, *errors;
  errors = (double*)malloc(50*sizeof(double));
  for(int epoca = 0; epoca < 1000; epoca++){
    e = 0;
    for(int i = 0; i < 50; i++){
      inserir_camada_entrada(entradas[i], &camada_entrada, 536);
      inserir_dados(camada_entrada, &camada_oculta, nmr_neuronio, 536);
      inserir_dados(camada_oculta, &camada_saida, 1, nmr_neuronio);
      if(i%2 == 0){
        errors[i] = pow(0.0-camada_saida->saida, 2);
        e += errors[i];
      }else{
        errors[i] = pow(1.0-camada_saida->saida, 2);
        e += errors[i];
      }
    }
    printf("e = %.10lf\n", e);
    if(abs(e/50.0) < 0.2)break;  
    //TODO: BackPropagation
    //back_propagation(&camada_entrada, &camada_oculta, &camada_saida, errors);
  }
}

void sortear_wb(Neuronio** neuronio, int nmr_entradas, int nmr_w){
  for(int j = 0; j < nmr_entradas; j++){
    (*neuronio+j)->w = (double*)malloc(nmr_w*sizeof(double));
    for(int i = 0; i < nmr_w; i++){
      (*neuronio+j)->w[i] = (double)rand()/(double)(RAND_MAX/15000.0);
    }
    (*neuronio+j)->b = (double)rand()/(double)(RAND_MAX/15000.0);
  }
}

void inserir_camada_entrada(double*entradas, Neuronio** camada, int size_camada){
  for(int i = 0; i < size_camada; i++){
    (*camada+i)->entrada = (double*)malloc(536*sizeof(double));
    for(int j = 0; j < 536; j++){
      (*camada+i)->entrada[j] = entradas[j];
    }
  }
  
    nucleo(camada, 536);

}

void inserir_dados(Neuronio*saidas, Neuronio**camada, int size_camada, int size_saida){
  for(int i = 0; i < size_camada; i++){
    (*camada+i)->entrada = (double*)malloc(size_saida*sizeof(double));
    for(int j = 0; j < size_saida; j++){
      (*camada+i)->entrada[j] = saidas[j].saida;
    }
  }  
    nucleo(camada, size_camada);


}

void nucleo(Neuronio**neuronio, int size){
  double aux;
  for(int i = 0; i < size; i++){
    printf("Lul - %d\n", i);
    aux = somatorio((*neuronio+i), size);
    (*neuronio+i)->saida = f(aux +(*neuronio+i)->b);
  }
}

double somatorio(Neuronio*entradas, int size){
  double soma = 0;
  for(int i = 0; i < size; i++){
    if(i%375 == 0)
    printf("%d - entrada = %.2lf\t|\tw = %.5lf\n",i, entradas->entrada[i], entradas->w[i]);
    soma += entradas->entrada[i] * entradas->w[i];
  }
  
  return soma;
}

double f(double n){
  double saida;
  saida = 1/(1+pow(M_E,-1*n));
  return saida;
}

void back_propagation(Neuronio**camada_entrada, Neuronio**camada_oculta, Neuronio**camada_saida, int *error){
 /* TODO: 
    Seja:
      U(m) = somatorio(wi + xi)
      V(m) = f(U(m) + bj)
    Calcular gradientes seguindo as funções: 
      ð(m) = f'(V(m)+bj)) * e(m)                      Para as camadas de entrada e oculta
      ð(m) = f'(V(m)+bj)) * somatori(ð(m) * e(m))     Para a camada de saida

    Para alterar as sinapses:                         Sendo n = a taxa constante de aprendizagem -> uma constante qualquer
      Wji(m+1) = Wji(m) + n*v(m) *ð(m)
      Bj(m+1) = Bj(m) + n*ðj(m) 



 */
}
