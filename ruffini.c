#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

typedef struct tgMetodoRuffini {
    char  *dividendo;           //- Dividendo
    int  constDivisor;        //- Termo constante do divisor
    int  *coefDividendo;  //- Coef. do dividendo (a)x + bx
    int  numCoefficients;
} DivisaoRuffine;

void carregaCoeficientes(DivisaoRuffine *p) 
{
    // Regular expression for finding coefficients and degrees in the dividend string
    const char *pattern = "([+-]?[0-9]*x\\^[0-9]+|[+-]?[0-9]*x|[+-]?[0-9]+)";
    
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
        // Extract the matched coefficient or degree
        char *match_str = str + match.rm_so;
        int coef = (isdigit(match_str[0]) || (('+' == match_str[0] || 
        '-' == match_str[0]) && isdigit(match_str[1]))) ? atoi(match_str) : 1;

        // Add the coefficient to your data structure
        ++size;
        p->coefDividendo = (int *)realloc(p->coefDividendo, size * sizeof(int));
        p->coefDividendo[size - 1] = coef;
        p->numCoefficients = size;

        // Move to the next part of the string
        str += match.rm_eo;
    }

    regfree(&regex);
}

void calcula(DivisaoRuffine *p) 
{
    if (p->coefDividendo == NULL || p->numCoefficients == 0) {
        printf("No coefficients loaded for division.\n");
        return;
    }

    int n = p->numCoefficients;
    int *resultado = (int *)malloc(n * sizeof(int));

    resultado[0] = p->coefDividendo[0];

    for (int i = 1; i < n; ++i) {
        resultado[i] = resultado[i - 1] * p->constDivisor;

        resultado[i] += p->coefDividendo[i];
    }

    printf("Resultado dos coeficientes da divisao:\n");
    for (int i = 0; i < n - 1; ++i) {
        if(i < n - 2)
            if(resultado[i] > 0 && i < n-2) printf("%dx^%d + ", resultado[i], (n - 2 - i));
            else printf("%dx^%d", resultado[i], (n - 2 - i));
        else printf("%d", resultado[i]);
    }
    printf("\n\nResto da divisao: %d\n\n", resultado[n - 1]);
    free(resultado);
}

void metodoRuffini(DivisaoRuffine *p) 
{
    carregaCoeficientes(p);
    calcula(p);
}

int main() 
{
    DivisaoRuffine polinomios = { 
        "3x^3-5x^2+x-2",
        2,
        NULL,
        0
    };

    metodoRuffini(&polinomios);
    return 0;
}
