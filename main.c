/*Este programa tem como objetivo a criação de um sistema de controle de estoque e caixa para um mercadinho.
O sistema deve ser capaz de realizar consultas de saldo, estoque, incluir novos produtos, realizar vendas*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//prototipagem das funções
void realoca(struct Produto **estoque, int n);
void aloca(struct Produto **estoque, int n);
void insereProduto(struct Produto **estoque, int *tamanho, int *posicao);
void consultaCaixa(int n);
void consultaEstoque(struct Produto **estoque, int n);

struct Produto{
    char produto[50];
    int preço;
    int quantidade;
};

/// @brief função que realoca para um espaço de memória maior
/// @param estoque ponteiro para o vetor que deve ser realocado
/// @param n tamanho para o qual deve ser realocado
void realoca(struct Produto **estoque, int n){
    //realoca pra caber n structs Produto
    *estoque = realloc(*estoque, n*sizeof(struct Produto));
    if(*estoque == NULL){
        printf("Sem memória");
        exit(1);
    }
}

/// @brief função que realoca um espaço de memória para um ponteiro
/// @param estoque ponteiro para o array que será alocado
/// @param n tamanho do espaço de memória alocado
void aloca(struct Produto **estoque, int n){
    //realoca pra caber n structs Produto
    *estoque = malloc(n*sizeof(struct Produto));

     if(*estoque == NULL){
        printf("Sem memória");
        exit(1);
    }
    
}

/// @brief = função que insere uma nova struct ao fim de um vetor de structs
/// @param estoque = ponteiro para o vetor que armazena as structs de produtos
/// @param tamanho = tamanho do vetor
/// @param posicao = posição da ultima struct inserida no vetor
void insereProduto(struct Produto **estoque, int *tamanho, int *posicao){
    
    if(*posicao >= *tamanho){
        
        //se a posição alcançar o tamanho do vetor, realoca pro dobro do tamanho
        (*tamanho)+=(*tamanho);
        //realoca pro tamanho maior
        realoca(estoque, *tamanho);
    }
    
    //incrementa a posicao final do vetor
    (*posicao)++;
    //le e insere um novo produto;
    scanf(" %s", (*estoque)[(*posicao)].produto);
    scanf("%d", &(*estoque)[(*posicao)-1].quantidade);
    scanf("%d", &(*estoque)[(*posicao)-1].preço);
    
}
/// @brief = função que imprime o saldo do caixa
/// @param n = valor acumulado do caixa
void consultaCaixa(int n){
    printf("Saldo: %d\n", n);
}


/// @brief = função que percorre o vetor de structs e imprime codigo, nome e quantidade
/// @param estoque = ponteiro para o vetor que armazena as structs de produtos
/// @param n = tamanho do vetor
void consultaEstoque(struct Produto **estoque, int n){

    for(int i =0; i<n; i++){
        printf("%d %s %d\n", i, (*estoque)[i].produto, (*estoque)[i].quantidade);
    }


}



int main(){
    struct Produto *estoque = NULL;
    //para o caso de não existir arquivo e ser lido um tamanho >0 do terminal
    //nesse caso teriamos tamanho 4, mas nenhum item ainda inserido, o que causaria erro nos indices
    int posicao=0;
    int tamanho=0;
    int caixa=0;
    FILE *fp;

    //precisamos fazer a parte que tenta ler do arquivo ou do terminal. AO final desta parte, teremos
    //tamanho e caixa atualizados. Assim, podemos alocar o espaço para o estoque.
    fp = fopen("estoque.bin", "r");
        if(fp == NULL){
            scanf("%d", &tamanho);
            scanf("%d", &caixa);
            //aloca o vetor estoque do tamanho necessário
            aloca(&estoque, tamanho);
        }
        
        else{
            fscanf("%d", &tamanho);
            fscanf("%d", &caixa);
           
            //aloca o vetor estoque do tamanho necessário
            aloca(&estoque, tamanho);

            //função que vai percorrer o arquivo lendo os itens e colocando no vetor
            leEstoque(fp, tamanho);
        }


    //passa endereço do estoque e o tamanho atual. Passando o tamanho por referência pq sempre vamos
    //incrementar, ai já fazemos isso na função pra deixar limpo
    insereProduto(&estoque, &tamanho, &posicao);

    consultaEstoque(&estoque, posicao);

    consultaCaixa(caixa);


    return 0;
}