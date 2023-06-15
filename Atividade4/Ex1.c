#include <stdio.h>
#include "ArvoreBinaria.h"

int main() {
    Raiz raiz;
    int qtdInp = 0, aux = 0;
    
    scanf("%d", &qtdInp);

    for(int i = 0; i < qtdInp; i++){
        scanf("%d", &aux);
        if(aux != 1 && i == 0)
            raiz = NULL;
        if(aux == 1 && i != 0)
            printf("Operacao invalida...Pulando Etapa");
        switch (aux){
        case 1:
            raiz = NULL;
            break;
        case 2:
            int x;
            scanf("%d", &x);
            printf("Demo:\n");
            adiciona(&raiz,x);
        case 3:
            imprimirArvore(raiz,0);
            break;
        case 4:
            imprimirEmOrdem(raiz);
            break;
        case 5:
            break;
        case 6:
            limparArvore(raiz);
            break;
        default:
            printf("Operacao invalida...Pulando Etapa\n");
            break;
        
        }
        printf("\n-----//-----\n");
    }
    return 0;
}