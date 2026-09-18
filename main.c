#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// ARRAYS (vetores)
#define MAX_ALUNOS 100
#define MAX_NOME 100

float av1[MAX_ALUNOS];
float av2[MAX_ALUNOS];
float av3[MAX_ALUNOS];
char alunos[MAX_ALUNOS][MAX_NOME];

int totalAlunos = 0;

//limpaInfo joga fora o que sobrou digitado no teclado (tipo o Enter) depois de uma leitura
void limparInfo() {
    int c;// guarda, um de cada vez, cada caractere que tiramos do
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//pede nome do aluno e do sai quando vier um nome valido
void validarNome(char nome[]) {
    bool valido = false;

    while (!valido) {
        printf("Insira o nome: ");
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // remove o Enter do final
        //bloqueia nome vazio
        if (strlen(nome) == 0) {

            printf("\n===============================================\n");
            printf("Opcao invalida, insira um nome valido.\n");
            printf("===============================================\n");
            continue;
        }
        bool somenteLetras = true;
        for (int i = 0; i < (int)strlen(nome); i++) {
            if (!isalpha((unsigned char) nome[i]) && nome[i] != ' ') {
                somenteLetras = false;//acha algo que nao e letra nem espaco
                break;
            }
        }
        //bloqueia nome que nao e apenas letras
        if (!somenteLetras) {
            printf("\n===============================================\n");
            printf("Opcao invalida, insira um nome valido.\n");
            printf("===============================================\n\n");
            continue;
        }

        valido = true;
    }
}
float validarNota(const char *mensagem) {
    float nota;

    while (true) {
        printf("%s", mensagem);
        //bloqueia quando oq foi digitado nao e numero
        if (scanf("%f", &nota) != 1) {
            limparInfo();
            printf("\n===============================================\n");
            printf("Opcao invalida, insira uma nota valida.\n");
            printf("===============================================\n");
            continue;
        }
        //bloqueia notas que nao esta entre 0 e 10
        if (nota < 0 || nota > 10) {
            limparInfo();
            printf("\n===============================================\n");
            printf("Opcao invalida, a nota deve ser entre 0 e 10.\n");
            printf("===============================================\n\n");
            continue;
        }
        limparInfo();
        return nota;
    }
}
//junta as informacao (nome e nota) guarda nos vetores globais
void cadastrar() {
    if (totalAlunos >= MAX_ALUNOS) {
        printf("\n===============================================\n");
        printf("Limite maximo de alunos atingido!\n");
        printf("===============================================\n");
        return; 
    }

    validarNome(alunos[totalAlunos]);
    float notaAv1 = validarNota("Insira a nota da av1: ");
    float notaAv2 = validarNota("Insira a nota da av2: ");
    float notaAv3 = validarNota("Insira a nota da av3: ");
    
    //guarda as notas dentro do nome dos alunos certos
    av1[totalAlunos] = notaAv1;
    av2[totalAlunos] = notaAv2;
    av3[totalAlunos] = notaAv3;

    printf("\nUsuario %s criado!\n", alunos[totalAlunos]);
    totalAlunos++;
}

int main() {
    bool encerrar = false;
    // Exibe o titulo do programa
    printf("\n==============================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de notas");
    printf("\n==============================================\n");
    printf("\n");
    while (!encerrar) {
        // Exibe as opcoes do programa
        printf("\n====================\n");
        printf("\n");
        printf("1 - Cadastrar alunos e notas\n");
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

        limparInfo(); // limpa o Enter que sobra do scanf("%d")

        switch (opcao) {
            // usuario escolhe a opcao 1, o programa mostra cadastrar
            case 1:
                cadastrar();
                break;
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
