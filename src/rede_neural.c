#include"../inc/rede_neural.h"

void treinar_rede(double**entradas, int nmr_neuronio, Neuronio**camada_entrada, Neuronio**camada_oculta, Neuronio**camada_saida){
  //instanciar dados da camada de entrada
  sortear_wb(camada_entrada, 536, 536);
  sortear_wb(camada_oculta, nmr_neuronio, 536);
  sortear_wb(camada_saida, 1, nmr_neuronio);
  printf("\t\t\tCalibrando Rede Neural\n");
  printf("===================================================================\n");
  double e = 0, *errors;
  errors = (double*)malloc(50*sizeof(double));
  for(int epoca = 0; epoca < 1000; epoca++){
    e = 0;
    for(int i = 0; i < 50; i++){
      inserir_camada_entrada(entradas[i], camada_entrada, 536);
      inserir_dados(camada_entrada, camada_oculta, nmr_neuronio, 536);
      inserir_dados(camada_oculta, camada_saida, 1, nmr_neuronio);
      if(i%2 == 0){
        errors[i] = 1.0-(*camada_saida)->saida;
        e += pow(errors[i], 2);
      }else{
        errors[i] = 0.0-(*camada_saida)->saida;
        e += pow(errors[i], 2);
      }
      back_propagation(camada_entrada, camada_oculta, camada_saida, errors[i], nmr_neuronio, i, entradas[i]);
    }
    printf("e = %.10lf\n", e/50.0);
    if(e/50.0 < 0.2){
      printf("Calibrado pelo fator erro\n");
      break;
    }
  }
  free(errors);
}

void sortear_wb(Neuronio** neuronio, int nmr_entradas, int nmr_w){
  for(int j = 0; j < nmr_entradas; j++){
    (*neuronio+j)->w = (double*)malloc(nmr_w*sizeof(double));
    for(int i = 0; i < nmr_w; i++){
      (*neuronio+j)->w[i] = (double)rand()/(double)(RAND_MAX);
    }
    (*neuronio+j)->b = (double)rand()/(double)(RAND_MAX);
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

void inserir_dados(Neuronio**saidas, Neuronio**camada, int size_camada, int size_saida){
  for(int i = 0; i < size_camada; i++){
    (*camada+i)->entrada = (double*)malloc(size_saida*sizeof(double));
    for(int j = 0; j < size_saida; j++){
      (*camada+i)->entrada[j] = (*saidas+j)->saida;
    }
  }  
    nucleo(camada, size_camada);


}

void nucleo(Neuronio**neuronio, int size){
  double aux;
  for(int i = 0; i < size; i++){
    aux = somatorio((*neuronio+i), size);
    (*neuronio+i)->saida = f(aux +(*neuronio+i)->b);
  }
}

double somatorio(Neuronio*entradas, int size){
  double soma = 0;
  for(int i = 0; i < size; i++){
    soma += entradas->entrada[i] * entradas->w[i];
  }
  
  return soma;
}

double f(double n){
  double saida;
  saida = 1.0/(1.0+pow(M_E,-n));
  return saida;
}

void back_propagation(Neuronio**camada_entrada, Neuronio**camada_oculta, Neuronio**camada_saida, int error, int nmr_neuronio, int index, double *entradas){
 
  // Calcular gradientes de cada camada 
  
  double *gradiente_entrada, *gradiente_oculta, *gradiente_saida;
  gradiente_entrada = (double*)malloc(536*sizeof(double));
  gradiente_oculta  = (double*)malloc(nmr_neuronio*sizeof(double));
  gradiente_saida   = (double*)malloc(1*sizeof(double));
  
  *gradiente_saida = f_linha((*camada_saida)->saida) * error;
  
  for(int i = 0; i < nmr_neuronio; i++){
    gradiente_oculta[i] = f_linha((*camada_oculta+i)->saida) * *gradiente_saida * (*camada_saida)->w[i];
  }

  for(int i = 0; i < 536; i++){
    gradiente_entrada[i] = f_linha((*camada_entrada+i)->saida) * somatorio_oculta(gradiente_oculta, camada_oculta, nmr_neuronio, i);
  }

  // Alterar Sinapses e Vieses
  
  altera_sinapses_vieses(camada_saida, camada_oculta, 1, nmr_neuronio, gradiente_saida);
  altera_sinapses_vieses(camada_oculta, camada_entrada, nmr_neuronio, 536, gradiente_oculta);

  for(int i = 0; i < 536; i++){
    for(int j = 0; j < 536; j++){
      (*camada_entrada+i)->w[j] = (*camada_entrada+i)->w[j] + T_A * entradas[j];
    }
    (*camada_entrada+i)->b = (*camada_entrada+i)->b + T_A * gradiente_entrada[i];
  } 
  free(gradiente_entrada);
  free(gradiente_oculta);
  free(gradiente_saida);
}

void altera_sinapses_vieses(Neuronio**camada_atual, Neuronio**camada_anterior, int size_atual, int size_anterior, double *gradiente){
  for(int i = 0; i < size_atual; i++){
    for(int j = 0; j < size_anterior; j++){
      (*camada_atual+i)->w[j] = (*camada_atual+i)->w[j] + T_A * (*camada_anterior+j)->saida * gradiente[i];
    }
    (*camada_atual+i)->b = (*camada_atual+i)->b + T_A * gradiente[i];
  }
}

double somatorio_oculta(double *gradiente, Neuronio**camada, int nmr_neuronio, int index){
  double soma = 0;
  for(int i = 0; i < nmr_neuronio; i++){
    soma += gradiente[i] * (*camada+i)->w[index];
  }
  return soma;
}

double f_linha(double n){
  return(pow(M_E, n) / pow(1.0+pow(M_E, n), 2.0));
}

void testar_rede(double**entradas, int nmr_neuronio, Neuronio**camada_entrada, Neuronio**camada_oculta, Neuronio**camada_saida){
  int acerto = 0, falsa_aceitacao = 0, falsa_rejeicao = 0;
  for(int i = 0; i < 50; i++){
    inserir_camada_entrada(entradas[i], camada_entrada, 536);
    inserir_dados(camada_entrada, camada_oculta, nmr_neuronio, 536);
    inserir_dados(camada_oculta, camada_saida, 1, nmr_neuronio);
    if(i % 2 == 0){
      if((*camada_saida)->saida > 0.5){
        acerto++;
      }
      else{
        falsa_rejeicao++;
      }
    }
    else{
        if((*camada_saida)->saida <= 0.5){
        acerto++;
      }
      else{
        falsa_aceitacao++;
      }
    }
  }
  printf("Taxa de acerto = %lf\nTaxa de Falsa aceitacao = %lf\nTaxa de falsa rejeicao = %lf\n", acerto*2.0, falsa_aceitacao*2.0, falsa_rejeicao*2.0);
}
