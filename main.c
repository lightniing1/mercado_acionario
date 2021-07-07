#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_compra_venda
{
    int qtd;
    int valor;
    char* sigla;
    struct lista_compra_venda *prox;

} lista_compra_venda;

typedef struct lista_empresa {

    int cotacao;
    char* sigla;
    struct lista_empresa *prox;

} lista_empresa;

lista_compra_venda * inicializa_lista_compra_venda (void);
lista_empresa * inicializa_lista_empresas (void);
int inserir_lista_acoes (lista_compra_venda *lista, lista_empresa *empresa, int qtd, int valor, char* sigla);
int inserir_empresa (lista_empresa *lista, char* sigla);
int excluir(lista_compra_venda *lista, int valor);
int pesquisa_empresa (lista_empresa * empresa, char* sigla);
void listagem_empresas (lista_compra_venda *lista_acoes_compra, lista_compra_venda *lista_acoes_venda, lista_empresa *lista_empresas);
int cotacao_empresa (lista_empresa * empresa, int cotacao, char* sigla);
void executa_compras_vendas (lista_compra_venda *lista_compra, lista_compra_venda *lista_venda, lista_empresa *empresa);


//Cria um nó "cabeca" sem dados, apenas apontando. Inicializa uma lista.
lista_compra_venda * inicializa_lista_compra_venda (void){

    lista_compra_venda * cabeca = malloc(sizeof(lista_compra_venda));
    cabeca -> prox = NULL;

    return cabeca;
}

lista_empresa * inicializa_lista_empresas (void){

    lista_empresa * cabeca = malloc(sizeof(lista_empresa));
    cabeca -> prox = NULL;

    return cabeca;
}

void Limpa_stdin(void)
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//Insere item apos a cabeca
int inserir_lista_acoes (lista_compra_venda *lista, lista_empresa *empresa, int qtd, int valor, char* sigla){

    //Se existir...
    lista_compra_venda *nova_lista_acoes = malloc(sizeof(lista_compra_venda)); //Criação do nó

    nova_lista_acoes->qtd = qtd;
    nova_lista_acoes->valor = valor;
    nova_lista_acoes->sigla = sigla; 
    nova_lista_acoes->prox = NULL;

    while (lista->prox != NULL){
        lista = lista->prox;
    }

    lista->prox = nova_lista_acoes;

    int pesquisa = pesquisa_empresa(empresa, nova_lista_acoes->sigla);
    
    if (pesquisa == 0){
        inserir_empresa(empresa, nova_lista_acoes->sigla);
    }
    ////printf("Item adicionado\n");

    

    return 0;
}

int inserir_empresa (lista_empresa *lista, char* sigla){

    lista_empresa *nova_empresa = malloc(sizeof(lista_empresa)); //Criação do nó
    
    nova_empresa->sigla = sigla;
    nova_empresa->cotacao = 0;
    nova_empresa->prox = NULL;

    while (lista->prox != NULL){
        lista = lista->prox;
    }

    lista->prox = nova_empresa;
    //printf("Empresa adicionada\n");

}

int excluir (lista_compra_venda *lista, int valor){

    lista_compra_venda *temp = lista;
    lista_compra_venda *anterior = NULL;

    while (temp != NULL && temp->valor != valor){
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL){
        ////printf("Nao achado\n");
        return 1;
    }

    anterior->prox = temp->prox;
    ////printf("Excluido\n");

    free(temp);
    return 0;
};

int pesquisa_empresa (lista_empresa * empresa, char* sigla){

    lista_empresa *temp = empresa;

    while(temp != NULL){
        if (temp->sigla == sigla){
            return 1;
        }
        temp = temp->prox;
    }

    if (temp == NULL){
        //printf("Empresa nao disponivel para setar cotacao");
        return 0;
    }

}

int cotacao_empresa (lista_empresa * empresa, int cotacao, char* sigla){

    while(empresa != NULL){
        empresa = empresa->prox;
        if (empresa->sigla == sigla){
            empresa->cotacao = cotacao;
            return 0;
        }
    }

    //printf("Nova cotacao setada\n");
}

//Verifica se pode realizar compra/venda nas ações listadas
void executa_compras_vendas (lista_compra_venda *lista_compra, lista_compra_venda *lista_venda, lista_empresa *empresa){

    char* sigla;
    int temp = 0;

    //Seleciona uma lista_acoes de compra...
    while (lista_compra->prox != NULL){
        lista_compra = lista_compra->prox;
        //printf("Verificando lista_acoes: %s | %d | %d\n", lista_compra->sigla, lista_compra->valor, lista_compra->qtd);

        //... e compara com todas as acoes de venda. Repete isso com todas as de compra.
        while (lista_venda->prox){
            lista_venda = lista_venda->prox;
            
            //Se existe uma ordem de compra e venda compativel e as siglas são iguais. Executa a operlista_acoes.
            if (lista_compra->valor == lista_venda->valor && lista_compra->sigla == lista_venda->sigla){

                //Seta a cotacao da empresa o ultimo preço de venda
                cotacao_empresa(empresa, lista_venda->valor, lista_venda->sigla);
                
                //Abate a quantidade de papeis comprados/vendidos.
                temp = lista_compra->qtd;
                lista_compra->qtd = lista_compra->qtd - lista_venda->qtd;
                lista_venda->qtd = lista_venda->qtd - temp;

                // Se ficar 0 ou negativo, vai para -1.
                if (lista_compra->qtd <= 0){
                    lista_compra->valor = -1;
                }
                
                if (lista_venda->qtd <= 0){
                    lista_venda->valor = -1;
                }

                //printf("Ordem realizada\n");
                //printf("\n");

            }
        }
    }

    //printf("Execuclista_acoes de acoes terminada\n");

};

