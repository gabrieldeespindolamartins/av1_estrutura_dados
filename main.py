#Exibe o titulo do programa
print("\n==============================================")
print("Bem-vindo ao sistema de gerenciamento de notas")
print("==============================================\n")

#Cria listas vazias para guardar as informacoes que serao adicionadas
av1 = []
av2 = []
av3 = []
alunos = []

#Início da função responsável por todo o processo de cadastro de um aluno
def cadastrar_aluno():
    while True:
        print("=========================")
        print("Insira o nome do aluno: ")
        print("=========================")
        nome = input("")

        #faz aceitar apenas letras no nome
        nome_sem_espaco = nome.strip().replace(" ", "")

        if nome_sem_espaco != "" and nome_sem_espaco.isalpha():
            break
        else:
            print("======================")
            print("insira um nome valido")
            print("======================")

    #pede as tres notas e guarda apenas numeros
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
        print("\nInsira a nota da av3")
        print("--------------------------")
        try:
            nota_av3 = float(input(""))
            break
        except ValueError:
            print("\nInsira uma nota valida\n")

    #guarda as informacoes na lista global la de cima 
    alunos.append(nome)
    av1.append(nota_av1)
    av2.append(nota_av2)
    av3.append(nota_av3)

    #Mensagem de confirmação mostrando o nome do aluno recém-cadastrado
    print(f"\nUsuario {nome} criado com sucesso!\n")

encerrar = False
#Início do loop principal do menu, que fica repetindo até o usuário escolher encerrar o programa.
while not encerrar:
    # Exibe as opções do programa
    print("1 - Cadastrar alunos e notas")
    print("0 - Finalizar programa")
    print("\n====================")
    # Solicita a opcao do usuario
    print("Selecione uma opcao: ")
    print("====================\n")
    try:
        opcao = int(input(""))
        # Verifica se a opcao do usuario é um numero inteiro valido
    except ValueError:
        print("=================================================")
        print("Erro de leitura: Digite um numero inteiro valido")
        print("=================================================")
        continue
    #Caso o usuario escolha a opcao 1, o programa levara a cadastrar aluno
    if opcao == 1:
        cadastrar_aluno()
    #Caso o usuario escolha a opcao 0, o programa finaliza
    elif opcao == 0:
        
        print("\n=========================")
        print("Finalizando o programa...")
        print("=========================")
        encerrar = True
        break
    #Caso o usuario escolha uma opcao invalida, o programa exibe uma mensagem de erro
    else:
        print("==============")
        print("Opcao invalida")
        print("==============")
