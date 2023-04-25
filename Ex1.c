#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parâmetro do tamanho dos alunos. 
#define TAM_ALUNO 30
#define TAM_LISTA 50
#define FIM_FILA -1

typedef struct Aluno{
    int matricula;
    char nome[TAM_ALUNO];
    float n1;
    float n2;
    float nex;
    struct Aluno *proximo;
}Aluno;

typedef struct{
    Aluno *topo;
}Pilha;

void inicalzaPilha(Pilha *pilha){
    pilha->topo = NULL;
}

int ultimaMatricula(Aluno *atual){
    int i = 0;
    if(atual == NULL){
        return 0;
    }else{
        return (atual->matricula > (i = ultimaMatricula(atual->proximo)) ? atual->matricula : i);
    }
}

int contaAlunos(Aluno *atual){
    int conta = 0;
    while(atual != NULL){
        atual = atual->proximo;
        conta++;
    }
    return conta;
}

void insereAluno(Pilha *atual, int posicao, char *nomeN, float n1N, float n2N, float nexN){ // "...N" = N de Novo.
    if(contaAlunos(atual->topo) < 50){
        Aluno *auxP = malloc(sizeof(Aluno));
        strcpy(auxP->nome,nomeN);
        auxP->n1 = n1N;
        auxP->n2 = n2N;
        auxP->nex = nexN;
        if(atual->topo == NULL){
            auxP->matricula = 0;
            posicao = FIM_FILA;
        }
        else
            auxP->matricula = ultimaMatricula(atual->topo) + 1;
        if(posicao == FIM_FILA){
            auxP->proximo = atual->topo;
            atual->topo = auxP;
        }else{
            Aluno *ajuda = atual->topo;
            for(int i = 1; i < posicao-1 && ajuda->proximo != NULL; i++){
                ajuda = ajuda->proximo;                
            }
            auxP->proximo = ajuda->proximo;
            ajuda->proximo = auxP;
        }
    }
}

void deletaAluno(Pilha *atual, int id){
    if(atual->topo == NULL)
        return;
    Aluno *aux = atual->topo, *aux2;
    if (aux->matricula == id){
        aux = atual->topo;
        atual->topo = atual->topo->proximo;
        free(aux);
    }
    while(aux->proximo->matricula != id && id < contaAlunos(atual->topo)){
        aux = aux->proximo;
    }
    aux2 = aux->proximo;
    aux->proximo = aux2->proximo;
    free(aux2);
}

void limpaPilha(Pilha *pilha){
    Aluno *aux = pilha->topo, *aux2;
    while(aux != NULL){
        aux2 = aux;
        aux = aux->proximo;
        free(aux2);
    }
    pilha->topo = NULL;
}
// Procura valores por ID
float notaId(Aluno *atual, int id, int par){
    while(atual->matricula != id){
        if(atual->proximo == NULL)
            return -1;
        atual = atual->proximo;
    }
    switch (par){
    case 1:
        return atual->n1;
        break;
    case 2:
        return atual->n2;
        break;
    default:
        return atual->nex;
        break;
    }
}

char *nomeId(Aluno *atual, int id){
    while(atual->matricula != id){
        atual = atual->proximo;
    }
    return atual->nome;
}

float mediaId(Aluno *atual, int id){
    while(atual->matricula != id){
        if(atual->proximo == NULL)
            return -1;
        atual = atual->proximo;
    }
    return (atual->n1 + atual->n2 + atual->nex)/3;    
}

// Encontra os melhores e piores
void maiorNota(Aluno *atual, int par){
    int maior = 0;
    float notaI;
    if(atual == NULL)
        return;
    else{
        for (int i = 0; i < ultimaMatricula(atual); i++){
            if(notaId(atual,maior,par) <= (notaI = notaId(atual,i,par))){
                if(notaI == -1)
                    continue;
                else
                    maior = i;
            }
        }
        printf("Maior nota %s: %s com %0.2f\n",(par == 1 ? "1" : (par == 2 ? "2" : "de Exercício")), nomeId(atual, maior), notaId(atual, maior, par));
    }
}

