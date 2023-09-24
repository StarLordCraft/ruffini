#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tgMetodoRuffini {
    char  *dividendo;           //- Dividendo
    char  *divisor;               //- Divisor
    int  constDivisor;        //- Termo constante do divisor
    int  constDividendo;    //- Termo constante do dividendo
    int  *coefDividendo;  //- Coef. do dividendo (a)x + bx
} DivisaoRuffine;

void carregaConstantes(DivisaoRuffine *p) 
{
    int i = strlen(p->divisor - 1);
    while(!isdigit(p->divisor[i]))
        --i;
    p->constDivisor = atoi(&p->divisor[i]);
    
    i = strlen(p->dividendo - 1);
    while(!isdigit(p->dividendo[i]))
        --i;
    p->constDividendo = atoi(&p->dividendo[i]);
}

void carregaCoeficientes(DivisaoRuffine *p) 
{
    char *num;
    int inicio = 0, fim = 0, size = 0;
    for(int i = 0; i < strlen(p->divisor); ++i){
        if(('x' == p->dividendo[i] || 'X' == p->dividendo[i])){
            fim = i - 1;
            for(int k = fim; k > strlen(p->divisor); --k)
                if( '-' == p->dividendo[k] || '+' == p->dividendo[k]){
                    inicio = k; break;   
                };
            for(int j = inicio; j != fim; ++j)num+=p->dividendo[j];
            
            ++size;
            p->coefDividendo = (int *)realloc(p->coefDividendo, size * sizeof(int));
            p->coefDividendo[size - 1] = atoi(num);
        }
    } 
}

void calcula(DivisaoRuffine *p) 
{

}

void metodoRuffini(DivisaoRuffine *p) 
{
    carregaConstantes(p);
    carregaCoeficientes(p);
    calcula(p);
}

int main ()
{
    DivisaoRuffine polinomios = { "x^2+4x+3", "x+1" };

    metodoRuffini(&polinomios);

    printf("Constante do Dividendo: %d\n", polinomios.constDividendo);
    printf("Constante do Divisor: %d\n", polinomios.constDivisor);
}