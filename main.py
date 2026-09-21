# ==============================================================================
# CABEÇALHO DO PROGRAMA
# ==============================================================================
print("\n==============================================")
print("Bem-vindo ao sistema de gerenciamento de notas")
print("==============================================\n")

# Cria listas vazias para guardar as informações que serão adicionadas
alunos = []
av1 = []
av2 = []
av3 = []


# ==============================================================================
# FUNÇÕES DO SISTEMA
# ==============================================================================

# Início da função responsável por todo o processo de cadastro de um aluno
def cadastrar_aluno():
    while True:
        print("=========================")
        print("Insira o nome do aluno: ")
        print("=========================")
        nome = input("")

        # Faz aceitar apenas letras no nome
        nome_sem_espaco = nome.strip().replace(" ", "")

        if nome_sem_espaco != "" and nome_sem_espaco.isalpha():
            break
        else:
            print("======================")
            print("Insira um nome valido")
            print("======================")

    # Pede as tres notas e guarda apenas numeros
    while True:
        print("\nInsira a nota da av1: \n")
        print("--------------------------")
        try:
            nota_av1 = float(input(""))
            break
        except ValueError:
            print("\nInsira uma nota valida\n")

    while True:
        print("\nInsira a nota da av2: \n")
        print("--------------------------")
        try:
            nota_av2 = float(input(""))
            break
        except ValueError:
            print("\nInsira uma nota valida\n")

    while True:
        print("\nInsira a nota da av3: \n")
        print("--------------------------")
        try:
            nota_av3 = float(input(""))
            break
        except ValueError:
            print("\nInsira uma nota valida\n")

    # Guarda as informações nas listas globais
    alunos.append(nome)
    av1.append(nota_av1)
    av2.append(nota_av2)
    av3.append(nota_av3)

    # Mensagem de confirmação mostrando o nome do aluno recém-cadastrado
    print(f"\nUsuario {nome} criado com sucesso!\n")


# Função: exibir_listagem
# Lista com os nomes dos alunos.
# av1: Lista com as notas da Avaliação 1.
# av2: Lista com as notas da Avaliação 2.
# av3: Lista com as notas da Avaliação 3.
def exibir_listagem(alunos, av1, av2, av3):
    # VALIDAÇÃO: Verifica se existem alunos cadastrados antes de tentar iterar
    if len(alunos) == 0:
        print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
        return

    # Cabeçalho da listagem
    print("\n--- Listagem geral de alunos ---")

    # Laço for para percorrer os vetores/listas paralelas sincronizadas pelo índice
    for i in range(len(alunos)):
        print(f"{i + 1} - {alunos[i]} | AV1: {av1[i]:.1f} | AV2: {av2[i]:.1f} | AV3: {av3[i]:.1f}")

    # Exibe o total de alunos cadastrados ao final do laço
    print(f"Total de alunos cadastrados: {len(alunos)}\n")


# Função: calcular_media_turma
# Percorre os vetores de notas de forma iterativa (laço for) para calcular a
# média de cada aluno e, a partir delas, a média geral da turma.
# av1: Lista com as notas da Avaliação 1.
# av2: Lista com as notas da Avaliação 2.
# av3: Lista com as notas da Avaliação 3.
# Retorna: a média geral da turma (float). Não faz print, apenas retorna o
# valor, para que a função possa ser reaproveitada em outras partes do sistema.
def calcular_media_turma(av1, av2, av3):
    # Variável acumuladora que soma a média de cada aluno a cada volta do laço
    soma_medias = 0

    # Laço for que percorre os vetores do índice 0 até o total de alunos cadastrados
    for i in range(len(av1)):
        # Calcula a média do aluno somando as três notas e dividindo por 3
        media_aluno = (av1[i] + av2[i] + av3[i]) / 3
        soma_medias += media_aluno

    # Calcula a média geral da turma dividindo a soma das médias pela quantidade de alunos
    media_turma = soma_medias / len(av1)
    return media_turma


# ==============================================================================
# MENU PRINCIPAL
# ==============================================================================
encerrar = False

# Início do loop principal do menu, que fica repetindo até o usuário escolher encerrar o programa.
while not encerrar:
    # Exibe as opções do programa
    print("1 - Cadastrar alunos e notas")
    print("2 - Exibir listagem geral de alunos e notas")
    print("3 - Calcular e exibir a média geral da turma")
    print("0 - Finalizar programa")
    print("\n====================")
    # Solicita a opcao do usuario
    print("Selecione uma opcao: ")
    print("====================\n")
    
    try:
        opcao = int(input(""))
    except ValueError:
        print("=================================================")
        print("Erro de leitura: Digite um numero inteiro valido")
        print("=================================================")
        continue

    # Caso o usuario escolha a opcao 1, o programa levara a cadastrar aluno
    if opcao == 1:
        cadastrar_aluno()

    # Caso o usuario escolha a opcao 2, o programa chama a função de listagem
    elif opcao == 2:
        exibir_listagem(alunos, av1, av2, av3)

    # Caso o usuario escolha a opcao 3, o programa calcula e exibe a média geral da turma
    elif opcao == 3:
        # VALIDAÇÃO: Verifica se existem alunos cadastrados antes de calcular, evitando divisão por zero
        if len(alunos) == 0:
            print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
        else:
            media_turma = calcular_media_turma(av1, av2, av3)
            print(f"\nMédia geral da turma: {media_turma:.2f}\n")

    # Caso o usuario escolha a opcao 0, o programa finaliza
    elif opcao == 0:
        print("\n=========================")
        print("Finalizando o programa...")
        print("=========================")
        encerrar = True
        break

    # Caso o usuario escolha uma opcao invalida, o programa exibe uma mensagem de erro
    else:
        print("==============")
        print("Opcao invalida")
        print("==============")