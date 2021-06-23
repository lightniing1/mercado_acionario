#include <stdio.h>
#include <stdlib.h>

typedef struct lista_encadeada
{
    int qtd;
    int valor;
    char* sigla;
    struct lista_encadeada *prox;

} lista_encadeada;

//Cria um nó "cabeca" sem dados, apenas apontando.
lista_encadeada * cria_lista (void){

    lista_encadeada * cabeca = malloc(sizeof(lista_encadeada));
    cabeca -> prox = NULL;

    return cabeca;
}

//Insere item apos a cabeca
void inserir (lista_encadeada *lista, int qtd, int valor, char* sigla){

    lista_encadeada *novo_item = malloc(sizeof(lista_encadeada));

    novo_item->qtd = qtd;
    novo_item->valor = valor;
    novo_item->sigla = sigla;
    novo_item->prox = NULL;

    while (lista->prox != NULL){
        lista = lista->prox;
    }

    lista->prox = novo_item;
    //printf("Item adicionado\n");

}

//Lista a quantidade e valor de cada acao da empresa selecionada
void exibir (lista_encadeada *lista){
    while (lista->prox != NULL){
        lista = lista->prox;
        printf("Sigla: %s | R$ %d | Quantidade: %d\n", lista->sigla, lista->valor, lista->qtd);
    }
}

int main()
{

    //TO DO: Tentar refatorar inserção dos papeis e criacao das empresas

    lista_encadeada *lista_compra_OIBR3 = cria_lista();
    lista_encadeada *lista_compra_LAME3 = cria_lista();
    lista_encadeada *lista_compra_ITUB3 = cria_lista();

    lista_encadeada *lista_venda_OIBR3 = cria_lista();
    lista_encadeada *lista_venda_LAME3 = cria_lista();
    lista_encadeada *lista_venda_ITUB3 = cria_lista();

    inserir(lista_compra_OIBR3, 10, 10, "OIBR3");
    inserir(lista_compra_OIBR3, 25, 21, "OIBR3");
    inserir(lista_compra_LAME3, 2130, 2543, "LAME3");
    inserir(lista_compra_LAME3, 2421, 30, "LAME3");
    inserir(lista_compra_ITUB3, 231, 20, "ITUB3");
    inserir(lista_compra_ITUB3, 2410, 550, "ITUB3");

    inserir(lista_venda_OIBR3, 200, 200, "OIBR3");
    inserir(lista_venda_OIBR3, 500, 500, "OIBR3");
    inserir(lista_venda_LAME3, 500, 500, "LAME3");
    inserir(lista_venda_LAME3, 500, 500, "LAME3");
    inserir(lista_venda_ITUB3, 500, 500, "ITUB3");
    inserir(lista_venda_ITUB3, 500, 500, "ITUB3");

    printf("Papeis de compra disponiveis\n");
    exibir(lista_compra_OIBR3);
    exibir(lista_compra_LAME3);
    exibir(lista_compra_ITUB3);

    printf("Papeis de venda disponiveis\n");
    exibir(lista_venda_OIBR3);
    exibir(lista_venda_LAME3);
    exibir(lista_venda_ITUB3);

    return 0;
}