#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define FORMATO ".bin"

typedef struct lista_compra_venda
{
    int qtd;
    int valor;
    char sigla[5];
    struct lista_compra_venda *prox;

} lista_compra_venda;

typedef struct lista_empresa {

    int cotacao;
    char sigla[5];
    struct lista_empresa *prox;

} lista_empresa;


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

    int pesquisa = 1;
    pesquisa = pesquisa_empresa(empresa, sigla);

    if (pesquisa == 0){

        inserir_empresa(empresa, sigla, 0);

        lista_compra_venda *nova_lista_acoes = malloc(sizeof(lista_compra_venda)); //Criação do nó
    
        nova_lista_acoes->qtd = qtd;
        nova_lista_acoes->valor = valor;
        strcpy(nova_lista_acoes->sigla, sigla); 
        nova_lista_acoes->prox = NULL;

        while (lista->prox != NULL){
            lista = lista->prox;
        }
        
        lista->prox = nova_lista_acoes;

        printf("%d\n", pesquisa);
            
    } else {

        lista_compra_venda *nova_lista_acoes = malloc(sizeof(lista_compra_venda)); //Criação do nó
    
        nova_lista_acoes->qtd = qtd;
        nova_lista_acoes->valor = valor;
        strcpy(nova_lista_acoes->sigla, sigla); 
        nova_lista_acoes->prox = NULL;

        while (lista->prox != NULL){
            lista = lista->prox;
        }
        
        lista->prox = nova_lista_acoes;

        printf("%d\n", pesquisa);
    }   

    return 0;
}


int inserir_empresa (lista_empresa *lista, char* sigla, int cotacao){

    lista_empresa *nova_empresa = malloc(sizeof(lista_empresa)); //Criação do nó
    
    strcpy(nova_empresa->sigla, sigla);
    nova_empresa->cotacao = cotacao;
    nova_empresa->prox = NULL;

    while (lista->prox != NULL){
        lista = lista->prox;
    }

    lista->prox = nova_empresa;

}

int cotacao_empresa (lista_empresa * empresa, int cotacao, char* sigla){

    int compara = 1;
    
    while(empresa->prox != NULL){

        empresa = empresa->prox;
        compara = strcmp(empresa->sigla, sigla);

        if (compara == 0){
            empresa->cotacao = cotacao;
        }
    }
    return 0;
}

int excluir (lista_compra_venda *lista, int valor){

    lista_compra_venda *temp = lista;
    lista_compra_venda *anterior = NULL;

    while (temp != NULL && temp->valor != valor){
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL){
        return 1;
    }

    anterior->prox = temp->prox;

    free(temp);
    return 0;
};


int pesquisa_empresa (lista_empresa *empresa, char* sigla){

    lista_empresa *temp = empresa;

    while(temp != NULL){

        if ( strcmp(temp->sigla, sigla) == 0){
            return 1;
        }

        temp = temp->prox;
    }

}

//Verifica se pode realizar compra/venda nas ações listadas
void executa_compras_vendas (lista_compra_venda *lista_compra, lista_compra_venda *lista_venda, lista_empresa *empresa){

    char* sigla;
    int temp = 0;
    int compara_siglas;

    //Seleciona uma lista_acoes de compra...
    while (lista_compra->prox != NULL){
        lista_compra = lista_compra->prox;

        //... e compara com todas as acoes de venda. Repete isso com todas as de compra.
        while (lista_venda->prox){

            lista_venda = lista_venda->prox;
            compara_siglas = strcmp(lista_compra->sigla, lista_venda->sigla);

            //Se existe uma ordem de compra e venda compativel e as siglas são iguais. Executa a operacoes.
            if ( (lista_compra->valor == lista_venda->valor) && (compara_siglas) == 0 ){

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

                printf("Ordem realizada\n");
                printf("\n");

            }
        }
    }

};

