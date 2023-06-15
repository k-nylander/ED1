#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct FILA{
    struct FILA *anterior;
    char pecas[4];
    struct FILA *proximo;
}FILA;

void iniciaFila(FILA *fila){
    fila->anterior = NULL;
    strcpy(fila->pecas,"FACE");
    fila->proximo = NULL;
}

bool verificaElemento(FILA *fila){
    int i=0, j=3;
    bool flag = false;
    
     while(fila->pecas[i++] == fila->anterior->pecas[j--])        
        if(i == 3 && j == 0)
            flag = true;
    return flag;
}

int adicionaElemento(FILA *fila, char input[4]){
    FILA *aux = malloc(sizeof(FILA));

    while(fila->proximo != NULL)
        fila = fila->proximo;

    fila->proximo = aux;
    aux->anterior = fila;
    strcpy(aux->pecas, input);
    aux->proximo = NULL;
    
    if(verificaElemento(aux)){
        if(aux->anterior->anterior != NULL){
            aux = aux->anterior->anterior;
            free(aux->proximo->proximo);
            free(aux->proximo);
            aux->proximo = NULL;
        }
        else{
            aux = aux->anterior;
            free(aux->proximo);
            iniciaFila(aux);

        }
        return 1;
    }
    return 0;

}

void printLista(FILA *fila){
    while (fila != NULL){
        printf("%s ",fila->pecas);
        fila = fila->proximo;
    }
    putchar('\n');    
}
int main(){
    FILA inicio;
    int qtd, soma = 0;
    char input[4];
    
    iniciaFila(&inicio);

    printf("Quantidade de entradas: ");
    scanf("%d", &qtd);
    if(qtd > 100){
        printf("Valor inválido...");
        return 1;
    }

    for(int i = 0; i < qtd; i++){
        scanf("%s", input);
        soma += adicionaElemento( &inicio, input);
    }
    printf("%d\n\n", soma);
    return 0;
}