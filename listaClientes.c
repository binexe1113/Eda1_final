#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<locale.h>
#include "listaClientes.h"


//Struct elemento retirada exatamente do exemplo da aula sobre lista dinamicas, adaptada para struct CLIENTE
struct elemento{
    CLIENTE dados;
    struct elemento *prox;
};
typedef struct elemento ELEM;

//Retirada do exemplo da aula sobre lista dinamicas
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
    printf("\n Programa ser� encerrado");
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
            *li = (*li) ->prox; // avan�a para o prox
            free(no); // libera o no atual
        }
        //No fim, libera o ponteiro da lista
        free(li);
        //Se a lista foi alocada: aborta programa
    }else{
        printf("\nERRO FATAL! LISTA N�O ALOCADA");
        abortaPrograma();
        return;
    }
}

//Retirada exatamente do exemplo da aula sobre lista dinamicas
// Fun��o que verifica se a lista est� vazia.
// Retorna 1 se a lista estiver vazia, 0 caso contr�rio.
int listaVazia(Lista *li){
    if (li == NULL){
        abortaPrograma();

    } //Verifica se o a cabe�a da lista aponta para NULL
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//Insere um novo cliente na lista de maneira a deixar o cliente com menor codigo no topo da lista
//Retorna 0 (False) em caso de erro durante a execucao do programa
//Retorna o codigo do cliente e 1 (True) caso seja inserido com sucesso!
int insereOrdenada(Lista *li, CLIENTE cl){
    int codigoNovo;
    char sn;
    if (li == NULL){
        abortaPrograma();
    }
    ELEM *atual = *li;
    //Verifica duplicidade de codigos
    while (atual != NULL) {
        while (atual->dados.codigo == cl.codigo) {
            printf("Erro: J� existe um cliente com o c�digo %d registrado.\n", cl.codigo);
            printf("Gostaria de alterar o c�digo?[s/n]\n");
            sn = lerCharSN();
            if(sn == 's'|| sn =='S'){
                printf("\nInsira um novo c�digo diferente de %d:\n", atual->dados.codigo);
                codigoNovo = validarCodigo();
                cl.codigo=codigoNovo;
                }
            else{
            printf("Inser��o cancelada\n");
            return 0;
            }

        }
        atual = atual->prox;
    }
    //Aloca memoria para o novo elemento
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no==NULL){
        return 0;
    }

    //Copia os dados do cliente para um novo n�
    no->dados = cl;

    //Se a lista (li) estiver vazia, insere no inicio (0)
    if(listaVazia(li)){
        no->prox=(*li);
        *li=no;
        return cl.codigo;

    }else{
        //Se nao estiver vazia percorre a lista at� encontrar a posicao correta
        ELEM *ant, *atual = *li;

        // Procura a posi��o onde o novo c�digo seja maior que os anteriores
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
        printf("Arquivo de dados n�o encontrado. Iniciando com lista vazia.\n");
        return li;
    }

    //Inicializo variavel cl do tipo CLIENTE
    CLIENTE cl;

    //Enquanto ler informa�oes da FILE (f) insere-os na lista.
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
        fgets(linha, sizeof(linha), stdin);//Le a entrada como string(mais seguran�a)

        //sscanf le o input(linha), tenta armazenar como double integer na variavel opcao.
        //Se conseguir (sscanf == 1) valida se eh um numero entr 1 e 8
        if (sscanf(linha, "%d", &opcao) == 1 && opcao >= 1 && opcao <= 8) {
            return opcao;//opcao validada!
        }
        printf("Entrada inv�lida! Digite um numero entre 1 e 8: ");
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
        printf("Entrada inv�lida! Por favor, digite um n�mero inteiro positivo: ");
    }
}



// Fun��o que coleta todos os dados exigidos pela struct CLIENTE
// Utiliza a fun��o validarCodigo() para garantir que o c�digo seja v�lido
// Retorna uma estrutura CLIENTE preenchida

CLIENTE coletaDadoCliente(){
    CLIENTE cl;//Variavel que armazena os dados

    //Coleta o codig do cliente (usa a funcao validarcodigo(explicada a cima))
    printf("Digite o c�digo do cliente: ");
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
            //Parte que verifica se o codigo do cliente atual � igual ao codigo fornecido pelo user
        if (noAtual->dados.codigo == codigo) {
            //Se for copia os dados do cliente para a variavel auxiliar. IMPORTANTE porque O PRINT esta na MAIN
                *clEncontrado = noAtual->dados;
                return 1;//Retorna True
        }
        //Avan�a para prox no
        noAtual = noAtual->prox;
    }
    //Codigo nao encontrado na lista (printf certo na MAIN)
    return 0;//Return False
}

