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
void insere(**raiz, chave){
    struct BTreeNo *no = *raiz
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
        insereNaoCheio(*raiz,cahve);
    }
}
void splitFilho(struct BTreeNo *pai,int indice){
    struct BTreeNo *filho = pai->filho[indice];
    struct BTreeNo *novoNo = criaNo(filho->eh_folha);

    int meio=ORDEM/2;

    novoNo->qtd_chaves = ORDEM/2-1;//1 CHAVE PRO NOVATO

    for(int i=0, i<ORDEM/2-1; i++){
        novoNo->chaves[i]=filho->chaves[i+ORDEM/2];
    }
    if(!filho->is_leaf){
        //SE FILHO NAO FOR FOLHA
        for (int j = 0; j < ORDEM / 2; j++) {
            novoNo->filho[j] = filho->filho[j + meio];
        }
    }
    // Reduz a quantidade de chaves do nó original
    filho->qtd_chaves=ORDEM/2-1;


    pai->filho[indice+1]=novoNo;


    pai->chaves[indice]=filho->chaves[meio-1];

    pai->qtd_chaves++;
}

int main()
{
    struct BTreeNode *raiz = NULL;

    insert(&raiz, 10);
    insert(&raiz, 20);
    insert(&raiz, 5);
    insert(&raiz, 6);
    insert(&raiz, 12);
    insert(&raiz, 30);

//    printf("In-order traversal of the B-tree: ");
//    traverse(raiz);
//    printf("\n");

    return 0;
}
