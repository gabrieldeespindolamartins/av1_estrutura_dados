
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALUNOS 100
#define TAM_NOME 100

// ==============================================================================
// FUNÇÕES AUXILIARES DE VALIDAÇÃO
// ==============================================================================

// Função para validar se o nome contém apenas letras e espaços
int validar_nome(const char *nome) {
    int tem_letra = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (nome[i] == '\n') continue; // Ignora a quebra de linha do fgets
        if (isalpha(nome[i])) {
            tem_letra = 1;
        } else if (nome[i] != ' ') {
            return 0; // Contém um caractere que não é letra nem espaço
        }
    }
    return tem_letra; // Retorna 1 se tiver pelo menos uma letra
}

// Função para ler uma nota válida (número decimal positivo)
float ler_nota(const char *mensagem) {
    float nota;
    int retorno;
    
    while (1) {
        printf("%s", mensagem);
        printf("--------------------------\n");
        retorno = scanf("%f", &nota);

        // Limpa o buffer do teclado
        while (getchar() != '\n');

        if (retorno == 1 && nota >= 0.0 && nota <= 10.0) {
            return nota;
        } else {
            printf("\nInsira uma nota valida (entre 0 e 10)\n\n");
        }
    }
}

// ==============================================================================
// FUNÇÕES DO SISTEMA
// ==============================================================================

// Função: cadastrar_aluno
// Descrição: Lê e valida o nome e as três notas do aluno, inserindo-os nos vetores.
// Parâmetros:
//   - alunos: Matriz de caracteres para os nomes [MAX_ALUNOS][TAM_NOME]
//   - av1, av2, av3: Vetores de float para as notas
//   - quantidade: Ponteiro para o total de alunos cadastrados
void cadastrar_aluno(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int *quantidade) {
    if (*quantidade >= MAX_ALUNOS) {
        printf("\n=================================================\n");
        printf("Limite maximo de alunos (%d) atingido!\n", MAX_ALUNOS);
        printf("=================================================\n\n");
        return;
    }

    char nome[TAM_NOME];

    // Validação do nome
    while (1) {
        printf("=========================\n");
        printf("Insira o nome do aluno: \n");
        printf("=========================\n");
        
        if (fgets(nome, sizeof(nome), stdin) != NULL) {
            // Remove a quebra de linha (\n) do final do texto, se existir
            nome[strcspn(nome, "\n")] = '\0';

            if (validar_nome(nome)) {
                break;
            }
        }

        printf("======================\n");
        printf("Insira um nome valido\n");
        printf("======================\n");
    }

    // Leitura e validação das 3 notas
    float nota1 = ler_nota("\nInsira a nota da av1: \n");
    float nota2 = ler_nota("\nInsira a nota da av2: \n");
    float nota3 = ler_nota("\nInsira a nota da av3: \n");

    // Armazena os dados nos vetores paralelos na posição atual
    int pos = *quantidade;
    strcpy(alunos[pos], nome);
    av1[pos] = nota1;
    av2[pos] = nota2;
    av3[pos] = nota3;

    // Incrementa o contador de alunos
    (*quantidade)++;

    printf("\nUsuario %s criado com sucesso!\n\n", nome);
}

/*
 * Função: exibir_listagem
 * Descrição: Percorre as listas paralelas e exibe todos os alunos cadastrados 
 *            com suas respectivas três notas (AV1, AV2, AV3) formatadas.
 * Parâmetros:
 *   - alunos: Matriz com os nomes
 *   - av1, av2, av3: Vetores com as notas
 *   - quantidade: Total de alunos cadastrados
 */
void exibir_listagem(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int quantidade) {
    // VALIDAÇÃO: Verifica se existem alunos cadastrados antes de iterar
    if (quantidade == 0) {
        printf("\nNenhum aluno cadastrado. Utilize a opcao 1 primeiro.\n\n");
        return;
    }

    // Cabeçalho da listagem
    printf("\n--- Listagem geral de alunos ---\n");

    // Laço for para percorrer os vetores paralelos sincronizados pelo índice
    // O limite do laço é estritamente a variável 'quantidade'
    for (int i = 0; i < quantidade; i++) {
        // Formatação do número sequencial (i + 1) e notas com 1 casa decimal (%.1f)
        printf("%d - %s | AV1: %.1f | AV2: %.1f | AV3: %.1f\n", 
               i + 1, alunos[i], av1[i], av2[i], av3[i]);
    }

    // Exibe o total de alunos cadastrados ao final do laço
    printf("Total de alunos cadastrados: %d\n\n", quantidade);
}

// ==============================================================================
// MENU PRINCIPAL
// ==============================================================================
int main() {
    // Vetores paralelos para armazenamento dos dados
    char alunos[MAX_ALUNOS][TAM_NOME];
    float av1[MAX_ALUNOS];
    float av2[MAX_ALUNOS];
    float av3[MAX_ALUNOS];
    int quantidade = 0; // Quantidade atual de alunos cadastrados

    int opcao;
    int encerrar = 0;

    printf("\n==============================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de notas\n");
    printf("==============================================\n\n");

    while (!encerrar) {
        printf("1 - Cadastrar alunos e notas\n");
        printf("2 - Exibir listagem geral de alunos e notas\n");
        printf("0 - Finalizar programa\n");
        printf("\n====================\n");
        printf("Selecione uma opcao: \n");
        printf("====================\n\n");

        if (scanf("%d", &opcao) != 1) {
            printf("=================================================\n");
            printf("Erro de leitura: Digite um numero inteiro valido\n");
            printf("=================================================\n\n");
            
            // Limpa o buffer de entrada caso o usuário digite texto
            while (getchar() != '\n');
            continue;
        }

        // Limpa a quebra de linha pendente após o scanf
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                cadastrar_aluno(alunos, av1, av2, av3, &quantidade);
                break;
            case 2:
                exibir_listagem(alunos, av1, av2, av3, quantidade);
                break;
            case 0:
                printf("\n=========================\n");
                printf("Finalizando o programa...\n");
                printf("=========================\n");
                encerrar = 1;
                break;
            default:
                printf("==============\n");
                printf("Opcao invalida\n");
                printf("==============\n\n");
                break;
        }
    }

    return 0;
}