/* Método da Bissecção */
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
    for (i = 0; i <= potencia; i++){
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
    a = fabs(a);                    //fabs() da math.h. Usada para módulo
    fprintf(out, " %.8f\n", a);

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
    int* coeficientes;          //vetor que armazena coeficientes da função. índice = potência de x do coeficiente
    double epsilon;             //precisão
    double a0;
    double b0;
    int potencia;               //armazena maior potência da função
    double fx;                  // f(x)
    double temp;
    double fa0, fb0;            //f(a0) e f(b0)
    double xk;                  // xk
    double parada;
    int i;
    int k = 0;
    int erro;
    
    FILE *out =  fopen("saida_bisseccao.txt", "w");
    
    printf("Digite a maior potência da função:\n");
    scanf("%d", &potencia);
    
    coeficientes = (int*)malloc(sizeof(int) * (potencia + 1));
    
    for (i=0; i<= potencia; i++){
        printf("Digite o coeficiente da potência %d\n", i);
        scanf("%d", &coeficientes[i]);
    }
    
    printf("Digite o epsolon:\n");
    scanf("%lf", &epsilon);
    
    printf("Digite o a0:\n");
    scanf("%lf", &a0);
    
    printf("Digite o b0:\n");
    scanf("%lf", &b0);
    
    fa0 = calcularFx(potencia, a0, coeficientes);
    fb0 = calcularFx(potencia, b0, coeficientes);
    
    fprintf(out, "k\t a\t\t b\t\t xk\t\t f(xk)\t\t ek\n");
    
    //Verifica se extremos do intervalo são raízes. Se não for entra no laço
    if(fa0 == 0){
        fprintf(out,"Raiz = a0 = %.8f\n", a0);
        return 0;
    }else if (fb0 == 0){
        fprintf(out, "Raiz = b0 = %.8f\n", b0);
        return 0;
    }else if (fb0 * fa0 > 0){
        fprintf(out, "ERRO: Intervalo inválido\n");
        return 0;
    }else if (fb0 * fa0 < 0){
        xk = (a0 + b0)/2;
        fx = calcularFx(potencia, xk, coeficientes);
        fprintf(out, "%d\t %.8f\t %.8f\t %.8f\t %.8f\n", k, a0, b0, xk, fx);
        
        while(parada != 1){
            
            if (fa0 * fx < 0){
                b0 = xk;
                xk = (a0 + xk) / 2;
                fb0 = calcularFx(potencia, b0, coeficientes);
                fx = calcularFx(potencia, xk, coeficientes);
                fprintf(out, "%d\t %.8f\t %.8f\t %.8f\t %.8f\t", k, a0, b0, xk, fx);
                erro = calcularParada(xk, b0, epsilon, out);
                parada = verificaParada(fx, erro, k);
                k++;
            
            }else if (fb0 * fx < 0){
                a0 = xk;
                xk = (b0 + xk)/2;
                fa0 = calcularFx(potencia, a0, coeficientes);
                fx = calcularFx(potencia, xk, coeficientes);
                fprintf(out, "%d\t %.8f\t %.8f\t %.8f\t %.8f\t", k, a0, b0, xk, fx);
                erro = calcularParada(xk, a0, epsilon, out);
                parada = verificaParada(fx, erro, k);
                k++;
            }else{
                fprintf(out, "ERRO\n");
                return 0;
            }
        }
    }
    return 0;
}