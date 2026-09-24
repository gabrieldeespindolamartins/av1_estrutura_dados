#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ==============================================================================
// CONSTANTES E VARIÁVEIS GLOBAIS
// ==============================================================================
#define MAX_ALUNOS 100
#define NOTA_APROVACAO 7.0

// Vetores paralelos para armazenar as informações
char alunos[MAX_ALUNOS][100];
float av1[MAX_ALUNOS];
float av2[MAX_ALUNOS];
float av3[MAX_ALUNOS];

// Contador do total de alunos cadastrados
int total_alunos = 0;


// ==============================================================================
// FUNÇÕES AUXILIARES DE VALIDAÇÃO
// ==============================================================================

// Valida se o nome contém apenas letras e espaços, e se não está vazio
int validar_nome(const char *nome) {
    int tem_letra = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isalpha((unsigned char)nome[i])) {
            tem_letra = 1;
        } else if (nome[i] != ' ' && nome[i] != '\n' && nome[i] != '\r') {
            return 0; // Contém números ou símbolos inválidos
        }
    }
    return tem_letra; // Retorna 1 se tiver pelo menos uma letra válida
}


// ==============================================================================
// FUNÇÕES DO SISTEMA
// ==============================================================================

// Função: ler_nota
// Lê uma nota do teclado. Aceita apenas números (float) entre 0 e 10.
// Rejeita texto/string e valores fora do intervalo.
float ler_nota(const char *mensagem) {
    float nota;
    char buffer[100];

    while (1) {
        printf("%s", mensagem);
        printf("--------------------------\n");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr;
            nota = strtof(buffer, &endptr);

            // Verifica se a conversão foi válida e se a nota está no intervalo [0.0, 10.0]
            if (endptr != buffer && (*endptr == '\n' || *endptr == '\0')) {
                if (nota >= 0.0f && nota <= 10.0f) {
                    return nota;
                }
            }
        }
        printf("\nInsira uma nota valida (entre 0 e 10)\n\n");
    }
}


// Início da função responsável por todo o processo de cadastro de um aluno
void cadastrar_aluno() {
    if (total_alunos >= MAX_ALUNOS) {
        printf("\nLimite maximo de alunos atingido (%d)!\n\n", MAX_ALUNOS);
        return;
    }

    char nome[100];

    while (1) {
        printf("=========================\n");
        printf("Insira o nome do aluno: \n");
        printf("=========================\n");

        if (fgets(nome, sizeof(nome), stdin) != NULL) {
            // Remove a quebra de linha tratada pelo fgets
            nome[strcspn(nome, "\r\n")] = '\0';

            if (validar_nome(nome)) {
                break;
            }
        }

        printf("======================\n");
        printf("Insira um nome valido\n");
        printf("======================\n");
    }

    // Pede as tres notas e guarda apenas numeros entre 0 e 10
    float nota_av1 = ler_nota("\nInsira a nota da av1: \n");
    float nota_av2 = ler_nota("\nInsira a nota da av2: \n");
    float nota_av3 = ler_nota("\nInsira a nota da av3: \n");

    // Guarda as informações nos vetores globais
    strcpy(alunos[total_alunos], nome);
    av1[total_alunos] = nota_av1;
    av2[total_alunos] = nota_av2;
    av3[total_alunos] = nota_av3;
    total_alunos++;

    // Mensagem de confirmação mostrando o nome do aluno recém-cadastrado
    printf("\nUsuario %s criado com sucesso!\n\n", nome);
}


// Função: exibir_listagem
// Lista com os nomes dos alunos e suas respectivas notas.
void exibir_listagem(char alunos_list[][100], float av1_list[], float av2_list[], float av3_list[], int quantidade) {
    // VALIDAÇÃO: Verifica se existem alunos cadastrados antes de tentar iterar
    if (quantidade == 0) {
        printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
        return;
    }

    // Cabeçalho da listagem
    printf("\n--- Listagem geral de alunos ---\n");

    // Laço for para percorrer os vetores paralelos sincronizados pelo índice
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s | AV1: %.1f | AV2: %.1f | AV3: %.1f\n", i + 1, alunos_list[i], av1_list[i], av2_list[i], av3_list[i]);
    }

    // Exibe o total de alunos cadastrados ao final do laço
    printf("Total de alunos cadastrados: %d\n\n", quantidade);
}


