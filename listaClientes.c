#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "listaClientes.h"


//Struct elemento retirada exatamente do exemplo da aula sobre lista dinamicas, adaptada para struct CLIENTE
struct elemento{
    CLIENTE dados;
    struct elemento *prox;
};
typedef struct elemento ELEM;

//Retirada exatamente do exemplo da aula sobre lista dinamicas
//Funcao que cria e inicializa uma nova lista
//Retorna um ponteiro para a nova lista(Lista*) [ou NULL se falhar!]
Lista *criaLista(){
    Lista *li;

    li =(Lista*) malloc(sizeof(Lista));
    if (li != NULL){
            *li = NULL;
    }
    return li;//Ponteiro da nova lista
}

//retirada exatamente do exemplo da aula sobre lista dinamicas
void abortaPrograma(){
    printf("\n ERRO lista nao alocada");
    printf("\n Programa sera encerrado");
    system("pause");
    exit(1);
}

//retirada exatamente do exemplo da aula sobre lista dinamicas
//Libera toda a memoria alocada para  a lista
void apagaLista(Lista *li){
    //Verifica se a lista foi alocada
    if (li != NULL){
        ELEM *no;
        //Percorre toda a lista liberando cada no
        while ((*li)!= NULL){
            no = *li; //guarda o no atual
            *li = (*li) ->prox; // avança para o prox
            free(no); // libera o no atual
        }
        //No fim, libera o ponteiro da lista
        free(li);
    }
}

//Retirada exatamente do exemplo da aula sobre lista dinamicas
// Função que verifica se a lista está vazia.
// Retorna 1 se a lista estiver vazia, 0 caso contrário.
int listaVazia(Lista *li){
    if (li == NULL){
        abortaPrograma();

    } //Verifica se o primeiro elemento da lista é NULL, 1 = True
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//Insere um novo cliente na lista de maneira a deixar o cliente com menor codigo no topo da lista
//Retorna 0 (False) em caso de erro durante a execucao do programa
//Retorna o codigo do cliente e 1 (True) caso seja inserido com sucesso!
int insereOrdenada(Lista *li, CLIENTE cl){
    if (li == NULL){
        abortaPrograma();
    }
    //Verifica duplicidade de codigos
    ELEM *atual = *li;
    while (atual != NULL) {
        if (atual->dados.codigo == cl.codigo) {
            printf("Erro: Ja existe um cliente com o codigo %d registrado. Insercao cancelada.\n", cl.codigo);
            return 0;
        }
        atual = atual->prox;
    }
    //Aloca memoria para o novo elemento
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no==NULL){
        return 0;
    }

    //Copia os dados do cliente para um novo nó
    no-> dados = cl;

    //Se a lista (li) estiver vazia, insere no inicio (0)
    if(listaVazia(li)){
        no->prox=(*li);
        *li=no;
        return cl.codigo;

    }else{
        //Se nao estiver vazia percorre a lista até encontrar a posicao correta
        ELEM *ant, *atual = *li;

        // Procura a posição onde o novo código seja maior que os anteriores
        while (atual != NULL && atual -> dados.codigo< cl.codigo){
            ant = atual;
            atual = atual -> prox;

        }
        //Para inserir no inicio da lista
        if (atual==*li){
            no -> prox = (*li);
            *li = no;
        }else{
            //Para inserir no final ou entre dois elementos da lista
            no->prox = ant->prox;
            ant->prox = no;
        }
        return cl.codigo; //sucesso
    }
}