//Funcao para transformar uma STRING em LOWERCASE
//Retorna uma variavel auxiliar, sendo a string em lowercase (NAO ALTERA A STRING ORIGINAL)
//Necessaria para a funcao consultaNome
char* strToLower(char* str) {
    int tam;
    //Verifica se a string de entrada � NULL
    if (str == NULL){
        return NULL;
    }

    //Calcula o tamanho da string, na variavel tam
    tam = strlen(str);
    //Aloca dinamicante a memoria para a nova string
    char* lower = malloc(tam + 1); // +1 para o caractere nulo \0

    //Verifica�ao de erro na aloca�ao
    if (lower == NULL) {
        perror("Erro ao alocar mem�ria");
        return NULL;
    }

    //Converte cada caractere da string de entrada para minusculo e armazena na nova string 'lower'
    for (int i = 0; i < tam; i++) {
        lower[i] = tolower(str[i]);
    }
    //Adiciona '\0' no fim da nova string!
    lower[tam] = '\0';

    return lower;//Sucesso! Retorna a nova string em minusculo SEM ALTERAR A ORIGINAL!
}


//Funcao Para consultar a lista por nome e retornar os resultados correspondentes
//Essa funcao se tornou Case-Insensitive por causa da func strToLower(declarada acima)
int consultaNome(Lista* li,char* nomeBusca) {

    int clientesEncontradosCount=0;
    char* nomeBuscaLower = strToLower(nomeBusca);//Converte input do usuario para minusculo SEM ALTERAR A STRING ORIGINAL

    //Verifica�ao de seguran�a
    if (li == NULL) {
            abortaPrograma();
            return 0;
    }

    //Inicializando ponteiro para percorrer a lista
    ELEM* noAtual = *li;

    printf("\n---- RESULTADOS DA BUSCA POR NOME: '%s' ----\n", nomeBusca);
    printf("---------------------------------------------\n");

    //Loop para percorrer a lista
    //Percorre a lista ocnvertendo o nome para minusculo e comparando com o nomeBusca
    //Se der match, contador+1 e exibe as informacoes do cliente
    while (noAtual != NULL) {
            //Converte o nome contido na lista para minusculo(SEM ALTERAR A STRING ORIGINAL)
            char* nomeNoAtualLower = strToLower(noAtual->dados.nome);
        //Verifica se nomeNoAtualLower cont�m nomeBuscaLower dentro de si
        if (strstr(nomeNoAtualLower, nomeBuscaLower)){ //if (True)
            clientesEncontradosCount++;

            //Exibe informa�oes
            printf("\nCliente com similaridade de busca #%d\n", clientesEncontradosCount);
            printf("  C�digo: %d\n", noAtual->dados.codigo);
            printf("  Nome: %s\n", noAtual->dados.nome);
            printf("  Empresa: %s\n", noAtual->dados.empresa);
            printf("  Departamento: %s\n", noAtual->dados.departamento);
            printf("  Telefone: %s\n", noAtual->dados.telefone);
            printf("  Celular: %s\n", noAtual->dados.celular);
            printf("  E-mail: %s\n", noAtual->dados.email);
            printf("-------------------------------------------\n");

        }
        //Libera a memoria alocada para a string neste no
        free(nomeNoAtualLower);

        //Avan�a para o Proximo cliente da lista
        noAtual = noAtual->prox;
    }//Fim do loop
        //Libera a memoria alocada para string fornecida pelo usuario
        free(nomeBuscaLower);

    //Mensagem para o usuario
    if (clientesEncontradosCount == 0) {
        printf("\nNenhum cliente com o nome '%s' foi encontrado.\n", nomeBusca);
    } else {
        printf("\nTotal de %d cliente(s) encontrado(s) com o nome '%s'.\n", clientesEncontradosCount, nomeBusca);
    }


    return 1;//True
}

