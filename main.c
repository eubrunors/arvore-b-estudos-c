#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDEM 4 // Maximum degree of the B-tree

struct BTreeNo {
    int qtd_chaves; // Number of keys currently in the node
    int chaves[ORDEM-1]; // Array of keys
    struct BTreeNo *filho[ORDEM]; // Array of child pointers
    bool eh_folha; // True if node is a leaf
};
// Function to create a new node
struct BTreeNo *criaNo(bool eh_folha)
{
    struct BTreeNo *novoNo = (struct BTreeNo *)malloc(sizeof(struct BTreeNo));
    novoNo->qtd_chaves = 0;
    novoNo->eh_folha = eh_folha;
    for (int i = 0; i < ORDEM; i++) {
        novoNo->filho[i] = NULL;
    }
    return novoNo;
}
void insere(struct BTreeNo **raiz,int chave){
    struct BTreeNo *no = *raiz;
    //INSERINDO EM NO RAIZ
    if(no==NULL){
        *raiz = criaNo(true);
        (*raiz)->chaves[0] = chave;
        (*raiz)->qtd_chaves = 1;
    }else{
        //SPLIT DE RAIZ
        if(no->qtd_chaves==ORDEM-1){
            struct BTreeNo *novaRaiz = criaNo(false);
            novaRaiz->filho[0] = no;
            splitFilho(novaRaiz,0);
            *raiz = novaRaiz;
        }
        //INSERIR EM NO NAO LOTADO
        insereNaoCheio(*raiz,chave);
    }
}
void splitFilho(struct BTreeNo *pai, int indice) {
    struct BTreeNo *filho = pai->filho[indice];
    struct BTreeNo *novoNo = criaNo(filho->eh_folha);

    int meio = ORDEM / 2;  // Ex: ORDEM = 4 → meio = 2

    // novoNo recebe as chaves da metade direita do filho
    novoNo->qtd_chaves = ORDEM / 2 - 1;  // 1 chave para novoNo

    for (int j = 0; j < novoNo->qtd_chaves; j++) {
        novoNo->chaves[j] = filho->chaves[j + meio];
    }

    // se não for folha, copia os filhos correspondentes
    if (!filho->eh_folha) {
        for (int j = 0; j < ORDEM / 2; j++) {
            novoNo->filho[j] = filho->filho[j + meio];
        }
    }

    // Reduz a quantidade de chaves do nó original
    filho->qtd_chaves = ORDEM / 2 - 1;

    // Move os ponteiros de filhos no pai para abrir espaço para o novo filho
    for (int j = pai->qtd_chaves; j >= indice + 1; j--) {
        pai->filho[j + 1] = pai->filho[j];
    }
    pai->filho[indice + 1] = novoNo;

    // Move as chaves no pai para abrir espaço para a chave do meio
    for (int j = pai->qtd_chaves - 1; j >= indice; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[indice] = filho->chaves[meio - 1];  // chave do meio sobe

    pai->qtd_chaves++;
}
void insereNaoCheio(struct BTreeNo *no, int chave){
    int i = no->qtd_chaves-1;
    if(no->eh_folha){
        while(i>=0 && no->chaves[i] > chave){
            no->chaves[i+1]=no->chaves[i];
            i--;
        }
        no->chaves[i+1]=chave;
        no->qtd_chaves++;
    }
    else {
        // Descobrir qual filho descer
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;  // filho[i] é o destino

        if (no->filho[i]->qtd_chaves == ORDEM - 1) {
            splitFilho(no, i);

            if (chave > no->chaves[i]) {
                i++;
            }
        }

        // Desce no filho correto (agora garantidamente não cheio)
        insereNaoCheio(no->filho[i], chave);
    }
}
void traverse(struct BTreeNo *no) {
    if (no == NULL) return;

    int i;
    for (i = 0; i < no->qtd_chaves; i++) {
        // Primeiro percorre o filho antes da chave
        if (!no->eh_folha) {
            traverse(no->filho[i]);
        }

        // Imprime a chave
        printf("%d ", no->chaves[i]);
    }

    // Após a última chave, percorre o último filho
    if (!no->eh_folha) {
        traverse(no->filho[i]);
    }
}

int main()
{
    struct BTreeNo *raiz = NULL;

    insere(&raiz, 10);
    insere(&raiz, 20);
    insere(&raiz, 5);
    insere(&raiz, 6);
    insere(&raiz, 12);
    insere(&raiz, 30);

    printf("In-order traversal of the B-tree: ");
    traverse(raiz);
    printf("\n");

    return 0;
}