//Lista a quantidade e valor de cada lista_acoes da empresa selecionada
void exibir_acoes (lista_compra_venda *lista){
    while (lista->prox != NULL){
        lista = lista->prox;
        printf("Sigla: %s\tR$ %d\tQuantidade: %d\t\n", lista->sigla, lista->valor, lista->qtd);
    }
}

//Lista a cotacao de todas as empresas
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


void salvar_acoes (lista_compra_venda *cabeca, char* nome_do_arquivo){

    lista_compra_venda *atual = cabeca;
    lista_compra_venda *temp = NULL;
    FILE *pArquivo;

    pArquivo = fopen(nome_do_arquivo, "wb");

    if (pArquivo != NULL){

        while (atual->prox != NULL){

            //Devido a um dos item da struct ser um ponteiro, não podemos salvar ele no arquivo. Daria problemas carregar um ponteiro para algo que aponta para algo invalido.
            //Entao salvamos o ponteiro para o proximo item temporariamente em outro lugar e salvamos os dados do arquivo com o ponteiro apontando para NULL.
            //Depois de salvo, colocamos o ponteiro no lugar.

            atual = atual->prox;
            temp = atual->prox;

            atual->prox = NULL;

            fwrite(atual, 1, sizeof(lista_compra_venda), pArquivo);

            atual->prox = temp;

        }
    
        fclose(pArquivo);

    } else {

        printf("Nao foi possivel salvar o arquivo\n");

    }

}

void salvar_empresas (lista_empresa * cabeca, char* nome_do_arquivo){

    lista_empresa *atual = cabeca;
    lista_empresa *temp = NULL;
    FILE *pArquivo;

    pArquivo = fopen(nome_do_arquivo, "wb");

    if (pArquivo != NULL){

        while (atual->prox != NULL){

            atual = atual->prox;
            temp = atual->prox;

            atual->prox = NULL;

            fwrite(atual, 1, sizeof(lista_empresa), pArquivo);

            atual->prox = temp;

        }
    
        fclose(pArquivo);
    }
}

void carrega_acoes (lista_compra_venda *cabeca, lista_empresa *empresas, char* nome_do_arquivo) {

    lista_compra_venda *temp;
    FILE *pArquivo;


    pArquivo = fopen(nome_do_arquivo, "rb");

    if (pArquivo != NULL){

        while ( fread (temp, sizeof(lista_compra_venda), 1, pArquivo) ){

            inserir_lista_acoes(cabeca, empresas, temp->qtd, temp->valor, temp->sigla);
        }

        fclose(pArquivo);

    }

}

void carrega_empresas (lista_empresa *cabeca, char* nome_do_arquivo) {

    lista_empresa *atual = cabeca;
    lista_empresa *temp;
    FILE *pArquivo;

    pArquivo = fopen(nome_do_arquivo, "rb");

    if (pArquivo != NULL){

        while ( fread (temp, sizeof(lista_empresa), 1, pArquivo) ){

            inserir_empresa(cabeca, temp->sigla, temp->cotacao);
        }

        fclose(pArquivo);

    }

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

    carrega_empresas(empresas_listadas, "l_e");
    carrega_acoes(lista_compra, empresas_listadas, "l_c");
    carrega_acoes(lista_venda, empresas_listadas, "l_v");
   
    while (opcao){

    executa_compras_vendas(lista_compra, lista_venda, empresas_listadas);
    excluir(lista_compra, -1);
    excluir(lista_venda, -1);

    printf("1 - Inserir acao para compra\n");
    printf("2 - Inserir acao para venda\n");
    printf("3 - Verificar cotacoes das empresas\n");
    printf("4 - Mostrar mercado\n");
    printf("0 - Sair\n");

    scanf("%d", &opcao);

    salvar_acoes(lista_compra, "l_c");
    salvar_acoes(lista_venda, "l_v");
    salvar_empresas(empresas_listadas, "l_e");

    Limpa_stdin();

        switch (opcao)
        {
        case 1:
            printf("__________________\n");
            
            printf("Sigla da empresa: ");
            scanf("%5s", nome);

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
            scanf("%5s", nome);

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
    
    return 0;
}