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


# ==============================================================================
# MENU PRINCIPAL
# ==============================================================================
encerrar = False

# Início do loop principal do menu, que fica repetindo até o usuário escolher encerrar o programa.
while not encerrar:
    # Exibe as opções do programa
    print("1 - Cadastrar alunos e notas")
    print("2 - Exibir listagem geral de alunos e notas")
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