//Lista a quantidade e valor de cada lista_acoes da empresa selecionada
void exibir_acoes (lista_compra_venda *lista){
    while (lista->prox != NULL){
        lista = lista->prox;
        printf("Sigla: %s\tR$ %d\tQuantidade: %d\t\n", lista->sigla, lista->valor, lista->qtd);
    }
}

void exibir_empresas (lista_empresa *lista){
    while (lista->prox != NULL){
        lista = lista->prox;
        if (lista->cotacao == 0){
            printf("Sigla: %s\tSem dado da ultima cotacao\n", lista->sigla);
        } else {
            printf("Sigla: %s\tR$ %d\n", lista->sigla, lista->cotacao);
        }
    }
}


void salvar_acoes (lista_compra_venda * cabeca){

    lista_compra_venda *atual = cabeca;
    lista_compra_venda *temp = NULL;

    FILE *pArquivo;

    if (pArquivo != NULL){

        pArquivo = fopen("arquivo.txt", "wb");

        while (atual->prox != NULL){

            //Devido a um dos item da struct ser um ponteiro, não podemos salvar ele no arquivo. Daria problemas carregar um ponteiro para algo que aponta para algo invalido.
            //Entao salvamos o ponteiro para o proximo item temporariamente em outro lugar e salvamos os dados do arquivo com o ponteiro apontando para NULL.
            //Depois de salvo, colocamos o ponteiro no lugar.

            atual = atual->prox;
            temp = atual->prox;

            atual->prox = NULL;
            printf("SALVANDO\n");
            fwrite(atual, 1, sizeof(lista_compra_venda), pArquivo);

            atual->prox = temp;

        }
    
        fclose(pArquivo);

    } else {

        printf("Nao foi possivel salvar o arquivo\n");

    }

}

void carrega_acoes (lista_compra_venda *cabeca){
    
}

int main()
{
    lista_empresa * empresas_listadas = inicializa_lista_empresas();
    lista_compra_venda * lista_compra = inicializa_lista_compra_venda();
    lista_compra_venda * lista_venda = inicializa_lista_compra_venda();

    int opcao;
    char* nome;
    int preco = 0;
    int qtd = 0;

    inserir_lista_acoes(lista_compra, empresas_listadas, 10, 15, "OIBR3");
    inserir_lista_acoes(lista_compra, empresas_listadas, 10, 15, "LAME3");

    exibir_acoes(lista_compra);
    exibir_empresas(empresas_listadas);
    salvar(lista_compra);
    
    /*
    while (opcao){

    printf("1 - Inserir acao para compra\n");
    printf("2 - Inserir acao para venda\n");
    printf("3 - Verificar cotacoes das empresas\n");
    printf("4 - Mostrar mercado\n");
    printf("0 - Sair\n");

    scanf("%d", &opcao);
    
    executa_compras_vendas(lista_compra, lista_venda, empresas_listadas);
    excluir(lista_compra, -1);
    excluir(lista_venda, -1);

    Limpa_stdin();

        switch (opcao)
        {
        case 1:
            printf("__________________\n");
            
            printf("Sigla da empresa: ");
            scanf("%s", nome);

            Limpa_stdin();

            printf("Preco da acao: ");
            scanf("%d", &preco);

            Limpa_stdin();

            printf("Quantidade: ");
            scanf("%d", &qtd);

            inserir_lista_acoes(lista_compra, empresas_listadas, qtd, preco, nome);
            printf("__________________\n");

            break;
        
        case 2:

            printf("__________________\n");

            printf("Sigla da empresa: ");
            scanf("%s", nome);

            Limpa_stdin();

            printf("Preco da acao: ");
            scanf("%d", &preco);

            Limpa_stdin();

            printf("Quantidade: ");
            scanf("%d", &qtd);
            
            inserir_lista_acoes(lista_venda, empresas_listadas, qtd, preco, nome);
            
            printf("__________________\n");

            break;

        case 3:

            printf("__________________\n");
            exibir_empresas(empresas_listadas);
            printf("__________________\n");

            break;

        case 4:
            
            printf("__________________\n");
            printf("Acoes de compra\n");
            exibir_acoes(lista_compra);

            
            printf("Acoes de venda\n");
            exibir_acoes(lista_venda);
            printf("__________________\n");
            break;

        case 0:

            break;

        default:

            printf("Opcao invalida\n");
            
            break;
        }

    }
    */
       return 0;
}