void menorNota(Aluno *atual, int par){
    int menor = 0;
    float notaI;
    if(atual == NULL)
        return;
    else{
        for (int i = 0; i < ultimaMatricula(atual); i++){
            if(notaId(atual,menor,par) >= (notaI=notaId(atual,i,par))){
                if(notaI == -1)
                    continue;
                else
                    menor = i;
            }
        }
        printf("Menor nota %s: %s com %0.2f\n",(par == 1 ? "1" : (par == 2 ? "2" : "de Exercício")), nomeId(atual, menor), notaId(atual, menor, par));
    }
}

void maiorGeral(Aluno *atual){
    int maior = 0;
    float mediaI;
    if(atual == NULL)
        return;
    else{
        for (int i = 0; i < ultimaMatricula(atual); i++){
            if( mediaId(atual, maior) < (mediaI=mediaId(atual, i))){
                if(mediaI == -1)
                    continue;
                else
                    maior = i;
            }
        }
        printf("Maior nota geral: %s com %0.2f\n", nomeId(atual, maior), mediaId(atual, maior));
    }
}

void menorGeral(Aluno *atual){
    int menor = 0;
    float mediaI;
    if(atual == NULL)
        return;
    else{
        for (int i = 0; i < ultimaMatricula(atual); i++){
            if( mediaId(atual, menor) > (mediaI=mediaId(atual, i))){
                if(mediaI == -1)
                    continue;
                else
                    menor = i;
            }
        }
        printf("Maior nota geral: %s com %0.2f\n", nomeId(atual, menor), mediaId(atual, menor));
    }
}

// Printa as listas
void printaLista(Aluno *atual){
    if(atual == NULL){
        printf("\nNão há alunos cadastrados...\n\n");
        return;
    }
    
    printf("|%3d|%30s|%0.2f|%0.2f|%0.2f|\n",atual->matricula,atual->nome,atual->n1,atual->n2,atual->nex);
    if(atual->proximo != NULL){
        printaLista(atual->proximo);
    }
}

void printaListaAprovacao(Aluno *atual){
    if(atual == NULL){
        printf("\nNão há alunos cadastrados...\n\n");
        return;
    }

    float media = mediaId(atual,atual->matricula);
    printf("|%3d|%30s|Média: %0.2f|%11s|\n",atual->matricula,atual->nome, media, (media >= 5.0 ? "Aprovado/a" : "Reprovado/a"));
    if(atual->proximo != NULL){
        printaListaAprovacao(atual->proximo);
    }
}

int main(){
    Pilha pilha;
    inicalzaPilha(&pilha);

    Aluno auxMain;
    int entradas = 0;
    printf("Quantidade de entradas:");
    if(scanf("%d", &entradas) != 1 || entradas >= TAM_LISTA){
        printf("Erro!!\nValor invalido...");
        exit(1);
    }
    for(int i = 1; i < entradas + 1; i++){
        printf("\n- Aluno %d -\nNome:", i);
        scanf("%s", auxMain.nome);
        printf("Nota 1: ");
        scanf("%f", &auxMain.n1);
        printf("Nota 2: ");
        scanf("%f", &auxMain.n2);
        printf("Nota Ex.: ");
        scanf("%f", &auxMain.nex);
        insereAluno(&pilha, FIM_FILA, auxMain.nome, auxMain.n1, auxMain.n2, auxMain.nex);
    }
    
    insereAluno(&pilha, FIM_FILA,"Mariazinha",6,7,4.5);
    insereAluno(&pilha, FIM_FILA,"Julinha",9,8,8);
    insereAluno(&pilha, 2,"Matheuzinho",10,2,5.5);
    insereAluno(&pilha, FIM_FILA,"Gabizinha",6,6.2,4.5);
    insereAluno(&pilha, FIM_FILA,"Thiaguinho",1,1,1);
    insereAluno(&pilha, 3,"Zezinho",0,0,0);
    
    deletaAluno(&pilha, 2);
    
    printf("\nA Sala foi populada para demonstrar...\nQtd de alunos: %d\n\n", contaAlunos(pilha.topo));

    //Teste do delete

    //Demonstração das funções
    printaLista(pilha.topo);
    putchar('\n');

    maiorNota(pilha.topo, 1);
    menorNota(pilha.topo, 1);
    maiorGeral(pilha.topo);
    menorGeral(pilha.topo);
    putchar('\n');

    printaListaAprovacao(pilha.topo);
    putchar('\n');

    printf("Limpando pilha...\n");
    limpaPilha(&pilha);
    putchar('\n');
    printaLista(pilha.topo);
    
}