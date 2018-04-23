//
//  metedo_lagrange.c
//  
//
//  Created by Camila Stenico on 10/11/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 54
//#define x 2020.0

int main(void){
    double * x;
    double * y;
    
    double s=1,t=1,k=0;
    double a = 2020.0;

    char c;
    
    int i, j, n, q;

    char leitura[15];

    
    FILE *pontos;
    
    pontos = fopen("pontos.txt", "r");
    
    x = (double*)malloc(sizeof(double)* N);
    y = (double*)malloc(sizeof(double)* N);
    
    i = 0;
    while(!feof(pontos)){
        //fread(c, 1, sizeof(char), pontos);
        c = fgetc(pontos);
        if(c != ',' && c!= '\n'){
            leitura[i] = c;
            i++;
        }else if(c == ','){
            x[j] = atof(leitura);
            for(q = 0; q < 15; q++){
                leitura[q] = '\0';
            }
            i = 0;
            
        }else if(c == '\n'){
            y[j] = atof(leitura);
            j++;
            for(q = 0; q < 15; q++){
                leitura[q] = '\0';
            }
            i = 0;
            
        }
    }
    y[j] = atof(leitura);

    
    //trecho da net
    for(i=0; i<n; i++)
    {
        s=1;
        t=1;
        for(j=0; j<n; j++)
        {
            if(j!=i)
            {
                s=s*(a-x[j]);
                t=t*(x[i]-x[j]);
            }
        }
        k=k+((s/t)*y[i]);
    }
    printf("\n\nThe respective value of the variable y is: %f\n",k);
    
    return 0;
}