// Função: calcular_media_aluno
// Calcula a média aritmética das três notas de um aluno.
float calcular_media_aluno(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0f;
}


// Função: calcular_media_turma
// Percorre os vetores de notas de forma iterativa (laço for) para calcular a
// média de cada aluno e, a partir delas, a média geral da turma.
float calcular_media_turma(float av1_list[], float av2_list[], float av3_list[], int quantidade) {
    float soma_medias = 0;

    for (int i = 0; i < quantidade; i++) {
        float media_aluno = calcular_media_aluno(av1_list[i], av2_list[i], av3_list[i]);
        soma_medias += media_aluno;
    }

    float media_turma = soma_medias / quantidade;
    return media_turma;
}


// Função: identificar_extremos
// Percorre de forma iterativa (laço for) todas as notas (AV1, AV2 e AV3) e
// identifica a maior e a menor nota, junto com o índice do aluno de cada uma.
void identificar_extremos(float av1_list[], float av2_list[], float av3_list[], int quantidade, float *maior, float *menor, int *indice_maior, int *indice_menor) {
    *maior = av1_list[0];
    *menor = av1_list[0];
    *indice_maior = 0;
    *indice_menor = 0;

    for (int i = 0; i < quantidade; i++) {
        // AV1
        if (av1_list[i] > *maior) {
            *maior = av1_list[i];
            *indice_maior = i;
        }
        if (av1_list[i] < *menor) {
            *menor = av1_list[i];
            *indice_menor = i;
        }

        // AV2
        if (av2_list[i] > *maior) {
            *maior = av2_list[i];
            *indice_maior = i;
        }
        if (av2_list[i] < *menor) {
            *menor = av2_list[i];
            *indice_menor = i;
        }

        // AV3
        if (av3_list[i] > *maior) {
            *maior = av3_list[i];
            *indice_maior = i;
        }
        if (av3_list[i] < *menor) {
            *menor = av3_list[i];
            *indice_menor = i;
        }
    }
}


// Função: listar_aprovados
// Percorre as listas de forma iterativa, exibe os alunos com média maior ou
// igual a NOTA_APROVACAO e conta quantos foram aprovados.
int listar_aprovados(char alunos_list[][100], float av1_list[], float av2_list[], float av3_list[], int quantidade) {
    printf("\n--- Alunos aprovados ---\n");

    int contador_aprovados = 0;

    for (int i = 0; i < quantidade; i++) {
        float media_aluno = calcular_media_aluno(av1_list[i], av2_list[i], av3_list[i]);

        if (media_aluno >= NOTA_APROVACAO) {
            printf("%s - Média: %.1f\n", alunos_list[i], media_aluno);
            contador_aprovados++;
        }
    }

    if (contador_aprovados == 0) {
        printf("Nenhum aluno aprovado.\n");
    }

    return contador_aprovados;
}


// ==============================================================================
// FUNÇÕES RECURSIVAS (ETAPA 6)
// ==============================================================================

// Função: somar_medias_recursivo
// Caso base: Se o tamanho (n) for igual a 0, retorna 0 (condição de parada).
// Passo redutor: Retorna o cálculo da média do aluno atual (n-1) somado à chamada
// da própria função para o tamanho reduzido (n-1).
// Retorna: A soma de todas as médias (float). Função pura, sem loops ou prints.
float somar_medias_recursivo(float av1_list[], float av2_list[], float av3_list[], int n) {
    if (n == 0) {
        return 0.0f;
    } else {
        return calcular_media_aluno(av1_list[n - 1], av2_list[n - 1], av3_list[n - 1]) + somar_medias_recursivo(av1_list, av2_list, av3_list, n - 1);
    }
}


