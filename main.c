#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "listaClientes.h"

int main()
{
    int opcao,status,codigo;
    char nome[99];
    CLIENTE cl,novosDados,clienteEncontrado,clienteEncontradoNome;

    Lista *li = carregaLista("lista_de_contatos.bin");
    if(li==NULL){
        printf("\nERRO FATAL! Nao foi possivel carregar ou inicializar a lista de contatos.");
        printf("\nENCERRANDO...\n\n\n");
        return 1;
    }

    do {
        printf("\n\n--------------MENU---------------");
        printf("\nInsira uma das opcoes de 1 a 7:\n");
        printf("\n1 Inserir novo cliente");
        printf("\n2 Exibir todos os contatos");
        printf("\n3 Buscar cliente pelo codigo");
        printf("\n4 Buscar cliente pelo nome");
        printf("\n5 Editar informações de um cliente");
        printf("\n6 Remover cliente dos contatos");
        printf("\n7 Sair da aplicacao\n");
        printf("---------------------------------\n\n");
        printf("Opcao: ");

        opcao = validarOpcao();

        switch(opcao){
            case 1:
                printf("\nInserir novo contato:\n");
                cl = coletaDadoCliente();
                status = insereOrdenada(li,cl);
                if(status){
                    printf("Cliente inserido com sucesso!");
                }else{
                    printf("Erro ao inserir o Cliente.");
                }
                break;

            case 2:
                printf("Exibindo todos os contatos...");
                exibeTodosContatos(li);
                break;

            case 3:

                printf("Buscar cliente pelo codigo: \n");
                printf("Digite o codigo do cliente: ");
                codigo = validarCodigo();
                system("cls");
                if(consultaCodigo(li,codigo,&clienteEncontrado)){
                    printf("\nCliente encontrado:");
                    printf("\nCodigo: %d", clienteEncontrado.codigo);
                    printf("\nNome: %s", clienteEncontrado.nome);
                    printf("\nEmpresa: %s",clienteEncontrado.empresa);
                    printf("\nDepartamento: %s",clienteEncontrado.departamento);
                    printf("\nTelefone: %s",clienteEncontrado.telefone);
                    printf("\nCelular: %s",clienteEncontrado.celular);
                    printf("\nE-mail: %s",clienteEncontrado.email);
                    printf("\n--------------------------------------\n");
                } else{
                    printf("\nCliente com o codigo %d nao encontrado.",codigo);
                }
                system("Pause");
                break;

            case 4:
                printf("Buscar cliente pelo nome: \n");
                printf("Digite o nome do cliente: ");
                fgets(nome,sizeof(nome),stdin);
                nome[strcspn(nome,"\n")] = '\0';
                system("cls");
                consultaNome(li,nome);
                system("Pause");
                break;

            case 5:
                printf("Digite o codigo do cliente que sera alterado:\n");
                codigo = validarCodigo();
                if(consultaCodigo(li,codigo,&cl)){
                    status = editaCliente(li,codigo);
                    if (!status){
                        printf("Erro! Falha na edicao.");
                    }
                    break;
                }else{
                    printf("Cliente com o codigo %d nao encontrado.",codigo);

                };
            case 6:
                printf("\nDigite o codigo do cliente que sera removido: ");
                codigo=validarCodigo();
                status = removeOrdenado(li,codigo);
                if(!status){
                    printf("\nProcesso de remocao de cliente descontinuado!");
                }else{
                    printf("\nProcesso de remocao finalizado com sucesso!");
                }

        }
    } while(opcao != 7);
    if(salvarLista(li,"lista_de_contatos.bin")){
        printf("\nSaindo com seguranca........");
    }else{
        printf("\nFalha no salvamento de dados.");
        }

    apagaLista(li);
    return 0;
}
