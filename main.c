#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ==============================================================================
// CONSTANTES E DEFINIÇÕES DO SISTEMA
// ==============================================================================
#define MAX_ALUNOS 100
#define TAM_NOME 100
#define NOTA_APROVACAO 7.0

// ==============================================================================
// VARIÁVEIS GLOBAIS (Equivalentes às listas em Python)
// ==============================================================================
char alunos[MAX_ALUNOS][TAM_NOME];
float av1[MAX_ALUNOS];
float av2[MAX_ALUNOS];
float av3[MAX_ALUNOS];
int total_alunos = 0; // Controla a quantidade atual de alunos cadastrados


// ==============================================================================
// FUNÇÕES DO SISTEMA
// ==============================================================================

// Função auxiliar: valida se a string contém apenas letras e espaços
int eh_nome_valido(const char *nome) {
    int letras = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isalpha((unsigned char)nome[i])) {
            letras++;
        } else if (!isspace((unsigned char)nome[i])) {
            return 0; // Contém caracteres inválidos (números/símbolos)
        }
    }
    return letras > 0; // Válido se possuir pelo menos uma letra
}




// Função: ler_nota
// Lê uma nota do teclado. Aceita apenas números (float) entre 0 e 10.
// Rejeita texto/string e valores fora do intervalo.
float ler_nota(const char *mensagem) {    
    char buffer[100];
    float nota;

    while (1) {
        printf("%s", mensagem);
        printf("--------------------------\n");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char extra;
            // Valida se foi digitado um float válido e nada além dele
            if (sscanf(buffer, "%f %c", &nota, &extra) == 1) {
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

    char nome[TAM_NOME];

    while (1) {
        printf("=========================\n");
        printf("Insira o nome do aluno: \n");
        printf("=========================\n");

        if (fgets(nome, sizeof(nome), stdin) != NULL) {
            // Remove o caractere de nova linha (\n) do final da string
            nome[strcspn(nome, "\n")] = '\0';

            if (eh_nome_valido(nome)) {
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
// Lista com os nomes dos alunos.
// av1: Vetor com as notas da Avaliação 1.
// av2: Vetor com as notas da Avaliação 2.
// av3: Vetor com as notas da Avaliação 3.
void exibir_listagem(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int total) {
    // VALIDAÇÃO: Verifica se existem alunos cadastrados antes de tentar iterar
    if (total == 0) {
        printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
        return;
    }

    // Cabeçalho da listagem
    printf("\n--- Listagem geral de alunos ---\n");

    // Laço for para percorrer os vetores paralelos sincronizados pelo índice
    for (int i = 0; i < total; i++) {
        printf("%d - %s | AV1: %.1f | AV2: %.1f | AV3: %.1f\n", i + 1, alunos[i], av1[i], av2[i], av3[i]);
    }

    // Exibe o total de alunos cadastrados ao final do laço
    printf("Total de alunos cadastrados: %d\n\n", total);
}


// Função: calcular_media_aluno
// Calcula a média aritmética das três notas de um aluno.
// Pode ser reaproveitada nas etapas 3 e 6.
// n1, n2, n3: Notas AV1, AV2 e AV3 do aluno.
// Retorna: a média do aluno (float).
float calcular_media_aluno(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0f;
}


// Função: calcular_media_turma
// Percorre os vetores de notas de forma iterativa (laço for) para calcular a
// média de cada aluno e, a partir delas, a média geral da turma.
// av1: Vetor com as notas da Avaliação 1.
// av2: Vetor com as notas da Avaliação 2.
// av3: Vetor com as notas da Avaliação 3.
// Retorna: a média geral da turma (float). Não faz print, apenas retorna o
// valor, para que a função possa ser reaproveitada em outras partes do sistema.
float calcular_media_turma(float av1[], float av2[], float av3[], int total) {
    // Variável acumuladora que soma a média de cada aluno a cada volta do laço
    float soma_medias = 0.0f;

    // Laço for que percorre os vetores do índice 0 até o total de alunos cadastrados
    for (int i = 0; i < total; i++) {
        // Reaproveita calcular_media_aluno para evitar repetir a mesma conta
        float media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i]);
        soma_medias += media_aluno;
    }

    // Calcula a média geral da turma dividindo a soma das médias pela quantidade de alunos
    float media_turma = soma_medias / total;
    return media_turma;
}


// Função: identificar_extremos
// Percorre de forma iterativa (laço for) todas as notas (AV1, AV2 e AV3) e
// identifica a maior e a menor nota, junto com o índice do aluno de cada uma.
// Em caso de empate, mantém o primeiro aluno encontrado (> e < estritos).
// av1, av2, av3: Vetores com as notas.
// Retorna via ponteiros: maior, menor, indice_maior, indice_menor.
void identificar_extremos(float av1[], float av2[], float av3[], int total, float *maior, float *menor, int *indice_maior, int *indice_menor) {
    // Inicializa com a primeira nota cadastrada (não usar 0 ou 10)
    *maior = av1[0];
    *menor = av1[0];
    *indice_maior = 0;
    *indice_menor = 0;

    // Laço for: percorre do índice 0 até o total de alunos cadastrados
    for (int i = 0; i < total; i++) {
        // AV1
        if (av1[i] > *maior) {
            *maior = av1[i];
            *indice_maior = i;
        }
        if (av1[i] < *menor) {
            *menor = av1[i];
            *indice_menor = i;
        }

        // AV2
        if (av2[i] > *maior) {
            *maior = av2[i];
            *indice_maior = i;
        }
        if (av2[i] < *menor) {
            *menor = av2[i];
            *indice_menor = i;
        }

        // AV3
        if (av3[i] > *maior) {
            *maior = av3[i];
            *indice_maior = i;
        }
        if (av3[i] < *menor) {
            *menor = av3[i];
            *indice_menor = i;
        }
    }
}


// Função: listar_aprovados
// Percorre as listas de forma iterativa, exibe os alunos com média maior ou
// igual a NOTA_APROVACAO e conta quantos foram aprovados.
// alunos: Matriz com os nomes.
// av1, av2, av3: Vetores com as notas.
// Retorna: quantidade de alunos aprovados (int).
int listar_aprovados(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int total) {
    printf("\n--- Alunos aprovados ---\n");

    int contador_aprovados = 0;

    // Laço for: percorre do índice 0 até o total de alunos cadastrados
    for (int i = 0; i < total; i++) {
        float media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i]);

        // >= para que média exatamente 7.0 também aprove
        if (media_aluno >= NOTA_APROVACAO) {
            printf("%s - Média: %.1f\n", alunos[i], media_aluno);
            contador_aprovados++;
        }
    }

    // Se ninguém atingiu a média, informa no lugar da listagem vazia
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
float somar_medias_recursivo(float av1[], float av2[], float av3[], int n) {
    if (n == 0) {
        return 0.0f;
    } else {
        return calcular_media_aluno(av1[n-1], av2[n-1], av3[n-1]) + somar_medias_recursivo(av1, av2, av3, n - 1);
    }
}


// Função: contar_aprovados_recursivo
// Caso base: Se o tamanho (n) for igual a 0, retorna 0 (condição de parada).
// Passo redutor: Calcula a média do aluno atual (n-1). Se aprovado, retorna 1 + a
// chamada da própria função para (n-1). Caso contrário, retorna 0 + chamada para (n-1).
// Retorna: A quantidade de alunos aprovados (int). Função pura, sem loops ou prints.
int contar_aprovados_recursivo(float av1[], float av2[], float av3[], int n) {
    if (n == 0) {
        return 0;
    } else {
        float media_aluno = calcular_media_aluno(av1[n-1], av2[n-1], av3[n-1]);
        if (media_aluno >= NOTA_APROVACAO) {
            return 1 + contar_aprovados_recursivo(av1, av2, av3, n - 1);
        } else {
            return 0 + contar_aprovados_recursivo(av1, av2, av3, n - 1);
        }
    }
}


// ==============================================================================
// PROGRAMA PRINCIPAL
// ==============================================================================
int main() {
    int encerrar = 0;
    char buffer_opcao[100];
    int opcao;

    // Cabeçalho do programa
    printf("\n==============================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de notas\n");
    printf("==============================================\n\n");

    // Início do loop principal do menu
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

        if (fgets(buffer_opcao, sizeof(buffer_opcao), stdin) == NULL) {
            continue;
        }

        char extra;
        // Validação da opção do menu para rejeitar entradas inválidas
        if (sscanf(buffer_opcao, "%d %c", &opcao, &extra) != 1) {
            printf("=================================================\n");
            printf("Erro de leitura: Digite um numero inteiro valido\n");
            printf("=================================================\n");
            continue;
        }

        // Caso o usuario escolha a opcao 1
        if (opcao == 1) {
            cadastrar_aluno();
        }
        // Caso o usuario escolha a opcao 2
        else if (opcao == 2) {
            exibir_listagem(alunos, av1, av2, av3, total_alunos);
        }
        // Caso o usuario escolha a opcao 3
        else if (opcao == 3) {
            // VALIDAÇÃO: Verifica se existem alunos cadastrados antes de calcular, evitando divisão por zero
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                float media_turma = calcular_media_turma(av1, av2, av3, total_alunos);
                printf("\nMédia geral da turma: %.2f\n\n", media_turma);
            }
        }
        // Caso o usuario escolha a opcao 4
        else if (opcao == 4) {
            // VALIDAÇÃO: evita acessar av1[0] com o vetor vazio
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
        // Caso o usuario escolha a opcao 5
        else if (opcao == 5) {
            // VALIDAÇÃO: Verifica se existem alunos cadastrados antes de listar
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                int total_aprovados = listar_aprovados(alunos, av1, av2, av3, total_alunos);
                printf("Total de aprovados: %d de %d alunos\n\n", total_aprovados, total_alunos);
            }
        }
        // Caso o usuario escolha a opcao 6
        else if (opcao == 6) {
            int quantidade = total_alunos;

            // VALIDAÇÃO: Evita divisão por zero e estouro de pilha
            if (quantidade == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                // Chamadas das funções recursivas passando a quantidade como valor inicial de n
                float soma_medias = somar_medias_recursivo(av1, av2, av3, quantidade);
                int total_aprovados = contar_aprovados_recursivo(av1, av2, av3, quantidade);

                // Cálculos de turma com conversão explícita para float
                float media_turma = soma_medias / quantidade;
                float taxa_aprovacao = ((float)total_aprovados / quantidade) * 100.0f;

                // Exibição dos dados
                printf("\n--- Estatísticas (cálculo recursivo) ---\n");
                printf("Soma das médias: %.2f\n", soma_medias);
                printf("Média geral da turma: %.2f\n", media_turma);
                printf("Total de aprovados: %d de %d\n", total_aprovados, quantidade);
                printf("Taxa de aprovação: %.2f%%\n\n", taxa_aprovacao);
            }
        }
        // Caso o usuario escolha a opcao 0
        else if (opcao == 0) {
            printf("\n=========================\n");
            printf("Finalizando o programa...\n");
            printf("=========================\n");
            encerrar = 1;
            break;
        }
        // Caso o usuario escolha uma opcao invalida
        else {
            printf("==============\n");
            printf("Opcao invalida\n");
            printf("==============\n");
        }
    }

    return 0;
}