//Funcao auxiliar para checagem de seguran�a
//Implementei para evitar que o usuario por acidente quebre o programa
//Uso dentro de outras funcoes, para garantir que o usuario ,quando necessario, responda APENAS s OU n
char lerCharSN() {
    //Armazeno o input do usuario em uma string
    char input[MAX];
    //Loop infinito, so sai no return
    while (1) {
        //Coleta o dado do usuario
        if (fgets(input, sizeof(input), stdin)) {
            //Verifica se a primeira letra do input � valida, depois se a segunda � \n
            //Lembrando que em fgets armazena o input at� o /n sendo: input[0]='s',input[1]='\n',input[2]='\0'
            if ((input[0] == 's' || input[0] == 'S' || input[0] == 'n' || input[0] == 'N') && input[1] == '\n') {
                return input[0];//Retornar (s,S,n,N)
            }
        }
        printf("Resposta inv�lida! Digite 's' ou 'n': ");//Mensagem de erro para o user
    }
}


//Funcao para editar os dados do cliente, reconhece o alvo da aedicao atravez do codigo fornecido pelo usuario

int editaCliente(Lista* li, int codigoBusca) {

    char resposta;//Variavel auxiliar para a funcao lerChar

    //Checagem de seguran�a
    if (li == NULL) {
        abortaPrograma();
        return 0;
    }

    //Inicializa o ponteiro que vai percorrer a lista
    ELEM* noAtual = *li;

    //Loop de verifica�ao, enquanto o n� atual nao for nulo e os codigos forem diferente, avan�a para o proximo no
    while (noAtual != NULL && noAtual->dados.codigo != codigoBusca) {
        noAtual = noAtual->prox;
    }

    //Isso acontece se percorrer a lista e encontrar o codigo
    //Printa todas as informa�oes do cliente

    printf("\nCliente com c�digo %d encontrado.", codigoBusca);
    printf("Dados atuais:\n");
    printf("  Nome: %s\n", noAtual->dados.nome);
    printf("  Empresa: %s\n", noAtual->dados.empresa);
    printf("  Departamento: %s\n", noAtual->dados.departamento);
    printf("  Telefone: %s\n", noAtual->dados.telefone);
    printf("  Celular: %s\n", noAtual->dados.celular);
    printf("  E-mail: %s\n", noAtual->dados.email);
    printf("----------------------------------------\n");

    //Verifica�ao de seguran�a, confirma se o usuario realmente quer editar este cliente
    printf("Gostaria de editar algum dos dados? (s/n)\n");
    resposta = lerCharSN();
    if (resposta =='s'|| resposta=='S'){


    //Se o usuario confirmou a edi�ao, copio os dados atuais para uma nova variavel da struct CLIENTE
    //Sei que n�o precisa, poderia fazer direto, mas desse jeito acho que � mais "seguro"
    //colconado direto as novas informa�oes no noAtual deu alguns bugs
        CLIENTE novosDados = noAtual->dados;

    //Todo esse bloco a seguir tem o mesmo funcionamento, pergunta se o usuario quer mudar o dado
        //Se o usuario quiser, armazena a nova informa�ao dentro de novosDados
        //Sen�o, o dado antigo ja esta copiado na variavel novosDados

    //Inicio do bloco
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

    //Fim do bloco

    //Passa as informa�oes da var novosDados para o cliente atual
        noAtual->dados = novosDados;

    //Mensagem de suceso
        printf("\nInformacoes do cliente com codigo %d atualizadas com sucesso!\n", codigoBusca);
        return 1;//Return True
    }else{
    //Mensagem de erro
        printf("\nEdicao cancelada!\n");
        return 0;//Return False
    }
}

//Funcao  remove ordenado (extraida diretamente dos slides da aula 11, com pequenas altera��es)
int removeOrdenado(Lista *li, int codigo){

    //var auxiliar para a funcao lerCharSN
    char resposta;
    if(li == NULL){
        abortaPrograma();
    }
    //Declara dois ponteiros: no para percorrer a lista. ant para guardar o elemento anterior ao no
    ELEM *ant,*no = *li;

    //Loop para percorrer a lista at� no ser nulo ou no dar match com a busca
    while(no != NULL && no -> dados.codigo != codigo){
        //passa variavel no para a ant
        ant = no;
        //avan�a com o no para o proximo cliente
        no = no->prox;
    }

    //Se acabar a lista sem encontrar
    if (no==NULL){
            printf("Cliente com o c�digo %d nao encontrado",codigo);

        return 0;//Return False
    }
        //Se encontrar, printa as informa�oes do cliente
        printf("Cliente com o c�digo %d encontrado\n",codigo);
        printf("  Nome: %s\n", no->dados.nome);
        printf("  Empresa: %s\n", no->dados.empresa);
        printf("  Departamento: %s\n", no->dados.departamento);
        printf("  Telefone: %s\n", no->dados.telefone);
        printf("  Celular: %s\n", no->dados.celular);
        printf("  E-mail: %s\n", no->dados.email);
        printf("----------------------------------------\n");
        //Pergunta de confirma�ao, para maior seguran�a do sistema
        printf("Gostaria de excluir este contato?[s/n]\n");
        resposta = lerCharSN();
        if (resposta != 's' && resposta != 'S'){ //Se a resposta for diferente de s ou S
            return 0;//Retorna Falso(processo de exclusao terminado, lido com isso na main)
        }

    //Verifica se o cliente a ser removido � o primeiro da lista
    if(no == *li){
        *li = no -> prox;//Se for, muda o ponteiro da lista para o proximo cliente


    }else {//Sen�o, ant pula o no atual, e aponta direto para o prox, removendo noAtual da lista
        ant->prox = no -> prox;
    }
    //Armazena o codigo do cliente a ser excluido(para uso na main)
    codigo = no -> dados.codigo;
    //Libera a memoria alocada
    free(no);
    return codigo;//Retorna o codigo do cliente excluido e 1(True)
}

