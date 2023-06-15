#include <stdlib.h>

typedef struct ramo {
    int no;
    struct ramo* Esq;
    struct ramo* Dir;
} Ramo;

typedef Ramo* Raiz;

Ramo* inicializa(int valor) {
    Ramo* novo = malloc(sizeof(Ramo));
    novo->Dir = NULL;
    novo->Esq = NULL;
    novo->no = valor;
    return novo;
}

void adiciona(Ramo** ramoAtual, int valor) {
    if (*ramoAtual == NULL) {
        *ramoAtual = inicializa(valor);
        return;
    }

    if (valor > (*ramoAtual)->no) {
        adiciona(&((*ramoAtual)->Dir), valor);
    } else {
        adiciona(&((*ramoAtual)->Esq), valor);
    }

    balanceia(ramoAtual);
}

void balanceia(Ramo** ramoAtual) {
    if (*ramoAtual == NULL) {
        return;
    }

    int alturaEsq = altura((*ramoAtual)->Esq);
    int alturaDir = altura((*ramoAtual)->Dir);

    int balanceamento = alturaEsq - alturaDir;

    if (balanceamento > 1) {
        if (altura((*ramoAtual)->Esq->Esq) >= altura((*ramoAtual)->Esq->Dir)) {
            rotacaoDireita(ramoAtual);
        } else {
            rotacaoEsquerda(&((*ramoAtual)->Esq));
            rotacaoDireita(ramoAtual);
        }
    } else if (balanceamento < -1) {
        if (altura((*ramoAtual)->Dir->Dir) >= altura((*ramoAtual)->Dir->Esq)) {
            rotacaoEsquerda(ramoAtual);
        } else {
            rotacaoDireita(&((*ramoAtual)->Dir));
            rotacaoEsquerda(ramoAtual);
        }
    }
}

void rotacaoEsquerda(Ramo **ramoAtual) {
    Ramo* novoRamo = (*ramoAtual)->Dir;
    (*ramoAtual)->Dir = novoRamo->Esq;
    novoRamo->Esq = *ramoAtual;
    *ramoAtual = novoRamo;
}

void rotacaoDireita(Ramo **ramoAtual) {
    Ramo* novoRamo = (*ramoAtual)->Esq;
    (*ramoAtual)->Esq = novoRamo->Dir;
    novoRamo->Dir = *ramoAtual;
    *ramoAtual = novoRamo;
}

int altura(Ramo* raiz) {
    if (raiz == NULL)
        return 0;
    int altEsq = altura(raiz->Esq);
    int altDir = altura(raiz->Dir);
    return 1 + ((altEsq > altDir) ? altEsq : altDir);
}

void imprimirArvore(Ramo* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArvore(raiz->Dir, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    printf("%d\n", raiz->no);

    imprimirArvore(raiz->Esq, nivel + 1);
}

void limparArvore(Ramo* raiz) {
    if (raiz == NULL) {
        return;
    }

    limparArvore(raiz->Esq);
    limparArvore(raiz->Dir);

    free(raiz);
    printf("0");
}

void imprimirEmOrdem(Ramo* raiz) {
    if (raiz == NULL) {
        return;
    }

    imprimirEmOrdem(raiz->Esq);
    printf("%d ", raiz->no);
    imprimirEmOrdem(raiz->Dir);
}