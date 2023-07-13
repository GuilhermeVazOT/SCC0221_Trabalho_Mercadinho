

/*Este programa tem como objetivo a criação de um sistema de controle de estoque e caixa para um mercadinho.
O sistema deve ser capaz de realizar consultas de saldo, estoque, incluir novos produtos, realizar vendas, modificar preço e aumentar estoque.

O programa foi modularizado e a explicação detalhada de cada função ocorrerá no decorrer do código.

Autores: Catarina Moreira Lima - 8957221
Eduarda Almeida Garrett de Carvalho - 14566794
Guilherme Vaz de Oliveira Taratá - 10817476*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Produto{
    char produto[50];
    float preco;
    int quantidade;
    int codigo;
}Produto;

//prototipagem das funções
void realoca(Produto **estoque, int n);
void aloca(Produto **estoque, int n);
void insereProduto(Produto **estoque, int *tamanho, int *posicao);
void consultaCaixa(float n);
void consultaEstoque(Produto **estoque, int n);
void leEstoque(FILE *fp, Produto *estoque);
void modificaPreco(Produto **estoque, int posicao);
void venda(Produto **estoque, float *caixa, int posicao);
void aumentaEstoque(Produto **estoque, int posicao);
void fechaEstoque(Produto **estoque, FILE *fp, int posicao, float caixa);

/// @brief Funcao que encerra o dia, gravando o estoque no arquivo e fechando, garantindo a escrita. Também libera ponteiro para stream e memoria alocada
/// @param estoque ponteiro para vetor de structs que guarda os produtos em estoque
/// @param fp ponteiro para arquivo
/// @param posicao quantidade de produtos no vetor
/// @param caixa variavel que acumula o caixa
void fechaEstoque(Produto **estoque, FILE *fp, int posicao, float caixa){

    fprintf(fp, "%d\n", posicao);
    fprintf(fp, "%f\n", caixa);
    
    for(int i =0; i<posicao; i++){
        fprintf(fp, "%s\n", (*estoque)[i].produto);
        fprintf(fp, "%f\n", (*estoque)[i].preco);
        fprintf(fp, "%d\n", (*estoque)[i].quantidade);
        fprintf(fp, "%d\n", (*estoque)[i].codigo);
        
    }
    fclose(fp);
    fp=NULL;
    free((*estoque));
    (*estoque)=NULL;

    
}


/// @brief função que aumenta a quantidade de um produto registrado no estoque.
/// @param estoque ponteiro para o vetor de struct que contém a quantidade do produto a ser incrementada.
/// @param posicao inteiro com o id do último produto do estoque.
void aumentaEstoque(Produto **estoque, int posicao){
    
    int id, qnt;

    fflush(stdin);

    scanf("%d %d", &id, &qnt);

    if(id < posicao)
        (*estoque)[id].quantidade += qnt;
}



/// @brief Funcao que modifica o preco de um produto existente
/// @param estoque Ponteiro para vetor de structs que guarda os produtos em estoque
void modificaPreco(Produto **estoque, int posicao){
    float preco_novo;
	int cod;
    scanf(" %d %f", &cod, &preco_novo);
    if(cod < posicao)
    (*estoque)[cod].preco = preco_novo;
}

/// @brief FUncao que realiza a venda de um produto: Decrementa o estoque, aumenta o caixa e imprime o que foi vendido e total da venda
/// @param estoque Ponteiro para vetor de structs que guarda os produtos em estoque
/// @param caixa endereco da variavel que acumula o caixa
void venda(Produto **estoque, float *caixa, int posicao){

	int *carrinho = NULL;
	float precoTotal = 0;
	int tam = 10;
	int cont = 0; 

    //aloca dinamicamente o espaco para o vetor que guarda os indices dos produtos a serem vendidos
	carrinho = (int*)calloc(tam, sizeof(int));

    //verifica sucesso
	if (carrinho == NULL){
		printf("ERRO: sem memoria pro carrinho\n");
		exit(1);
	}

    //loop infinito
	while(1){
        //verifica se ha a necessidade de realocar
		if (cont+1 == tam){
			tam += tam; 
			carrinho = (int *) realloc(carrinho, sizeof(int)*tam);
            if (carrinho == NULL){
				printf("ERRO: sem memoria pro carrinho\n");
				exit(1);
			}
		}
        //le o indice a ser vendido
        scanf(" %d", &carrinho[cont]);
        //se for -1 sai do loop
        if (carrinho[cont] == -1){
			break;
		}
        //OBS o contador nao conta o -1
    cont ++;
    }

    //Percorre o vetor realizando a venda
	for (int i = 0; i < cont; i++){
        //so vende se tiver estoque >0
        if ((*estoque)[carrinho[i]].quantidade>0 && carrinho[i]<posicao){
            (*estoque)[carrinho[i]].quantidade--;
            precoTotal += (*estoque)[carrinho[i]].preco;
            printf("%s %.2f\n", (*estoque)[carrinho[i]].produto, (*estoque)[carrinho[i]].preco);
        }
    }
    
    //adiciona o valor vendido no caixa
	(*caixa) += precoTotal;
    //imprime o valor total
    printf("Total: %.2f\n", precoTotal);
    for (int j = 0; j < 50; j++){
		printf("-");
	}
	printf("\n");
}

/// @brief Funcao que le o estoque de um arquivo existente
/// @param fp Ponteiro para o arquivo
/// @param estoque Ponteiro para vetor de structs que guarda os produtos em estoque
void leEstoque(FILE *fp, Produto *estoque){

        fscanf(fp, "%s", estoque->produto);
        fscanf(fp, "%f", &estoque->preco);
        fscanf(fp, "%d", &estoque->quantidade);
        fscanf(fp, "%d", &estoque->codigo);

        

}

/// @brief função que realoca para um espaço de memória maior e copia os dados
/// @param estoque ponteiro para o array que deve ser realocado
/// @param n tamanho para o qual deve ser realocado
void realoca(Produto **estoque, int n){
    //realoca pra caber n structs Produto
    *estoque = realloc(*estoque, n*sizeof(Produto));
    if(*estoque == NULL){
        printf("Sem memória realoc");
        exit(1);
    }
}

/// @brief função que realoca um espaço de memória para um ponteiro
/// @param estoque ponteiro para o array que será alocado
/// @param n tamanho do espaço de memória alocado
void aloca(Produto **estoque, int n){
    //realoca pra caber n structs Produto
    *estoque = malloc(n*sizeof(Produto));

     if(*estoque == NULL){
        printf("Sem memória");
        exit(1);
    }
    
}

/// @brief = função que insere um novo produto ao fim de um vetor de structs
/// @param estoque = ponteiro para o vetor que armazena as structs de produtos
/// @param tamanho = tamanho do vetor (espaco disponivel)
/// @param posicao = posição da ultima inserida no vetor
void insereProduto(Produto **estoque, int *tamanho, int *posicao){
    //verifica a necessidade de realocar
    if(*posicao+1 >= *tamanho){
        //se a posição alcançar o tamanho do vetor, realoca pro dobro do tamanho
        (*tamanho)+=(*tamanho)+1;
        //realoca pro tamanho maior
        realoca(estoque, *tamanho);
    }
    
    
    //le e insere um novo produto;
    scanf(" %s", (*estoque)[(*posicao)].produto);
    scanf("%d", &(*estoque)[(*posicao)].quantidade);
    scanf("%f", &(*estoque)[(*posicao)].preco);
    (*estoque)[(*posicao)].codigo=*posicao;
    
    //incrementa a posicao final do vetor
    (*posicao)++;
}


/// @brief = função que imprime o saldo do caixa
/// @param n = valor acumulado do caixa
void consultaCaixa(float n){
    printf("Saldo: %.2f\n", n);

    for(int i = 0; i<50; i++){
        printf("-");
    }
    printf("\n");
}


/// @brief = função que percorre o vetor de structs e imprime codigo, nome e quantidade
/// @param estoque = ponteiro para o vetor que armazena as structs de produtos
/// @param n = tamanho do vetor
void consultaEstoque(Produto **estoque, int n){

    for(int i =0; i<n; i++){
        printf("%d %s %d\n", (*estoque)[i].codigo, (*estoque)[i].produto, (*estoque)[i].quantidade);
    }

    for(int i = 0; i<50; i++){
        printf("-");
    }
    printf("\n");

}



int main(){
    Produto *estoque = NULL;
    //para o caso de não existir arquivo e ser lido um tamanho >0 do terminal
    //nesse caso teriamos tamanho 4, mas nenhum item ainda inserido, o que causaria erro nos indices
    int posicao=0;
    int tamanho=0;
    float caixa=0;
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
            fscanf(fp, "%d", &tamanho);
            fscanf(fp, "%f", &caixa);
            posicao=tamanho;
           
            //aloca o vetor estoque do tamanho necessário
            aloca(&estoque, tamanho);
            for(int i =0; i<tamanho; i++){
                //função que vai percorrer o arquivo lendo os itens e colocando no vetor
                leEstoque(fp, &estoque[i]);
            }
            fclose(fp);
            fp=NULL;
        }
    //loop infinito
    while(1){
        scanf(" %s", comando);
    // sequencia que verifica qual o comando que foi inserido
        if(strcmp(comando, "IP")==0){
             //passa endereço do estoque e o tamanho atual. Passando o tamanho por referência pq sempre vamos
            //incrementar, ai já fazemos isso na função pra deixar limpo
            insereProduto(&estoque, &tamanho, &posicao);
        }
        else if(strcmp(comando, "AE")==0){
            aumentaEstoque(&estoque, posicao);
        }
        else if(strcmp(comando, "MP")==0){
            modificaPreco(&estoque, posicao);
        }
        else if(strcmp(comando, "VE")==0){
            venda(&estoque, &caixa, posicao);
        }
        else if(strcmp(comando, "CE")==0){
            consultaEstoque(&estoque, posicao);
        }

        else if(strcmp(comando, "CS")==0){
            consultaCaixa(caixa);
        }
        else if(strcmp(comando, "FE")==0){
            //abre o arquivo (ou cria) com a intencao de sobrescrever
            fp = fopen("estoque.bin", "w");
            if (fp ==NULL){
                printf("Erro ao gravar arquivo");
                exit(1);
            }

            fechaEstoque( &estoque, fp, posicao, caixa);
            //saida do loop
            break;
        }
    }

    return 0;
}