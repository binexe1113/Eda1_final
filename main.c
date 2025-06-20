#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "listaClientes.h"

int main()
{
    int opcao,status,codigo;
    char nome[99];
    CLIENTE cl,novosDados;

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
                if(consultaCodigo(li,codigo,&cl)){
                    printf("\nCliente encontrado:");
                    printf("\nCodigo: %d", cl.codigo);
                    printf("\nNome: %s", cl.nome);
                    printf("\nEmpresa: %s",cl.empresa);
                    printf("\nDepartamento: %s",cl.departamento);
                    printf("\nTelefone: %s",cl.telefone);
                    printf("\nCelular: %s",cl.celular);
                    printf("\nE-mail: %s",cl.email);
                } else{
                    printf("\nCliente com o codigo %d nao encontrado.",codigo);
                }
                break;

            case 4:
                printf("Buscar cliente pelo nome: \n");
                printf("Digite o nome do cliente: ");
                fgets(nome,sizeof(nome),stdin);
                nome[strcspn(nome,"\n")] = '\0';
                if(consultaNome(li,nome,&cl)){
                    printf("\nCliente encontrado:");
                    printf("\nCodigo: %d", cl.codigo);
                    printf("\nNome: %s", cl.nome);
                    printf("\nEmpresa: %s",cl.empresa);
                    printf("\nDepartamento: %s",cl.departamento);
                    printf("\nTelefone: %s",cl.telefone);
                    printf("\nCelular: %s",cl.celular);
                    printf("\nE-mail: %s",cl.email);
                } else{
                    printf("\nCliente com o nome %s nao encontrado.",nome);
                }
                break;

            case 5:
                printf("Digite o codigo do cliente que sera alterado:\n");
                codigo = validarCodigo();
                if(consultaCodigo(li,codigo,&cl)){
                    status = editaCliente(li,codigo);
                    if (status){
                        printf("Informacoes editadas com sucesso!\n");
                    }else{
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
                if(status){
                    printf("\nCliente removido com sucesso da lista de contatos");
                }else{
                    printf("\nCliente nao encotnrado na lista de contatos");
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
