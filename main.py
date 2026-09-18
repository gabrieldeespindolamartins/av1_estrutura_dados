#Exibe o titulo do programa
print("\n==============================================")
print("Bem-vindo ao sistema de gerenciamento de notas")
print("==============================================\n")
encerrar = False
while not encerrar:
    # Exibe as opções do programa
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
    #Caso o usuario escolha a opcao 0, o programa finaliza
    if opcao == 0:
        
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
