#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto{
    char produto[50];
    int preço;
    int quantidade;
};

void realoca(struct Produto **estoque, int n){
    //realoca pra caber n structs Produto
    *estoque = realloc(*estoque, n*sizeof(struct Produto));
}

//recebe o endereço do ponteiro que aponta pro vetor de structs e o tamanho
void insereProduto(struct Produto **estoque, int *n){
    //incrementa o tamanho
    *n++;
    //realoca pro tamanho maior
    realoca(estoque, *n);
    

    scanf(" %s", (*estoque)[*n-1].produto);
    scanf("%d", (*estoque)[*n-1].quantidade);
    scanf("%d", (*estoque)[*n-1].preço);
    
}

void consultaCaixa(int n){
    printf("Saldo: %d\n", n);
}


void consultaEstoque(struct Produto **estoque, int n){

    for(int i =0; i<n; i++){
        printf("%d %s %d\n", i, (*estoque)[i].produto, (*estoque)[i].quantidade);
    }


}



int main(){
    struct Produto *estoque = NULL;
    int tamanho=0;
    int caixa=0;

    //passa endereço do estoque e o tamanho atual
    insereProduto(&estoque, &tamanho);


    return 0;
}