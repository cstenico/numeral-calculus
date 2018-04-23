//
//  metodo_divisao_newton.c
//  
//
//  Created by Camila Stenico on 08/11/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 54
#define x 2020.0

int main(void){
    double * vetor_x;
    double * vetor_fx;
    double ** matriz_fx;
    char leitura[15];
    char c;
    double *vetor_newton;
    double pnx;
    double subtotal;
    int max;
    
    int i, j, k, gap;
    
    FILE *pontos;
    
    pontos = fopen("pontos.txt", "r");
    
    vetor_x = (double*)malloc(sizeof(double)* N);
    vetor_fx = (double*)malloc(sizeof(double)* N);
    vetor_newton = (double*)malloc(sizeof(double)* N);
    
    matriz_fx = (double**)malloc(sizeof(double*)* N);
    for(i = 0; i < N; i++){
        matriz_fx[i] = (double*)malloc(sizeof(double)* N);
    }
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            matriz_fx[i][j] = 0.0;
        }
    }
    
    j = 0;
    for(k = 0; k < 15; k++){
        leitura[k] = '\0';
    }
    i = 0;
    while(!feof(pontos)){
        //fread(c, 1, sizeof(char), pontos);
        c = fgetc(pontos);
        if(c != ',' && c!= '\n'){
            leitura[i] = c;
            i++;
        }else if(c == ','){
            vetor_x[j] = atof(leitura);
            for(k = 0; k < 15; k++){
                leitura[k] = '\0';
            }
            i = 0;

        }else if(c == '\n'){
            vetor_fx[j] = atof(leitura);
            j++;
            for(k = 0; k < 15; k++){
                leitura[k] = '\0';
            }
            i = 0;

        }
    }
    vetor_fx[j] = atof(leitura);
    
    //pontos foram lidos, portando as duas primeiras colunas da tabela estão prontas (vetor_x e vetor_fx).
     printf("--------------------------------------------------\n");
     printf("--------------------------------------------------\n");
    
    
    for(i = 0; i < N; i++){
        printf("%f\n", vetor_x[i]);
    }
    
    printf("--------------------------------------------------\n");
     printf("--------------------------------------------------\n");
     printf("--------------------------------------------------\n");
    
    for(i = 0; i < N; i++){
        printf("%f\n", vetor_fx[i]);
    }
     printf("--------------------------------------------------\n");
     printf("--------------------------------------------------\n");
    
    i = 0;
    j = 1;
    max = N;
    
    //primeira coluna da matriz
    for(j = 1; j < max; j++){
        matriz_fx[i][0] = (vetor_fx[j] - vetor_fx[i]) - (vetor_x[j] - vetor_x[i]);
        i++;
    }
    
    //montar matriz completa
    //k indica coluna
    //i e j são linhas
    
    i = 0;
    j = 0;
    max = N - 1;
    k = 1;
    gap = 2;
        
    while(max > 0){
        i = 0;
        j = 0;
        while(j + gap < N){
            matriz_fx[i][k] = (matriz_fx[i + 1][k-1] - matriz_fx[i][k-1])/(vetor_x[j+gap] - vetor_x[j]);
            j++;
        }
        gap++;
        k++;
        max--;
    }
    //tabela pronta
    //agora tem que fazer formula de newton
    // x = 2020
    
    vetor_newton[0] = 1.0;
    for(i = 1; i < N; i++){
        vetor_newton[i] = x - vetor_x[i];
    }
    
      printf("--------------------------------------------------\n");
    for(i = 0; i < N; i++){
        printf("%f\n", vetor_newton[i]);
    }
    
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    
    max = 1;
    pnx = 0.0;
    j = 0;
    while(max < N){
        subtotal = 1.0;
        for(i = 0; i < max; i++) {
            subtotal = vetor_newton[i] * subtotal ;
        }
        if(j == 0){
            subtotal = subtotal * vetor_fx[0];
        }else{
            subtotal = subtotal * matriz_fx[0][j];
        }
        pnx = pnx + subtotal;

        
        j++;
        max++;
        
    }
    
    printf("%f\n", pnx);
    
    return 0;
    
    
}