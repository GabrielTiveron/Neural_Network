#ifndef ILBP_H
#define ILBP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void cada_pixel(int **, double[512]); //Pegar cada pixel para redirecionar a outra função;
int media_vizinhos(int **, int, int); //Calcula a media dos 8 vizinhos do pixel;
int gera_matriz_normalizada(int *, int); //Gera matriz de 0s e 1s para ser rotacionada;
int reconhecer_ordens(int [9]); //Rotaciona matriz para ver a menor combinação


#endif
