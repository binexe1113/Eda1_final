#define MAX 99

typedef struct cliente{
    int codigo;
    char nome[MAX];
    char empresa[MAX];
    char departamento[MAX];
    char telefone[MAX];
    char celular[MAX];
    char email[MAX];
}CLIENTE;

typedef struct elemento* Lista;

Lista *criaLista();

void abortaPrograma();

void apagaLista(Lista *li);

int listaVazia(Lista *li);

Lista* carregaLista(char* nome_arquivo);


int validarOpcao();

CLIENTE coletaDadoCliente();

int insereOrdenada(Lista *li, CLIENTE cl);

int validarCodigo();

int validarOpcao();

int consultaCodigo(Lista* li, int codigo, CLIENTE* clEncontrado);

int consultaNome(Lista* li,char* nome_busca);

int editaCliente(Lista* li, int codigoBusca);

int removeOrdenado(Lista *li, int codigo);

char lerCharSN();

int salvarLista(Lista* li, const char* nome_arquivo);

void exibeTodosContatos(Lista* li);



