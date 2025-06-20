#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "listaClientes.h"

struct elemento{
    CLIENTE dados;
    struct elemento *prox;
};
typedef struct elemento ELEM;

Lista *criaLista(){
    Lista *li;
    li =(Lista*) malloc(sizeof(Lista));
    if (li != NULL){
            *li = NULL;
    }
    return li;
}

void abortaPrograma(){
    printf("\n ERRO lista nao alocada");
    printf("\n Programa sera encerrado");
    system("pause");
    exit(1);
}


void apagaLista(Lista *li){
    if (li != NULL){
        ELEM *no;
        while ((*li)!= NULL){
            no = *li;
            *li = (*li) ->prox;
            free(no);
        }
        free(li);
    }
}

int listaVazia(Lista *li){
    if (li == NULL){
        abortaPrograma();

    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}


int insereOrdenada(Lista *li, CLIENTE cl){
    if (li == NULL){
        abortaPrograma();
    }
    ELEM *atual = *li;
    while (atual != NULL) {
        if (atual->dados.codigo == cl.codigo) {
            printf("Erro: Ja existe um cliente com o codigo %d registrado. Insercao cancelada.\n", cl.codigo);
            return 0;
        }
        atual = atual->prox;
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no==NULL){
        return 0;
    }
    no-> dados = cl;
    if(listaVazia(li)){
        no->prox=(*li);
        *li=no;
        return cl.codigo;
    }else{
        ELEM *ant, *atual = *li;
        while (atual != NULL && atual -> dados.codigo< cl.codigo){
            ant = atual;
            atual = atual -> prox;

        }
        if (atual==*li){
            no -> prox = (*li);
            *li = no;
        }else{
            no->prox = ant->prox;
            ant->prox = no;
        }
        return cl.codigo;
    }
}

Lista* carregaLista(char* nome_arquivo) {
    Lista* li = criaLista();
    if (li == NULL) {
            abortaPrograma();
    }

    FILE* fp = fopen(nome_arquivo, "rb");
    if (fp == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com lista vazia.\n");
        return li;
    }

    CLIENTE cl;

    while (fread(&cl, sizeof(CLIENTE), 1, fp) == 1) {

        insereOrdenada(li, cl);
    }

    fclose(fp);
    return li;

}


int validarOpcao() {
    char linha[MAX];
    int opcao;

    while (1) {
        fgets(linha, sizeof(linha), stdin);

        if (sscanf(linha, "%d", &opcao) == 1 && opcao >= 1 && opcao <= 7) {
            return opcao;
        }
        printf("Entrada invalida! Digite um numero entre 1 e 7: ");
    }
}

int validarCodigo() {
    char linha[MAX];
    int codigo;

    while (1) {
        fgets(linha, sizeof(linha), stdin);

        if (sscanf(linha, "%d", &codigo) == 1 && codigo > 0) {
            return codigo;
        }
        printf("Entrada invalida! Por favor, digite um numero inteiro positivo: ");
    }
}



CLIENTE coletaDadoCliente(){
    CLIENTE cl;

    printf("Digite o codigo do cliente: ");
    cl.codigo = validarCodigo();

    printf("Digite o nome do cliente: ");
    fgets(cl.nome,sizeof(cl.nome),stdin);
    cl.nome[strcspn(cl.nome,"\n")] = '\0';

    printf("Digite o nome da empresa: ");
    fgets(cl.empresa,sizeof(cl.empresa),stdin);
    cl.empresa[strcspn(cl.empresa,"\n")] = '\0';

    printf("Digite o nome do departamento: ");
    fgets(cl.departamento,sizeof(cl.departamento),stdin);
    cl.departamento[strcspn(cl.departamento,"\n")] = '\0';

    printf("Digite o telefone do cliente: ");
    fgets(cl.telefone,sizeof(cl.telefone),stdin);
    cl.telefone[strcspn(cl.telefone,"\n")] = '\0';

    printf("Digite o celular do cliente: ");
    fgets(cl.celular,sizeof(cl.celular),stdin);
    cl.celular[strcspn(cl.celular,"\n")] = '\0';

    printf("Digite o email do cliente: ");
    fgets(cl.email,sizeof(cl.email),stdin);
    cl.email[strcspn(cl.email,"\n")] = '\0';

    return cl;
    }


int consultaCodigo(Lista* li, int codigo, CLIENTE* clEncontrado) {
    if (li == NULL || *li == NULL) {
        return 0;
    }

    ELEM* noAtual = *li;

    while (noAtual != NULL) {
        if (noAtual->dados.codigo == codigo) {
                *clEncontrado = noAtual->dados;
        }
        return 1;
        noAtual = noAtual->prox;
    }
    return 0;
}

int consultaNome(Lista* li,char* nomeBusca, CLIENTE* clEncontrado) {
    if (li == NULL || *li == NULL) {
        return 0;
    }

    ELEM* noAtual = *li;

    while (noAtual != NULL) {
        if (strcmp(noAtual->dados.nome, nomeBusca) == 0) {

            if (clEncontrado != NULL) {
                *clEncontrado = noAtual->dados;
            }
            return 1;
        }

        noAtual = noAtual->prox;
    }

    return 0;
}

char lerCharSN() {
    char buffer[10];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if ((buffer[0] == 's' || buffer[0] == 'S' ||
                 buffer[0] == 'n' || buffer[0] == 'N') && buffer[1] == '\n') {
                return buffer[0];
            }
        }
        printf("Resposta inválida! Digite 's' ou 'n': ");
    }
}