//Carrega uma lista de clientes a partir do arquivo binario
//Retorna um ponteiro para a lista preenchida, ou uma lista vazia
Lista* carregaLista(char* nome_arquivo) {
    //Cria a lista vazia
    Lista* li = criaLista();
    if (li == NULL) {
            abortaPrograma();
    }

    //Abre o arquivo binario em modo de leitura(Read Binary)
    FILE* f = fopen(nome_arquivo, "rb");
    //Se nao existir o FILE retorna a lista vazia
    if (f == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com lista vazia.\n");
        return li;
    }

    CLIENTE cl;

    //Enquanto ler informaçoes da FILE (f) insere-os na lista.
    while (fread(&cl, sizeof(CLIENTE), 1, f) == 1) {

        insereOrdenada(li, cl);
    }
    //fecha o arquivo apos a leitura completa
    fclose(f);

    return li;//Retorna  a lista preenchida com todos os dados de f

}

//Funcao implementada para evitar que o usuarioq uebre o codigo por acidente
//Le o input do usuario em um loop infinito e classifica se valido ou nao de acordo com os parametros
//Se o usuario responder apropriadamente libera ele do loop
int validarOpcao() {
    char linha[MAX]; //Buffer para armazenar a entrada do usuario como string
    int opcao;

    //loop infinito
    while (1) {
        fgets(linha, sizeof(linha), stdin);//Le a entrada como string(mais segurança)

        //sscanf le o input(linha), tenta armazenar como double integer na variavel opcao.
        //Se conseguir (sscanf == 1) valida se eh um numero entr 1 e 7
        if (sscanf(linha, "%d", &opcao) == 1 && opcao >= 1 && opcao <= 7) {
            return opcao;//opcao validada!
        }
        printf("Entrada invalida! Digite um numero entre 1 e 7: ");
    }
}


//Funcao implementada para evitar que o usuarioq uebre o codigo por acidente
//Le o input do usuario em um loop infinito e classifica se valido ou nao de acordo com os parametros
//Se o usuario responder apropriadamente libera ele do loop

int validarCodigo() {
    char linha[MAX];
    int codigo;

    while (1) {
        fgets(linha, sizeof(linha), stdin);

        //sscanf le o input(linha), tenta armazenar como double integer na variavel codigo.
        //se sscanf == 1, vlaida se eh um valor positivo(acho que esses valores nao deveriam ser negativos)
        if (sscanf(linha, "%d", &codigo) == 1 && codigo > 0) {
            return codigo;//retorna com sucesso!
        }
        printf("Entrada invalida! Por favor, digite um numero inteiro positivo: ");
    }
}



// Função que coleta todos os dados exigidos pela struct CLIENTE
// Utiliza a função validarCodigo() para garantir que o código seja válido
// Retorna uma estrutura CLIENTE preenchida

CLIENTE coletaDadoCliente(){
    CLIENTE cl;//Variavel que armazena os dados

    //Coleta o codig do cliente (usa a funcao validarcodigo(explicada a cima))
    printf("Digite o codigo do cliente: ");
    cl.codigo = validarCodigo();

    //Coleta o nome do cliente
    printf("Digite o nome do cliente: ");
    fgets(cl.nome,sizeof(cl.nome),stdin);
    cl.nome[strcspn(cl.nome,"\n")] = '\0';

    //coleta o nome da empresa
    printf("Digite o nome da empresa: ");
    fgets(cl.empresa,sizeof(cl.empresa),stdin);
    cl.empresa[strcspn(cl.empresa,"\n")] = '\0';

    //coleta o departamento do cliente
    printf("Digite o nome do departamento: ");
    fgets(cl.departamento,sizeof(cl.departamento),stdin);
    cl.departamento[strcspn(cl.departamento,"\n")] = '\0';

    //coleta o telefone
    printf("Digite o telefone do cliente: ");
    fgets(cl.telefone,sizeof(cl.telefone),stdin);
    cl.telefone[strcspn(cl.telefone,"\n")] = '\0';

    //coleta o celular
    printf("Digite o celular do cliente: ");
    fgets(cl.celular,sizeof(cl.celular),stdin);
    cl.celular[strcspn(cl.celular,"\n")] = '\0';

    //coleta o email
    printf("Digite o email do cliente: ");
    fgets(cl.email,sizeof(cl.email),stdin);
    cl.email[strcspn(cl.email,"\n")] = '\0';

    return cl;//Retorna a estrutura CLIENTE preenchida com sucesso![ou deveria]
    }


    //Funcao busca um cliente na lista pelo codigo
    //Se encontrar, copia os dados para uma variavel(para evitar erros) e retorna 1(True)
    //Caso nao ache, retorne 0 (False)
