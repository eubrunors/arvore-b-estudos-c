#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ordem 4 // Maximum degree of the B-tree

struct BTreeNo {
    int qtd_chaves; // Number of keys currently in the node
    int chaves[ordem-1]; // Array of keys
    struct BTreeNo *filho[ordem]; // Array of child pointers
    bool eh_folha; // True if node is a leaf
};
// Function to create a new node
struct BTreeNo *criaNo(bool eh_folha)
{
    struct BTreeNo *novoNo = (struct BTreeNo *)malloc(sizeof(struct BTreeNo));
    novoNo->qtd_chaves = 0;
    novoNo-> = eh_folha;
    for (int i = 0; i < M; i++) {
        novoNo->filho[i] = NULL;
    }
    return novoNo;
}
void insere(**raiz, chave){
    struct BTreeNo *no = *raiz
    if(no==NULL){
        *raiz = criaNo(true);
        (*raiz)->chaves[0] = chave;
        (*raiz)->qtd_chaves = 1;
    }
}

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
