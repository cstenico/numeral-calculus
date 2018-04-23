//
//  mmq.c
//  
//
//  Created by Camila Stenico on 10/11/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>                           /* math functions                */

//#define REAL float
#define REAL double
#define N 54
#define banana 2020.0


inline static REAL sqr(REAL x) {
    return x*x;
}


int linreg(int n, const REAL x[], const REAL y[], REAL* m, REAL* b, REAL* r)
{
    REAL   sumx = 0.0;                        /* sum of x                      */
    REAL   sumx2 = 0.0;                       /* sum of x**2                   */
    REAL   sumxy = 0.0;                       /* sum of x * y                  */
    REAL   sumy = 0.0;                        /* sum of y                      */
    REAL   sumy2 = 0.0;                       /* sum of y**2                   */
    
    for (int i=0;i<n;i++)
    {
        sumx  += x[i];
        sumx2 += sqr(x[i]);
        sumxy += x[i] * y[i];
        sumy  += y[i];
        sumy2 += sqr(y[i]);
    }
    
    REAL denom = (n * sumx2 - sqr(sumx));
    if (denom == 0) {
        // singular matrix. can't solve the problem.
        *m = 0;
        *b = 0;
        *r = 0;
        return 1;
    }
    
    *m = (n * sumxy  -  sumx * sumy) / denom;
    *b = (sumy * sumx2  -  sumx * sumxy) / denom;
    if (r!=NULL) {
        *r = (sumxy - sumx * sumy / n) /          /* compute correlation coeff     */
        sqrt((sumx2 - sqr(sumx)/n) *
             (sumy2 - sqr(sumy)/n));
    }
    
    return 0;
}

int main()
{
    REAL *x; //= {1, 2, 4,  5,  10, 20};
    REAL *y; //[6]= {4, 6, 12, 15, 34, 68};
    
    char leitura[15];
    char c;
    
    FILE *pontos;
    
    pontos = fopen("pontos.txt", "r");
    
    x = (double*)malloc(sizeof(double)* N);
    y = (double*)malloc(sizeof(double)* N);
    int j = 0;
    int k;
    int i;
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
            x[j] = atof(leitura);
            for(k = 0; k < 15; k++){
                leitura[k] = '\0';
            }
            i = 0;
            
        }else if(c == '\n'){
            y[j] = atof(leitura);
            j++;
            for(k = 0; k < 15; k++){
                leitura[k] = '\0';
            }
            i = 0;
            
        }
    }

    
    REAL m,b,r, resultado;
    linreg(N,x,y,&m,&b,&r);
    printf("m=%g b=%g r=%g\n",m,b,r);
    resultado = m*banana + b;
    printf("Result is %f\n", resultado);
    
    
    return 0;
}