// Função: contar_aprovados_recursivo
// Caso base: Se o tamanho (n) for igual a 0, retorna 0 (condição de parada).
// Passo redutor: Calcula a média do aluno atual (n-1). Se aprovado, retorna 1 + a
// chamada da própria função para (n-1). Caso contrário, retorna 0 + chamada para (n-1).
// Retorna: A quantidade de alunos aprovados (int). Função pura, sem loops ou prints.
int contar_aprovados_recursivo(float av1_list[], float av2_list[], float av3_list[], int n) {
    if (n == 0) {
        return 0;
    } else {
        float media_aluno = calcular_media_aluno(av1_list[n - 1], av2_list[n - 1], av3_list[n - 1]);
        if (media_aluno >= NOTA_APROVACAO) {
            return 1 + contar_aprovados_recursivo(av1_list, av2_list, av3_list, n - 1);
        } else {
            return 0 + contar_aprovados_recursivo(av1_list, av2_list, av3_list, n - 1);
        }
    }
}


// ==============================================================================
// MENU PRINCIPAL
// ==============================================================================
int main() {
    int encerrar = 0;
    int opcao;
    char buffer[100];

    // Cabeçalho inicial do programa
    printf("\n==============================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de notas\n");
    printf("==============================================\n\n");

    while (!encerrar) {
        // Exibe as opções do programa
        printf("1 - Cadastrar alunos e notas\n");
        printf("2 - Exibir listagem geral de alunos e notas\n");
        printf("3 - Calcular e exibir a média geral da turma\n");
        printf("4 - Identificar a maior e a menor nota registrada\n");
        printf("5 - Contar e listar discentes aprovados\n");
        printf("6 - Emitir estatísticas via funções recursivas\n");
        printf("0 - Finalizar programa\n");
        printf("\n====================\n");
        printf("Selecione uma opcao: \n");
        printf("====================\n\n");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        char *endptr;
        opcao = (int)strtol(buffer, &endptr, 10);

        // Trata erro de digitação de opções não numéricas
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("=================================================\n");
            printf("Erro de leitura: Digite um numero inteiro valido\n");
            printf("=================================================\n");
            continue;
        }

        // Opção 1: Cadastrar alunos e notas
        if (opcao == 1) {
            cadastrar_aluno();
        }
        // Opção 2: Listagem geral
        else if (opcao == 2) {
            exibir_listagem(alunos, av1, av2, av3, total_alunos);
        }
        // Opção 3: Média geral da turma
        else if (opcao == 3) {
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                float media_turma = calcular_media_turma(av1, av2, av3, total_alunos);
                printf("\nMédia geral da turma: %.2f\n\n", media_turma);
            }
        }
        // Opção 4: Extremos (Maior e Menor nota)
        else if (opcao == 4) {
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                float maior, menor;
                int indice_maior, indice_menor;
                identificar_extremos(av1, av2, av3, total_alunos, &maior, &menor, &indice_maior, &indice_menor);
                printf("\nMaior nota registrada: %.1f - aluno %s\n", maior, alunos[indice_maior]);
                printf("Menor nota registrada: %.1f - aluno %s\n\n", menor, alunos[indice_menor]);
            }
        }
        // Opção 5: Listar e contar aprovados
        else if (opcao == 5) {
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                int aprovados = listar_aprovados(alunos, av1, av2, av3, total_alunos);
                printf("Total de aprovados: %d de %d alunos\n\n", aprovados, total_alunos);
            }
        }
        // Opção 6: Estatísticas via funções recursivas
        else if (opcao == 6) {
            int quantidade = total_alunos;

            // VALIDAÇÃO: evita divisão por zero
            if (quantidade == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                float soma_medias = somar_medias_recursivo(av1, av2, av3, quantidade);
                int total_aprovados = contar_aprovados_recursivo(av1, av2, av3, quantidade);

                float media_turma = soma_medias / quantidade;
                float taxa_aprovacao = ((float)total_aprovados / quantidade) * 100.0f;

                printf("\n--- Estatísticas (cálculo recursivo) ---\n");
                printf("Soma das médias: %.2f\n", soma_medias);
                printf("Média geral da turma: %.2f\n", media_turma);
                printf("Total de aprovados: %d de %d\n", total_aprovados, quantidade);
                printf("Taxa de aprovação: %.2f%%\n\n", taxa_aprovacao);
            }
        }
        // Opção 0: Encerrar programa
        else if (opcao == 0) {
            printf("\n=========================\n");
            printf("Finalizando o programa...\n");
            printf("=========================\n");
            encerrar = 1;
            break;
        }
        // Opção inválida
        else {
            printf("==============\n");
            printf("Opcao invalida\n");
            printf("==============\n");
        }
    }

    return 0;
}