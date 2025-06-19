#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    int opcao,status,codigo;
    char nome[99];

    CLIENTE cl;
    Lista *li = criaLista();

    do {
        printf("\n\nMENU");
        printf("\n1 Inserir novo cliente");
        printf("\n2 Exibir todos os contatos");
        printf("\n3 Buscar cliente pelo codigo");
        printf("\n4 Buscar cliente pelo nome");
        printf("\n5 Editar informações de um cliente");
        printf("\n6 Remover cliente dos contatos");
        printf("\n7 Sair da aplicacao");

        opcao = validarOpcao();

        switch(opcao){
            case 1:
                printf("\nInserir novo contato:\n")
                cl = coletaDadoCliente;
                status = insereOrdenada(li,cl);
                if(status){
                    printf("Cliente inserido com sucesso!")
                }else{
                    printf("Erro ao inserir o Cliente.");
                }
                break;

            case 2:
                printf("TO DO");
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
                printf("Digite o codigo do cliente: ");
                nome = validarNome();
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
    }


    printf("Hello world!\n");
    return 0;
}