//Funcao para salvar a lista de contatos EM ARQUIVO BINARIO

int salvarLista(Lista* li, const char* nomeArquivo) {
    if (li == NULL) {
        abortaPrograma();
        return 0;//ERRO Retorna False
    }
    //Aviso para debug
    if (*li == NULL) {
        printf("Aviso: Lista de clientes vazia. Criando/substituindo arquivo vazio.\n");
    }

    //Abre o arquivo em modo escrita em binario(write binary (WB))
    FILE* fp = fopen(nomeArquivo, "wb");
    if (fp == NULL) {
            //Se nao poder abrir o arquivo, exibe mensagem de erro
        printf("Erro: Nao foi possivel abrir o arquivo '%s' para escrita.\n", nomeArquivo);
        return 0;//ERRO Retorna False
    }

    //Inicializa o ponteiro para percorrer a lista
    ELEM* noAtual = *li;

    int clientesSalvos = 0;

    //Loop para percorrer a lista inteira
    while (noAtual != NULL) {

        //Escreve os dados do cliente atual no arquivo, fwrite retorna 1 se conseguir armazenar 1 bloco de cliente e armazena esse valor na variavel auxiliar
        int escritaSucesso = fwrite(&(noAtual->dados), sizeof(CLIENTE), 1, fp);

        //Checagem para ver se a variavel auxiliar tem algum valor diferente de 1, se tiver encerra a funcao
        if (escritaSucesso != 1) {
            printf("Erro: Falha ao escrever os dados do cliente no arquivo.\n");
            fclose(fp);
            return 0;//Falha Return 0(False)
        }
        //Se tudo foi um sucesso, adiciona ao contador e passa para o proximo n�
        clientesSalvos++;
        noAtual = noAtual->prox;

    }//Fim do loop
    fclose(fp);//Fecha o arquivo
    printf("Dados de %d cliente(s) salvos com sucesso em '%s'.\n", clientesSalvos, nomeArquivo);

    return 1;//Sucesso!(True)
}

//Funcao para exibir todos os contatos da lista

void exibeTodosContatos(Lista* li) {
    if (li == NULL) {
        abortaPrograma();
        return;
    }
    if (listaVazia(li)){//Checagem para ver se o ponteiro da lista esta vazio
        printf("\nNenhum contato na lista\n");
        printf("Adicione algum contato para exibi-lo aqui.");
        return;
    }

    printf("\nRelatorio de todos os contatos:\n");

    //Inicializa o ponteiro para percorrer toda a lista
    ELEM* noAtual = *li;

    int contador = 0;

    //Loop para fazer o n� percorrer a Lista inteira
    while (noAtual != NULL) {
            //Enquanto o n� nao � nulo, soma 1 ao contador e printo as informa��es do cliente
        contador++;
        printf("--------------------------------------\n");
        printf("  C�digo: %d\n", noAtual->dados.codigo);
        printf("  Nome: %s\n", noAtual->dados.nome);
        printf("  Empresa: %s\n", noAtual->dados.empresa);
        printf("  Departamento: %s\n", noAtual->dados.departamento);
        printf("  Telefone: %s\n", noAtual->dados.telefone);
        printf("  Celular: %s\n", noAtual->dados.celular);
        printf("  E-mail: %s\n", noAtual->dados.email);
        printf("--------------------------------------\n");

        noAtual = noAtual->prox; //Passa para o proximo cliente,avan�a o no
    }

    printf("Total de contatos na lista: %d",contador);
    printf("\n--- FIM DO RELATORIO ---\n");

}


