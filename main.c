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
// n1, n2, n3: Notas AV1, AV2 e AV3 do aluno.
// Retorna: a média do aluno (float).
float calcular_media_aluno(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0f;
}

// Função: calcular_media_turma
// Percorre os vetores de notas de forma iterativa para calcular a média geral da turma.
// av1, av2, av3: Vetores com as notas.
// Retorna: a média geral da turma (float).
float calcular_media_turma(float av1[], float av2[], float av3[], int total) {
    float soma_medias = 0.0f;

    for (int i = 0; i < total; i++) {
        float media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i]);
        soma_medias += media_aluno;
    }

    float media_turma = soma_medias / total;
    return media_turma;
}

// Função: identificar_extremos
// Identifica a maior e a menor nota, junto com o índice do aluno de cada uma.
// av1, av2, av3: Vetores com as notas.
// Retorna via ponteiros: maior, menor, indice_maior, indice_menor.
void identificar_extremos(float av1[], float av2[], float av3[], int total, float *maior, float *menor, int *indice_maior, int *indice_menor) {
    *maior = av1[0];
    *menor = av1[0];
    *indice_maior = 0;
    *indice_menor = 0;

    for (int i = 0; i < total; i++) {
        if (av1[i] > *maior) { *maior = av1[i]; *indice_maior = i; }
        if (av1[i] < *menor) { *menor = av1[i]; *indice_menor = i; }

        if (av2[i] > *maior) { *maior = av2[i]; *indice_maior = i; }
        if (av2[i] < *menor) { *menor = av2[i]; *indice_menor = i; }

        if (av3[i] > *maior) { *maior = av3[i]; *indice_maior = i; }
        if (av3[i] < *menor) { *menor = av3[i]; *indice_menor = i; }
    }
}

// Função: listar_aprovados
// Exibe os alunos com média >= NOTA_APROVACAO e conta quantos foram aprovados.
// alunos: Matriz com os nomes.
// av1, av2, av3: Vetores com as notas.
// Retorna: quantidade de alunos aprovados (int).
int listar_aprovados(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int total) {
    printf("\n--- Alunos aprovados ---\n");

    int contador_aprovados = 0;

    for (int i = 0; i < total; i++) {
        float media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i]);

        if (media_aluno >= NOTA_APROVACAO) {
            printf("%s - Média: %.1f\n", alunos[i], media_aluno);
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
// Caso base: Se n == 0, retorna 0.
// Passo redutor: Média do aluno (n-1) + chamada recursiva para (n-1).
float somar_medias_recursivo(float av1[], float av2[], float av3[], int n) {
    if (n == 0) {
        return 0.0f;
    } else {
        return calcular_media_aluno(av1[n-1], av2[n-1], av3[n-1]) + somar_medias_recursivo(av1, av2, av3, n - 1);
    }
}

// Função: contar_aprovados_recursivo
// Caso base: Se n == 0, retorna 0.
// Passo redutor: Verifica se o aluno (n-1) foi aprovado e soma à chamada recursiva para (n-1).
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
// ETAPA 7 – FUNCIONALIDADES EXTRAS E SUBMENU
// ==============================================================================

// Função: buscar_aluno
// Realiza uma busca sequencial pelo nome do aluno no vetor de alunos.
// alunos: Matriz com os nomes dos alunos.
// quantidade: Quantidade atual de alunos cadastrados.
// nome_buscado: Nome que se deseja procurar.
// Retorna: O índice do aluno se encontrado, ou -1 caso contrário.
int buscar_aluno(char alunos[][TAM_NOME], int quantidade, const char *nome_buscado) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(alunos[i], nome_buscado) == 0) {
            return i; // Retorna o índice imediatamente ao encontrar
        }
    }
    return -1; // Retorna -1 se não for encontrado
}

// Função: exibir_invertido
// Exibe a listagem de alunos e suas notas na ordem inversa de cadastro.
// alunos, av1, av2, av3: Vetores contendo dados e notas dos alunos.
// n: Tamanho atual/restante da lista a ser impressa.
// Caso base: Se n == 0, apenas retorna (condição de parada).
// Passo redutor: Exibe o aluno da posição n - 1 e realiza a chamada recursiva para n - 1.
void exibir_invertido(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int n) {
    // CASO BASE: Condição de parada
    if (n == 0) {
        return;
    }

    // PASSO REDUTOR: Exibe o aluno da posição n-1
    printf("%d - %s | AV1: %.1f | AV2: %.1f | AV3: %.1f\n", n, alunos[n - 1], av1[n - 1], av2[n - 1], av3[n - 1]);

    // Chamada recursiva para o elemento anterior
    exibir_invertido(alunos, av1, av2, av3, n - 1);
}

