#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include<locale.h>
#include "listaClientes.h"

int main()
{
    setlocale(LC_ALL, "portuguese");
    int opcao,status,codigo;
    char nome[MAX];
    char sn;
    CLIENTE cl,novosDados,clienteEncontrado,clienteEncontradoNome;

    //Carregar a lista usando funcção carregaLista
    Lista *li = carregaLista("lista_de_contatos.bin");
    //Checagem de segurança
    if(li==NULL){
        printf("\nERRO FATAL! Nao foi possivel carregar ou inicializar a lista de contatos.");
        printf("\nENCERRANDO...\n\n\n");
        abortaPrograma();
        return 0;
    }

    //O menu fica dentro de um loop (do while), que repete as açoes até o usuario escolher a opcao 8(sair do programa)
    // ao escolher uma opcao o usuario se coloca dentro de um switch case, e ao encerrar a operaçao naquele caso, realiza um break, que o retira do case e devolve ao menu
    do {
        system("cls");
        printf("\n\n--------------MENU---------------");
        printf("\nInsira uma das opções de 1 a 8:\n");
        printf("\n1 Inserir novo cliente");
        printf("\n2 Exibir todos os contatos");
        printf("\n3 Buscar cliente pelo código");
        printf("\n4 Buscar cliente pelo nome");
        printf("\n5 Editar informações de um cliente");
        printf("\n6 Remover cliente dos contatos");
        printf("\n7 Salvar lista");
        printf("\n8 Sair da apliçãcao salvando a lista\n");
        printf("---------------------------------\n\n");
        printf("Insira uma opção: ");

        opcao = validarOpcao();//Uso de validarOpcao, forçando o usuario a escolher apenas um numero entre 1 e 8

        switch(opcao){
            case 1://Opcao para inserir um novo cliente
                system("cls");
                printf("\nInserir novo contato:\n");
                cl = coletaDadoCliente();//Usa a variavel cl para armazenar os dados do novo cliente
                status = insereOrdenada(li,cl);//Usa a variavel status para conferir o retorno da funcao, a checagem de codigo repetido aconte aqui, no insereOrdenada
                if(status){//Se 1:
                    printf("Cliente inserido com sucesso!");
                }else{//Se 0:
                    printf("Erro ao inserir o Cliente.");
                }
                system("Pause");
                break;

            case 2://Opcao para exibir todos os contatos
                system("cls");
                printf("Exibindo todos os contatos...");
                exibeTodosContatos(li);//Funcao que exibe todos os contatos contidos na lista
                system("Pause");
                break;

            case 3://Opcao para buscar o cliente pelo codigo
                system("cls");
                printf("Buscar cliente pelo código: \n");
                printf("Digite o código do cliente: ");
                codigo = validarCodigo();//Funcao para validar a entrada do usuario como codigo(apenas numeros inteiros)
                if(consultaCodigo(li,codigo,&clienteEncontrado)){ //Se consultaCodigo retornar 1, printa as informações do cliente
                    printf("\nCliente encontrado:");
                    printf("\nCódigo: %d", clienteEncontrado.codigo);
                    printf("\nNome: %s", clienteEncontrado.nome);
                    printf("\nEmpresa: %s",clienteEncontrado.empresa);
                    printf("\nDepartamento: %s",clienteEncontrado.departamento);
                    printf("\nTelefone: %s",clienteEncontrado.telefone);
                    printf("\nCelular: %s",clienteEncontrado.celular);
                    printf("\nE-mail: %s",clienteEncontrado.email);
                    printf("\n--------------------------------------\n");
                } else{ //Se não, avisa o usuario
                    printf("\nCliente com o código %d nao encontrado.\n",codigo);
                }
                system("Pause");
                break;

            case 4://Buscar cliente pelo nome
                system("cls");
                printf("Buscar cliente pelo nome: \n");
                printf("Digite o nome do cliente: ");
                fgets(nome,sizeof(nome),stdin);//fgets para ler string do usuario
                nome[strcspn(nome,"\n")] = '\0';//limpar o input do usuario

                consultaNome(li,nome);//Executa a funcao consultaNome com o input do usuario e a lista de contatos. Toda a logica acontece lá
                system("Pause");
                break;

            case 5://Editar informacoes de um cliente
                system("cls");
                printf("Digite o código do cliente que sera alterado:\n");
                codigo = validarCodigo();//Funcao para validar codigo para validar input do usuario de acordo com as conformidades de um "codigo"
                if(consultaCodigo(li,codigo,&cl)){ //Usa a func consultaCodigo com o input do usuario
                    status = editaCliente(li,codigo);//Armazena o retorno dela (0 ou 1)
                    if (!status){ //Se for 0:(oposto de 1)
                        printf("\nEdição nao realizada\n");
                        system("Pause");
                        break;

                    }else{//Se for 1:
                        //Printfs dentro da func editaCliente
                        system("Pause");
                        break;
                    }

                }else{//Se nao achar nenhum cliente com o codigo forncecido pelo usuario
                    printf("Cliente com o código %d nao encontrado.\n",codigo);
                    system("Pause");
                    break;

                }

            case 6://Opcao para remover um cliente da Lista
                system("cls");
                printf("Tem certeza que deseja remover algum cliente?[s/n]\n");
                sn = lerCharSN();
                if(sn == 'S' || sn == 's'){//Confirmaçao inicial, para seguir com a operaçao
                    printf("\nDigite o código do cliente que sera removido: ");
                    codigo=validarCodigo();//Funcao para validar codigo para validar input do usuario de acordo com as conformidades de um "codigo"
                    //Variavel status usada para receber 1 ou 0
                    status = removeOrdenado(li,codigo);//Funcao removerOrdenado executa a logica de Remover o cliente da lista
                    if(!status){//Se receber o oposto de 1 (0), nao remover cliente
                        printf("\nProcesso de remoção de cliente descontinuado!");
                        printf("\nNenhum cliente removido! \n");
                        system("Pause");
                        break;
                    }else{//Se receber 1, ja removeu o cliente
                        printf("\nProcesso de remoção finalizado com sucesso!");
                        system("Pause");
                        break;
                }
                }else{
                    printf("Processo de remoção de cliente terminado");
                    printf("\nNenhum cliente removido! \n");
                    system("Pause");
                    break;
                }

            case 7://Opcao para salvar a lista sem fechar o app
                system("cls");
                printf("Salvando alterações na lista..............\n");
                //Usa a variavel status para armazenar o retorno da func salvarLista
                status = salvarLista(li,"lista_de_contatos.bin");//Usa a funcao salvarLista para salvar a lista no arquivo
                system ("Pause");
                break;
                if(!status){//Se recebe o oposto de 1 (0), houve falha
                    printf("\nFalha no salvamento de dados");
                    system("Pause");
                    break;
                }
            case 8://Opcao para sair do programa(Salvando os dados)
                system("cls");
                printf("Salvando dados antes de sair...\n");
                if (salvarLista(li, "lista_de_contatos.bin")) { //Usa a funcao salvarLista para armazenar os dados
                    printf("Dados salvos com sucesso!\n");
                    printf("Saindo com seguranca..............\n");
                    apagaLista(li);//Usa a funcao apagaLista para liberar a memoria alocada
                    system("Pause");
                    //Return 0 faz com que o loop termine e encerre o programa
                    return 0;//Fim do programa!
                } else {//Se o salvamento falhar evita que o usuario saia com a lista não salva
                    printf("Falha no salvamento de dados. Retornando ao menu...\n");
                    system("Pause");
                    break;
                }

        }

    }while (1); //O loop so acaba quando main retornar 0

    return 0;//Esse return nunca deveria ser acessado pelo programa, mas por desencargo de consciencia ele está aqui, depois do do while.
}
