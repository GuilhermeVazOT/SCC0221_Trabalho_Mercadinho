/*Este programa tem como objetivo a criação de um sistema de controle de estoque e caixa para um mercadinho.
O sistema deve ser capaz de realizar consultas de saldo, estoque, incluir novos produtos, realizar vendas, modificar preço e aumentar estoque.

O programa foi modularizado e a explicação detalhada de cada função ocorrerá no decorrer do código.

Autores: Catarina Moreira Lima - 8957221*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//prototipagem das funções
void realoca(struct Produto **estoque, int n);
void aloca(struct Produto **estoque, int n);
void insereProduto(struct Produto **estoque, int *tamanho, int *posicao);
void consultaCaixa(int n);
void consultaEstoque(struct Produto **estoque, int n);
void leEstoque(FILE *fp, struct Produto *estoque);

struct Produto{
    char produto[50];
    float preço;
    int quantidade;
    int codigo;
};

void leEstoque(FILE *fp, struct Produto *estoque){

        fscanf(fp, "%s", estoque->produto);
        fscanf(fp, "%.2f", &estoque->preço);
        fscanf(fp, "%d", &estoque->quantidade);
        fscanf(fp, "%d", &estoque->codigo);

}

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
    //le e insere um novo produto;
    scanf(" %s", (*estoque)[(*posicao)].produto);
    scanf("%d", &(*estoque)[(*posicao)].quantidade);
    scanf("%f", &(*estoque)[(*posicao)].preço);
    (*estoque)[(*posicao)].codigo=posicao;
    
    (*posicao)++;
    
}
/// @brief = função que imprime o saldo do caixa
/// @param n = valor acumulado do caixa
void consultaCaixa(int n){
    printf("Saldo: %.2f\n", n);

    for(int i = 0; i<50; i++){
        printf("-");
    }
    printf("\n");
}


/// @brief = função que percorre o vetor de structs e imprime codigo, nome e quantidade
/// @param estoque = ponteiro para o vetor que armazena as structs de produtos
/// @param n = tamanho do vetor
void consultaEstoque(struct Produto **estoque, int n){

    for(int i =0; i<n; i++){
        printf("%d %s %d\n", (*estoque)[i].codigo, (*estoque)[i].produto, (*estoque)[i].quantidade);
    }

    for(int i = 0; i<50; i++){
        printf("-");
    }
    printf("\n");

}



int main(){
    struct Produto *estoque = NULL;
    //para o caso de não existir arquivo e ser lido um tamanho >0 do terminal
    //nesse caso teriamos tamanho 4, mas nenhum item ainda inserido, o que causaria erro nos indices
    int posicao=0;
    int tamanho=0;
    int caixa=0;
    FILE *fp;
    char comando[3];

    //precisamos fazer a parte que tenta ler do arquivo ou do terminal. AO final desta parte, teremos
    //tamanho e caixa atualizados. Assim, podemos alocar o espaço para o estoque.
    fp = fopen("estoque.bin", "r");
        if(fp == NULL){
            scanf("%d", &tamanho);
            scanf("%f", &caixa);
            //aloca o vetor estoque do tamanho necessário
            aloca(&estoque, tamanho);
        }
        
        else{
            fscanf("%d", &tamanho);
            fscanf("%f", &caixa);
           
            //aloca o vetor estoque do tamanho necessário
            aloca(&estoque, tamanho);
            for(int i =0; i<tamanho; i++){
                //função que vai percorrer o arquivo lendo os itens e colocando no vetor
                leEstoque(fp, &estoque[i]);
            }
        }

    while(1){
        scanf(" %s", comando);

        if(srtcmp(comando, "IP")==0){
             //passa endereço do estoque e o tamanho atual. Passando o tamanho por referência pq sempre vamos
            //incrementar, ai já fazemos isso na função pra deixar limpo
            insereProduto(&estoque, &tamanho, &posicao);
        }
        else if(strcmp(comando, "AE")==0){
            aumentaEstoque(&estoque);
        }
        else if(strcmp(comando, "MP")==0){
            modificaPreco(&estoque);
        }
        else if(strcmp(comando, "VE")==0){
            venda(&estoque, &caixa);
        }
        else if(strcmp(comando, "CE")==0){
            consultaEstoque(&estoque, posicao);
        }

        else if(strcmp(comando, "CS")==0){
            consultaCaixa(caixa);
        }
        else if(strcmp(comando, "FE")==0){

            //fecha o dia tralalalala

            break;
        }
    }

    return 0;
}