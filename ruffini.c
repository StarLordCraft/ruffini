#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tgMetodoRuffini {
    char  *dividendo;           //- Dividendo
    char  *divisor;               //- Divisor
    int  constDivisor;        //- Termo constante do divisor
    int  constDividendo;    //- Termo constante do dividendo
    int  coefDividendoAx[];  //- Coef. do dividendo (a)x + bx
} DivisaoRuffine;

void carregaConstantes(DivisaoRuffine *p) {
    int i = strlen(p->divisor - 1);
    while(!isdigit(p->divisor[i]))
        --i;
    p->constDivisor = atoi(&p->divisor[i]);
    
    i = strlen(p->dividendo - 1);
    while(!isdigit(p->dividendo[i]))
        --i;
    p->constDividendo = atoi(&p->dividendo[i]);
}

void carregaCoeficientes(DivisaoRuffine *p) { }
void calcula(DivisaoRuffine *p) {}

void metodoRuffini(DivisaoRuffine *p) {
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