int editaCliente(Lista* li, int codigoBusca) {
    char resposta;

    if (li == NULL || *li == NULL) {
        printf("Erro: Lista de clientes vazia ou invalida.\n");
        return 0;
    }

    ELEM* noAtual = *li;

    while (noAtual != NULL && noAtual->dados.codigo != codigoBusca) {
        noAtual = noAtual->prox;
    }

    if (noAtual == NULL) {
        printf("Erro: Cliente com o codigo %d nao encontrado.\n", codigoBusca);
        return 0;
    }

    printf("\nCliente com codigo %d encontrado.", codigoBusca);
    printf("Dados atuais:\n");
    printf("  Nome: %s\n", noAtual->dados.nome);
    printf("  Empresa: %s\n", noAtual->dados.empresa);
    printf("  Departamento: %s\n", noAtual->dados.departamento);
    printf("  Telefone: %s\n", noAtual->dados.telefone);
    printf("  Celular: %s\n", noAtual->dados.celular);
    printf("  E-mail: %s\n", noAtual->dados.email);
    printf("----------------------------------------\n");



    CLIENTE novosDados = noAtual->dados;
    novosDados.codigo = codigoBusca;

    printf("\nDeseja editar o nome do cliente? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("\nNovo nome do cliente: ");
    fgets(novosDados.nome, sizeof(novosDados.nome), stdin);
    novosDados.nome[strcspn(novosDados.nome, "\n")] = '\0';
    }

    printf("\nDeseja editar o nome da empresa? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("Novo nome da empresa: ");
    fgets(novosDados.empresa, sizeof(novosDados.empresa), stdin);
    novosDados.empresa[strcspn(novosDados.empresa, "\n")] = '\0';
    }

    printf("\nDeseja editar o nome do departamento? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("Novo nome do departamento: ");
    fgets(novosDados.departamento, sizeof(novosDados.departamento), stdin);
    novosDados.departamento[strcspn(novosDados.departamento, "\n")] = '\0';
    }

    printf("\nDeseja editar o telefone do cliente? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("Novo telefone do cliente: ");
    fgets(novosDados.telefone, sizeof(novosDados.telefone), stdin);
    novosDados.telefone[strcspn(novosDados.telefone, "\n")] = '\0';
    }

    printf("\nDeseja editar o celular do cliente? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("Novo celular do cliente: ");
    fgets(novosDados.celular, sizeof(novosDados.celular), stdin);
    novosDados.celular[strcspn(novosDados.celular, "\n")] = '\0';
    }

    printf("\nDeseja editar o email do cliente? (s/n): ");
    resposta = lerCharSN();
    if (resposta == 's' || resposta == 'S') {
    printf("Novo email do cliente: ");
    fgets(novosDados.email, sizeof(novosDados.email), stdin);
    novosDados.email[strcspn(novosDados.email, "\n")] = '\0';
    }


    noAtual->dados = novosDados;

    printf("\nInformacoes do cliente com codigo %d atualizadas com sucesso!\n", codigoBusca);
    return 1;
}


int removeOrdenado(Lista *li, int codigo){
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *ant,*no = *li;
    while(no != NULL && no -> dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }
    if (no==NULL){
        return 0;
    }
    if(no== *li){
        *li = no -> prox;
    }else {
        ant->prox = no -> prox;
    }
    codigo = no -> dados.codigo;
    free(no);
    return codigo;
}


int salvarLista(Lista* li, const char* nomeArquivo) {
    if (li == NULL) {
        abortaPrograma();
    }
    if (*li == NULL) {
        printf("Aviso: Lista de clientes vazia. Criando/substituindo arquivo vazio.\n");
    }

    FILE* fp = fopen(nomeArquivo, "wb");
    if (fp == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s' para escrita.\n", nomeArquivo);
        return 0;
    }

    ELEM* noAtual = *li;
    int clientesSalvos = 0;

    while (noAtual != NULL) {
        size_t escritaSucesso = fwrite(&(noAtual->dados), sizeof(CLIENTE), 1, fp);

        if (escritaSucesso != 1) {
            printf("Erro: Falha ao escrever os dados do cliente no arquivo.\n");
            fclose(fp);
            return 0;
        }
        clientesSalvos++;
        noAtual = noAtual->prox;
    }

    fclose(fp);
    printf("Dados de %d cliente(s) salvos com sucesso em '%s'.\n", clientesSalvos, nomeArquivo);
    return 1;
}

void exibeTodosContatos(Lista* li) {
    if (li == NULL || *li == NULL) {
        printf("\nA lista de clientes esta vazia ou invalida. Nao ha clientes para exibir.\n");
        return;
    }

    printf("\nRelatorio de todos os contatos:\n");

    ELEM* noAtual = *li;
    int contador = 0;

    while (noAtual != NULL) {
        contador++;
        printf("--------------------------------------\n");
        printf("  Codigo: %d\n", noAtual->dados.codigo);
        printf("  Nome: %s\n", noAtual->dados.nome);
        printf("  Empresa: %s\n", noAtual->dados.empresa);
        printf("  Departamento: %s\n", noAtual->dados.departamento);
        printf("  Telefone: %s\n", noAtual->dados.telefone);
        printf("  Celular: %s\n", noAtual->dados.celular);
        printf("  E-mail: %s\n", noAtual->dados.email);
        printf("--------------------------------------\n");

        noAtual = noAtual->prox;
    }

    printf("Total de contatos salvos: %d",contador);
    printf("\n--- FIM DO RELATORIO ---\n");
}


