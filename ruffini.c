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
} DivisaoRuffini;


/// @param p é o endereço de memória que a expressão está
/// @return void
/* 
-- O que essa função faz:
- Input: Recebe a exŕessão
- Procces por meio de regex deve extrair e armazenar corretamente os coeficientes do polinômio
*/   
void carregaCoeficientes(DivisaoRuffini *p) 
{
    const char *pattern = "([+-]?[0-9]*x\\^[0-9]+|[+-]?[0-9]*x|[+-]?[0-9]+)";
    
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex pattern\n");
        return;
    }

    char *str = p->dividendo;
    int size = 0;
    
    while (regexec(&regex, str, 1, &match, 0) == 0) {
        char *match_str = str + match.rm_so;
    
        // Pegando coeficiente implicito como x que tem coeficiente 1 implicito
        int coef = (isdigit(match_str[0]) || (('+' == match_str[0] || 
        '-' == match_str[0]) && isdigit(match_str[1]))) ? atoi(match_str) : 1;

        ++size;
        p->coefDividendo = (int *)realloc(p->coefDividendo, size * sizeof(int));
        p->coefDividendo[size - 1] = coef;
        p->numCoefficients = size;

        str += match.rm_eo;
    }

    regfree(&regex);
}


/// @param p é o endereço de memória que a expressão está
/// @return void
/* 
-- O que essa função faz:
- Input: Recebe a expressão com coeficientes processados
- Deve aplicar o método de briot Ruffini pra retornar o quociente e resto da divisão
- 2 arrays resultado e coefDividendo 
*/  
void calcula(DivisaoRuffini *p) 
{
    if (p->coefDividendo == NULL || p->numCoefficients == 0) {
        printf("No coefficients loaded for division.\n");
        return;
    }

    int n = p->numCoefficients;
    int *resultado = (int *)malloc(n * sizeof(int));

    resultado[0] = p->coefDividendo[0];

    for (int i = 1; i < n; ++i)
        // - propositalmente o resultado[i] corresponde a coefDividendo[1 + i] para simplificar o for.
        // - Isso se você considerar briot Ruffini padrão
        resultado[i] = (resultado[i - 1] * p->constDivisor) + p->coefDividendo[i];
    

    printf("Resultado dos coeficientes da divisao:\n");
    for (int i = 0; i < n - 1; ++i) {
        if(i < n - 2)
            if(resultado[i] > 0 && i < n - 3) printf("%dx^%d + ", resultado[i], (n - 2 - i));
            else printf("%dx^%d", resultado[i], (n - 2 - i));
        else 
        if(resultado[i] > 0)printf(" + %d", resultado[i]);
        else printf("%d", resultado[i]);
    }
    printf("\n\nResto da divisao: %d\n\n", resultado[n - 1]);
    free(resultado); free(p->coefDividendo);
}

void metodoRuffini(DivisaoRuffini *p) 
{
    carregaCoeficientes(p);
    calcula(p);
}

int main(int argc, char **argv) 
{
    char *exprr = NULL;
    char caractere;
    int tamanho = 0;

    printf("Digite o polinomio que deseja dividir:\n");
    while((caractere = getchar()) != '\n'){
        if(' ' == caractere)continue;
        ++tamanho;
        exprr = realloc(exprr, tamanho * sizeof(char));
        exprr[tamanho - 1] = caractere;
    }

    int divisor = 0;
    printf("Digite o numero que dividira o polinomio:\n");
    scanf("%d", &divisor);
    
    DivisaoRuffini polinomios = { 
        exprr,
        divisor,
        NULL,
        0
    };

    metodoRuffini(&polinomios);
    free(exprr);
    return 0;
}