int consultaCodigo(Lista* li, int codigo, CLIENTE* clEncontrado) {
    if (li == NULL) {
        abortaPrograma();
    }

    //Ponteiro auxiliar para percorrer a lista
    ELEM* noAtual = *li;

    //Loop para percorrer a Linked list
    while (noAtual != NULL) {
            //Parte que verifica se o codigo do cliente atual é igual ao codigo fornecido pelo user
        if (noAtual->dados.codigo == codigo) {
            //Se for copia os dados do cliente para a variavel auxiliar. IMPORTANTE porque O PRINT esta na MAIN
                *clEncontrado = noAtual->dados;
                return 1;//Retorna True
        }
        //Avança para prox no
        noAtual = noAtual->prox;
    }
    //Codigo nao encontrado na lista (printf certo na MAIN)
    return 0;//Return False
}

int consultaNome(Lista* li,char* nome_busca) {
    if (li == NULL || *li == NULL) {
        printf("\nA lista de clientes esta vazia ou invalida.\n");
        return 0;
    }

    ELEM* noAtual = *li;
    int clientes_encontrados_count = 0;

    printf("\n--- RESULTADOS DA BUSCA POR NOME: '%s' ---\n", nome_busca);
    printf("---------------------------------------------\n");

    while (noAtual != NULL) {
        if (strstr(noAtual->dados.nome, nome_busca)) {
            clientes_encontrados_count++;

            printf("\nCliente #%d (Nome Homonimo)\n", clientes_encontrados_count);
            printf("  Codigo: %d\n", noAtual->dados.codigo);
            printf("  Nome: %s\n", noAtual->dados.nome);
            printf("  Empresa: %s\n", noAtual->dados.empresa);
            printf("  Departamento: %s\n", noAtual->dados.departamento);
            printf("  Telefone: %s\n", noAtual->dados.telefone);
            printf("  Celular: %s\n", noAtual->dados.celular);
            printf("  E-mail: %s\n", noAtual->dados.email);
            printf("-------------------------------------------\n");
        }

        noAtual = noAtual->prox;
    }

    if (clientes_encontrados_count == 0) {
        printf("\nNenhum cliente com o nome '%s' foi encontrado.\n", nome_busca);
    } else {
        printf("\nTotal de %d cliente(s) encontrado(s) com o nome '%s'.\n", clientes_encontrados_count, nome_busca);
    }

    return clientes_encontrados_count;
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

    printf("Gostaria de editar algum dos dados? (s/n)\n");
    resposta = lerCharSN();
    if (resposta =='s'|| resposta=='S'){


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
}else{
    printf("Edicao cancelada!");
    return 1;
}
}

int removeOrdenado(Lista *li, int codigo){
    char resposta;
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *ant,*no = *li;
    while(no != NULL && no -> dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }
    if (no==NULL){
            printf("Cliente com o codigo %d nao encontrado",codigo);

        return 0;
    }
        printf("Cliente com o codigo %d encontrado\n",codigo);
        printf("  Nome: %s\n", no->dados.nome);
        printf("  Empresa: %s\n", no->dados.empresa);
        printf("  Departamento: %s\n", no->dados.departamento);
        printf("  Telefone: %s\n", no->dados.telefone);
        printf("  Celular: %s\n", no->dados.celular);
        printf("  E-mail: %s\n", no->dados.email);
        printf("----------------------------------------\n");
        printf("Gostaria de excluir este contato?[s/n]\n");
        resposta = lerCharSN();
        if (resposta != 's' && resposta != 'S'){
            return 0;
        }


    if(no == *li){
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


