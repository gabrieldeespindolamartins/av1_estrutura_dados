#include <stdio.h>
#include <stdbool.h>

int main() {
    bool encerrar = false;
    // Exibe o titulo do programa
    printf("\n==============================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de notas");
    printf("\n==============================================\n");
    printf("\n");
    while (!encerrar) {
        printf("Escolha uma opcao:\n");
        // Exibe as opcoes do programa
        printf("0 - Finalizar o programa\n");
        printf("\n");
        // Solicita a opcao do usuario
        printf("\n====================\n");
        printf("Selecione uma opcao: ");
        printf("\n====================\n");
        int opcao;
        // Verifica se a opcao do usuario é um numero inteiro valido
        if (scanf("%d", &opcao) != 1) {
            int c;
            //Limpa o a caixa de texto do usuario
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("\n===============================================\n");
            printf("Erro de leitura: Digite um numero inteiro valido\n");
            printf("===============================================\n");
            printf("\n");
            continue;
        }

        switch (opcao) {
            // Caso o usuario escolha a opcao 0, o programa finaliza
            case 0:
                printf("\n===============================================\n");
                printf("Finalizando o programa...\n");
                printf("===============================================\n");
                printf("\n");
                encerrar = true;
                break;

            // Caso o usuario escolha uma opcao diferente de 0, o programa exibe uma mensagem de erro
            default:
                printf("\n==============\n");
                printf("Opcao invalida\n");
                printf("==============\n");
                printf("\n");
        }
    }

    return 0;
}
