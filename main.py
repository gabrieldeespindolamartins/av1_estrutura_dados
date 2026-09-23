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

# Nota mínima para aprovação (evita espalhar o valor 7.0 pelo código)
NOTA_APROVACAO = 7.0


# ==============================================================================
# FUNÇÕES DO SISTEMA
# ==============================================================================

# Função: ler_nota
# Lê uma nota do teclado. Aceita apenas números (float) entre 0 e 10.
# Rejeita texto/string e valores fora do intervalo.
def ler_nota(mensagem):
    while True:
        print(mensagem)
        print("--------------------------")
        try:
            nota = float(input(""))
            if 0.0 <= nota <= 10.0:
                return nota
            else:
                print("\nInsira uma nota valida (entre 0 e 10)\n")
        except ValueError:
            print("\nInsira uma nota valida (entre 0 e 10)\n")


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

    # Pede as tres notas e guarda apenas numeros entre 0 e 10
    nota_av1 = ler_nota("\nInsira a nota da av1: \n")
    nota_av2 = ler_nota("\nInsira a nota da av2: \n")
    nota_av3 = ler_nota("\nInsira a nota da av3: \n")

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


# Função: calcular_media_aluno
# Calcula a média aritmética das três notas de um aluno.
# Pode ser reaproveitada nas etapas 3 e 6.
# n1, n2, n3: Notas AV1, AV2 e AV3 do aluno.
# Retorna: a média do aluno (float).
def calcular_media_aluno(n1, n2, n3):
    return (n1 + n2 + n3) / 3


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
        # Reaproveita calcular_media_aluno para evitar repetir a mesma conta
        media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i])
        soma_medias += media_aluno

    # Calcula a média geral da turma dividindo a soma das médias pela quantidade de alunos
    media_turma = soma_medias / len(av1)
    return media_turma


# Função: identificar_extremos
# Percorre de forma iterativa (laço for) todas as notas (AV1, AV2 e AV3) e
# identifica a maior e a menor nota, junto com o índice do aluno de cada uma.
# Em caso de empate, mantém o primeiro aluno encontrado (> e < estritos).
# av1, av2, av3: Listas com as notas.
# Retorna: maior, menor, indice_maior, indice_menor.
def identificar_extremos(av1, av2, av3):
    # Inicializa com a primeira nota cadastrada (não usar 0 ou 10)
    maior = av1[0]
    menor = av1[0]
    indice_maior = 0
    indice_menor = 0

    # Laço for: percorre do índice 0 até o total de alunos cadastrados
    for i in range(len(av1)):
        # AV1
        if av1[i] > maior:
            maior = av1[i]
            indice_maior = i
        if av1[i] < menor:
            menor = av1[i]
            indice_menor = i

        # AV2
        if av2[i] > maior:
            maior = av2[i]
            indice_maior = i
        if av2[i] < menor:
            menor = av2[i]
            indice_menor = i

        # AV3
        if av3[i] > maior:
            maior = av3[i]
            indice_maior = i
        if av3[i] < menor:
            menor = av3[i]
            indice_menor = i

    return maior, menor, indice_maior, indice_menor


# Função: listar_aprovados
# Percorre as listas de forma iterativa, exibe os alunos com média maior ou
# igual a NOTA_APROVACAO e conta quantos foram aprovados.
# alunos: Lista com os nomes.
# av1, av2, av3: Listas com as notas.
# Retorna: quantidade de alunos aprovados (int).
def listar_aprovados(alunos, av1, av2, av3):
    print("\n--- Alunos aprovados ---")

    contador_aprovados = 0

    # Laço for: percorre do índice 0 até o total de alunos cadastrados
    for i in range(len(alunos)):
        media_aluno = calcular_media_aluno(av1[i], av2[i], av3[i])

        # >= para que média exatamente 7.0 também aprove
        if media_aluno >= NOTA_APROVACAO:
            print(f"{alunos[i]} - Média: {media_aluno:.1f}")
            contador_aprovados += 1

    # Se ninguém atingiu a média, informa no lugar da listagem vazia
    if contador_aprovados == 0:
        print("Nenhum aluno aprovado.")

    return contador_aprovados


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
    print("4 - Identificar a maior e a menor nota registrada")
    print("5 - Contar e listar discentes aprovados")
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

    # Caso o usuario escolha a opcao 4, identifica a maior e a menor nota registrada
    elif opcao == 4:
        # VALIDAÇÃO: evita acessar av1[0] com a lista vazia
        if len(alunos) == 0:
            print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
        else:
            maior, menor, indice_maior, indice_menor = identificar_extremos(av1, av2, av3)
            print(f"\nMaior nota registrada: {maior:.1f} - aluno {alunos[indice_maior]}")
            print(f"Menor nota registrada: {menor:.1f} - aluno {alunos[indice_menor]}\n")

    # Caso o usuario escolha a opcao 5, lista e conta os alunos aprovados
    elif opcao == 5:
        # VALIDAÇÃO: Verifica se existem alunos cadastrados antes de listar
        if len(alunos) == 0:
            print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
        else:
            total_aprovados = listar_aprovados(alunos, av1, av2, av3)
            print(f"Total de aprovados: {total_aprovados} de {len(alunos)} alunos\n")

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