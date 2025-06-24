// Tamanho máximo das strings de dados do cliente (nome, empresa, etc.)

#define MAX 99

//Estrutura que representa os dados de um cliente
typedef struct cliente{
    int codigo;
    char nome[MAX];
    char empresa[MAX];
    char departamento[MAX];
    char telefone[MAX];
    char celular[MAX];
    char email[MAX];
}CLIENTE;

//Ponteiro para o elemento da lista
typedef struct elemento* Lista;

//Cria e inicializa a lista
Lista *criaLista();

//Finaliza o programa quando a li ==NULL
void abortaPrograma();

//Apaga e libera toda a memória da lista de clientes
void apagaLista(Lista *li);

//Verifica se a cabeça da lista aponta para NULL
int listaVazia(Lista *li);

//Carrega os dados dos clientes a aprtir de um arquivo binario e retorna uma nova lista
Lista* carregaLista(char* nome_arquivo);

//Converte os caracterers de uma string para minusculo e a retorna
char* strToLower(char* str);

//Coleta os dados de um cliente e o retorna para a estrutura CLIENTE devidamente preenchida
CLIENTE coletaDadoCliente();

//Insere um cliente na lista de forma ordenada pelo codigo
int insereOrdenada(Lista *li, CLIENTE cl);

//Valida o input do usuario para um codigo(inteiro positivo)
int validarCodigo();

//Valida o input do usuario para uma opcao do menu(inteiro entre 1 e 8)
int validarOpcao();

//Procura um cliente na lista pelo codigo
int consultaCodigo(Lista* li, int codigo, CLIENTE* clEncontrado);

//Procura um cliente na lista pelo nome
int consultaNome(Lista* li,char* nome_busca);

//Edita um cliente na lista, a partir do codigo fornecido pelo usuario
int editaCliente(Lista* li, int codigoBusca);

//Remove um cliente da lista com base no codigo fornecido pelo usuario, mantendo a ordem de codigos
int removeOrdenado(Lista *li, int codigo);

//Valida o input do usuario retornando sim ou nao (s,S,n,N)
char lerCharSN();

//Salva os clientes da lista em um arquivo binario
int salvarLista(Lista* li, const char* nome_arquivo);

//Exibe todos os contatos da lista
void exibeTodosContatos(Lista* li);