// Função: contar_acima_da_media
// Conta quantos alunos possuem média individual superior à média da turma.
// av1, av2, av3: Vetores de notas dos alunos.
// quantidade: Quantidade total de alunos.
// media_turma: Média geral calculada para a turma.
// Retorna: Quantidade de alunos acima da média.
int contar_acima_da_media(float av1[], float av2[], float av3[], int quantidade, float media_turma) {
    int contador = 0;
    for (int i = 0; i < quantidade; i++) {
        float media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i]);
        if (media_aluno > media_turma) {
            contador++;
        }
    }
    return contador;
}

// Função: exibir_submenu_extras
// Gerencia e exibe o submenu de funcionalidades extras.
// alunos: Matriz com os nomes dos alunos.
// av1: Vetor com as notas da Avaliação 1.
// av2: Vetor com as notas da Avaliação 2.
// av3: Vetor com as notas da Avaliação 3.
// quantidade: Total de alunos cadastrados (passado por valor).
void exibir_submenu_extras(char alunos[][TAM_NOME], float av1[], float av2[], float av3[], int quantidade) {
    int voltar = 0;
    int opcao;

    while (!voltar) {
        printf("1 - Buscar aluno pelo nome\n");
        printf("2 - Exibir listagem invertida (recursiva)\n");
        printf("3 - Estatisticas complementares\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\n====================\n");
        printf("Selecione uma opcao: \n");
        printf("====================\n\n");

        if (scanf("%d", &opcao) != 1) {
            printf("=================================================\n");
            printf("Erro de leitura: Digite um numero inteiro valido\n");
            printf("=================================================\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        // Limpa a quebra de linha pendente após o scanf
        while (getchar() != '\n');

        // VALIDAÇÃO: Verifica se existem alunos antes de acessar as opções 1, 2 e 3
        if ((opcao >= 1 && opcao <= 3) && quantidade == 0) {
            printf("Nenhum aluno cadastrado. Utilize a opcao 1 do menu principal primeiro.\n\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                char nome_buscado[TAM_NOME];
                printf("Insira o nome do aluno:\n");
                if (fgets(nome_buscado, sizeof(nome_buscado), stdin) != NULL) {
                    nome_buscado[strcspn(nome_buscado, "\n")] = '\0';
                }

                int indice = buscar_aluno(alunos, quantidade, nome_buscado);
                if (indice != -1) {
                    float media = calcular_media_aluno(av1[indice], av2[indice], av3[indice]);
                    printf("%s | AV1: %.1f | AV2: %.1f | AV3: %.1f | Média: %.1f\n\n",
                           alunos[indice], av1[indice], av2[indice], av3[indice], media);
                } else {
                    printf("Aluno nao encontrado.\n\n");
                }
                break;
            }

            case 2:
                printf("\n--- Listagem invertida ---\n");
                exibir_invertido(alunos, av1, av2, av3, quantidade);
                printf("\n");
                break;

            case 3: {
                float media_turma = calcular_media_turma(av1, av2, av3, quantidade);
                int total_aprovados = listar_aprovados(alunos, av1, av2, av3, quantidade);
                int acima_media = contar_acima_da_media(av1, av2, av3, quantidade, media_turma);
                float percentual = ((float)total_aprovados / quantidade) * 100.0f;

                printf("\nAlunos acima da media da turma: %d\n", acima_media);
                printf("Percentual de aprovacao: %.2f%%\n\n", percentual);
                break;
            }

            case 0:
                printf("Voltando ao menu principal...\n\n");
                voltar = 1;
                break;

            default:
                printf("==============\n");
                printf("Opcao invalida\n");
                printf("==============\n\n");
                break;
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
        printf("7 - Funcionalidades Extras - Submenu\n");
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
            if (total_alunos == 0) {
                printf("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n\n");
            } else {
                float media_turma = calcular_media_turma(av1, av2, av3, total_alunos);
                printf("\nMédia geral da turma: %.2f\n\n", media_turma);
            }
        }
        // Caso o usuario escolha a opcao 4
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
        // Caso o usuario escolha a opcao 5
        else if (opcao == 5) {
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
        // Caso o usuario escolha a opcao 7 (Submenu de Extras)
        else if (opcao == 7) {
            exibir_submenu_extras(alunos, av1, av2, av3, total_alunos);
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