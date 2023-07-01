
/*1. Inserir um produto no estoque: são fornecidos o nome do produto, a quantidade recebida e o
preço.
2. Aumentar o estoque de um produto: são fornecidos o código do produto e a quantidade a
adicionar no estoque.
3. Modificar o preço de um produto: são fornecidos o código do produto e o novo preço.
4. Realizar uma venda: são fornecidos os códigos dos produtos e o sistema imprime na tela os
nomes dos produtos, seus preços e o total.
5. Consultar o estoque dos produtos: lista código, nome e quantidade no estoque de todos os
produtos.
6. Consultar o saldo do caixa.
*/

insere_Produto();

aumenta_Estoque();

modifica_Preco();

Venda();

consulta_Estoque();

consulta_Saldo();

struct Estoque{
    char produto[30];
    int preço;
    int quantidade;
};

