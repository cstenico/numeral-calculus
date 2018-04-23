/* Método de Newton */
/*
 Autores:
 Camila Stenico dos Santos
 Octávio Oliveira Iozzi
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXINT 100


/*Função que retorna o valor de f(x)
 Parâmetros:
 potencia: número da maior potência da função
 x: valor do ponto que será calculado f(x)
 coeficientes: vetor com os coeficientes da função, onde o índice equivale a potência de x
 
 Retorna: f(x)
 */
double calcularFx(int potencia, double x, int *coeficientes){
    double fx = 0;
    int i;
    for (i = 0; i < potencia; i++){
        fx = fx + pow(x, i) * coeficientes[i];
    }
    return fx;
}

/*Função que verifica se condição de parada baseado no erro relativo |xk − xk−1| < ε·max{1,|xk|}.
 Parâmetros:
 xk = equivale ao ponto atual
 x0 = equivale ao ponto xk-1
 epsilon = precisão escolhida
 out: arquivo onde será escrito o valor de ek
 
 Retorno:
 0, se não for atingida condição de parada
 1, se for atingida condição de parada
 */

int calcularParada(double xk, double x0, double epsilon, FILE *out){
    double a = xk - x0;
    a = fabs(a);
    fprintf(out, "%.8f\n", a);
    
    double b; //max{1, |xk|}
    xk = fabs(xk);
    
    if( 1.0 > xk){
        b = 1.0;
    }else{
        b = xk;
    }
    
    if(b < a*epsilon){
        return 1;
    }else{
        return 0;
    }
    
}

int verificaParada (double fx, int erro, int k){
    if(fx < 0.000001 && fx > -0.000001){
        return 1;
    }
    if(erro == 1){
        return 1;
    }
    if(k == MAXINT){
        return 1;
    }
    return 0;
}

int main(void){
    int* coeficientes;              //vetor que armazena coeficentes da função. índice equivale a potência de x do coeficiente
    int* coeficientes_derivadas;    //vetor que armazena coeficentes da função derivada. índice equivale a potência de x do coeficiente
    double epsilon;                  //precisão
    int potencia;                   //armazena maior potência da função
    int i;
    int k = 0;
    int parada;
    int erro;
    
    FILE *out =  fopen("saida_newton.txt", "w");
    
    double xk;                       //xk
    double xk_1;                     //Xk-1
    double fx;                       //f(xk)
    double fx_1;                     //f(Xk-1)
    double dfx_1;                    //f'(xk-1)
    
    
    fprintf(out, "k\t xk\t\t f(xk)\t\t f'(xk)\t\t ek\n");
    
    printf("Digite o xk\n");
    scanf("%lf", &xk);
    
    printf("Digite o epsolon:\n");
    scanf("%lf", &epsilon);
    
    printf("Digite a maior potência da função:\n");
    scanf("%d", &potencia);
    
    coeficientes = (int*)malloc(sizeof(int) * (potencia + 1));
    coeficientes_derivadas = (int*)malloc(sizeof(int) * (potencia));
    
    for (i = 0; i<= potencia; i++){
        printf("Digite o coeficiente de x^%d\n", i);
        scanf("%d", &coeficientes[i]);
    }
    
    for (i = 0; i < potencia; i++){
        printf("Digite o coeficiente derivado de x^%d\n", i);
        scanf("%d", &coeficientes_derivadas[i]);
    }
    
    fx = calcularFx(potencia, xk, coeficientes);
    dfx_1 = calcularFx(potencia - 2, xk, coeficientes_derivadas);
    
    fprintf(out, "0\t  %.8f\t %.8f\t %.8f\n", xk, fx, dfx_1);

    if(fx == 0){
        fprintf(out, "Raiz é xk = %.8f\n", xk);
    }else{
        k++;
        while(fx != 0 && parada != 1 && k < MAXINT){
            xk_1 = xk;
            fx_1 = fx;
            dfx_1 = calcularFx(potencia - 1, xk_1, coeficientes_derivadas);
            xk = xk_1 - (fx_1 / dfx_1);
            fprintf(out, "%d\t %.8f\t %.8f\t %.8f\t", k, xk, fx, dfx_1);
            fx = calcularFx(potencia, xk, coeficientes);
            erro = calcularParada(xk, xk_1, epsilon, out);
            parada = verificaParada(fx, erro, k);
            k++;
        }
    }
    fclose(out);
    return 0;
}