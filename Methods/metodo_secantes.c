/* Método das Secantes */
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
int calcularErro(double xk, double x0, double epsilon, FILE *out){
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
    
    a = a * epsilon;
    
    if(b < a){
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
    int* coeficientes;       //vetor que armazena coeficentes da função. índice equivale a potência de x do coeficiente
    double epsilon;          //precisão
    int potencia;
    int i;
    int k = 0;
    int parada;
    int erro;
    
    FILE *out = fopen("saida_secantes.txt", "w");
    
    double xk;              // xk
    double xk_1;            // Xk-1
    double xk_2;            // xk_2
    double fx;              // f(x)
    double fx_1;            // f(xk-1)
    double fx_2;            // f(xk-2)
    
    
    printf("Digite o xk\n");
    scanf("%lf", &xk);
    
    printf("Digite o xk-1\n");
    scanf("%lf", &xk_1);
    
    printf("Digite o epsilon:\n");
    scanf("%lf", &epsilon);
    
    printf("Digite a maior potência da função:\n");
    scanf("%d", &potencia);
    
    coeficientes = (int*)malloc(sizeof(int) * (potencia + 1));
    
    for (i = 0; i<= potencia; i++){
        printf("Digite o coeficiente de x^%d\n", i);
        scanf("%d", &coeficientes[i]);
    }
    
    fx = calcularFx(potencia, xk, coeficientes);
    fx_1 = calcularFx(potencia, xk_1, coeficientes);
    
    fprintf(out, "k\t xk\t\t f(xk)\t\t ek\n");
    
    k = 2;
    
    if(fx !=0.0 && fx_1 != 0.0){
        while(parada != 1){
            xk_2 = xk_1;
            xk_1 = xk;
            fx_2 = fx_1;
            fx_1 = fx;
            xk = (fx_1 * xk_2 - fx_2 * xk_1) / (fx_1 - fx_2);
            fx = calcularFx(potencia, xk, coeficientes);
            fprintf(out, "%d\t %.8f\t %.8f\t ", k, xk, fx);
            erro = calcularErro(xk, xk_1, epsilon, out);
            parada = verificaParada(fx, erro, k);
            k++;
        }
        return 0;
    }else if(fx == 0){
        fprintf(out, "Raiz é xk-1 = %.8f\n", xk);
        return 0;
    }else if(fx_1 == 0){
        fprintf(out, "Raiz é xk-2 = %.8f\n", xk_1);
        return 0;
    }
    fprintf(out, "ERRO\n");
    return 0;
}