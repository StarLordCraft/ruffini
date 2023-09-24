#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

typedef struct tgMetodoRuffini {
    char  *dividendo;           //- Dividendo
    char  *divisor;               //- Divisor
    int  constDivisor;        //- Termo constante do divisor
    int  constDividendo;    //- Termo constante do dividendo
    int  *coefDividendo;  //- Coef. do dividendo (a)x + bx
    int  numCoefficients;
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
    // Regular expression for finding coefficients in the dividend string
    const char *pattern = "[+-]?[0-9]*x";

    regex_t regex;
    regmatch_t match;

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex pattern\n");
        return;
    }

    char *str = p->dividendo;

    int size = 0;
    while (regexec(&regex, str, 1, &match, 0) == 0) {
        // Extract the matched coefficient
        char *match_str = str + match.rm_so;

        // If the coefficient is empty, assume it's 1
        int coef = (match_str[0] == '+' || match_str[0] == '-') ? atoi(match_str) : 1;

        // Add the coefficient to your data structure
        ++size;
        p->coefDividendo = (int *)realloc(p->coefDividendo, size * sizeof(int));
        p->coefDividendo[size - 1] = coef; p->numCoefficients = size;

        // Move to the next part of the string
        str += match.rm_eo;
    }

    regfree(&regex);
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

    for (int i = 0; i < polinomios.numCoefficients; ++ i) printf("%d\n", polinomios.coefDividendo[i]);
}