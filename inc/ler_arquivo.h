#ifndef LER_ARQUIVO_H
#define LER_ARQUIVO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"./ilbp.h"
#include"./auxiliar.h"
#include"./glcm.h"
#define BASE_ASFALTO "../dataset/asphalt/asphalt_"
#define BASE_GRAMA "../dataset/grass/grass_"
#define EXTENSAO ".txt\0"

// char ** montar_arquivos(int *, char *);
void montar_arquivo(char**,int , char *);
void sortear_casos(int*);
void gerar_vetores(int**, int, int, double*);
void ler_imagens(char*, int**);


#endif
