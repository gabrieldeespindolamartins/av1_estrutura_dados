# ==============================================================================
# CONSTANTES E DEFINIÇÕES DO SISTEMA
# ==============================================================================
MAX_ALUNOS = 100
NOTA_APROVACAO = 7.0

# ==============================================================================
# VARIÁVEIS GLOBAIS (Listas paralelas para armazenar dados dos alunos)
# ==============================================================================
alunos = []
av1 = []
av2 = []
av3 = []


# ==============================================================================
# FUNÇÕES DO SISTEMA
# ==============================================================================

def eh_nome_valido(nome: str) -> bool:
    """
    Valida se a string contém apenas letras e espaços.
    Retorna True se válida e possuir pelo menos uma letra.
    """
    letras = 0
    for char in nome:
        if char.isalpha():
            letras += 1
        elif not char.isspace():
            return False  # Contém caracteres inválidos (números/símbolos)
    return letras > 0


def ler_nota(mensagem: str) -> float:
    """
    Lê uma nota do teclado. Aceita apenas float entre 0.0 e 10.0.
    Rejeita texto/string e valores fora do intervalo.
    """
    while True:
        print(mensagem, end="")
        print("--------------------------")
        entrada = input().strip()

        try:
            nota = float(entrada)
            if 0.0 <= nota <= 10.0:
                return nota
        except ValueError:
            pass

        print("\nInsira uma nota valida (entre 0 e 10)\n")


def cadastrar_aluno():
    """Realiza todo o processo de cadastro de um aluno e suas 3 notas."""
    if len(alunos) >= MAX_ALUNOS:
        print(f"\nLimite maximo de alunos atingido ({MAX_ALUNOS})!\n")
        return

    while True:
        print("=========================")
        print("Insira o nome do aluno: ")
        print("=========================")
        nome = input().strip()

        if eh_nome_valido(nome):
            break

        print("======================")
        print("Insira um nome valido")
        print("======================")

    # Solicita as três notas com validação
    nota_av1 = ler_nota("\nInsira a nota da av1: \n")
    nota_av2 = ler_nota("\nInsira a nota da av2: \n")
    nota_av3 = ler_nota("\nInsira a nota da av3: \n")

    # Guarda as informações nas listas paralelas
    alunos.append(nome)
    av1.append(nota_av1)
    av2.append(nota_av2)
    av3.append(nota_av3)

    print(f"\nUsuario {nome} criado com sucesso!\n")


def exibir_listagem(alunos_list, av1_list, av2_list, av3_list):
    """Exibe a listagem geral de alunos cadastrados e suas notas."""
    total = len(alunos_list)
    if total == 0:
        print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
        return

    print("\n--- Listagem geral de alunos ---")
    for i in range(total):
        print(f"{i + 1} - {alunos_list[i]} | AV1: {av1_list[i]:.1f} | AV2: {av2_list[i]:.1f} | AV3: {av3_list[i]:.1f}")

    print(f"Total de alunos cadastrados: {total}\n")


def calcular_media_aluno(n1: float, n2: float, n3: float) -> float:
    """Calcula a média aritmética das três notas de um aluno."""
    return (n1 + n2 + n3) / 3.0


def calcular_media_turma(av1_list, av2_list, av3_list) -> float:
    """Calcula e retorna a média geral da turma."""
    total = len(av1_list)
    soma_medias = sum(calcular_media_aluno(av1_list[i], av2_list[i], av3_list[i]) for i in range(total))
    return soma_medias / total


def identificar_extremos(av1_list, av2_list, av3_list):
    """
    Identifica a maior e a menor nota entre todas as avaliações e os alunos correspondentes.
    Retorna tupla: (maior, menor, indice_maior, indice_menor)
    """
    maior = av1_list[0]
    menor = av1_list[0]
    indice_maior = 0
    indice_menor = 0

    total = len(av1_list)
    for i in range(total):
        notas = [av1_list[i], av2_list[i], av3_list[i]]
        for nota in notas:
            if nota > maior:
                maior = nota
                indice_maior = i
            if nota < menor:
                menor = nota
                indice_menor = i

    return maior, menor, indice_maior, indice_menor


def listar_aprovados(alunos_list, av1_list, av2_list, av3_list) -> int:
    """Exibe os alunos aprovados (média >= 7.0) e retorna a quantidade total de aprovados."""
    print("\n--- Alunos aprovados ---")
    contador_aprovados = 0
    total = len(alunos_list)

    for i in range(total):
        media_aluno = calcular_media_aluno(av1_list[i], av2_list[i], av3_list[i])
        if media_aluno >= NOTA_APROVACAO:
            print(f"{alunos_list[i]} - Média: {media_aluno:.1f}")
            contador_aprovados += 1

    if contador_aprovados == 0:
        print("Nenhum aluno aprovado.")

    return contador_aprovados


# ==============================================================================
# FUNÇÕES RECURSIVAS (ETAPA 6)
# ==============================================================================

def somar_medias_recursivo(av1_list, av2_list, av3_list, n: int) -> float:
    """
    Caso Base: Se n == 0, retorna 0.0 (condição de parada).
    Passo Redutor: Média do aluno (n-1) + chamada recursiva com n-1.
    """
    if n == 0:
        return 0.0
    return calcular_media_aluno(av1_list[n - 1], av2_list[n - 1], av3_list[n - 1]) + somar_medias_recursivo(av1_list, av2_list, av3_list, n - 1)


def contar_aprovados_recursivo(av1_list, av2_list, av3_list, n: int) -> int:
    """
    Caso Base: Se n == 0, retorna 0.
    Passo Redutor: Verifica aprovação do aluno (n-1) + chamada recursiva com n-1.
    """
    if n == 0:
        return 0
    media_aluno = calcular_media_aluno(av1_list[n - 1], av2_list[n - 1], av3_list[n - 1])
    ponto = 1 if media_aluno >= NOTA_APROVACAO else 0
    return ponto + contar_aprovados_recursivo(av1_list, av2_list, av3_list, n - 1)


# ==============================================================================
# ETAPA 7 – FUNCIONALIDADES EXTRAS E SUBMENU
# ==============================================================================

def buscar_aluno(alunos_list, nome_buscado: str) -> int:
    """
    Realiza uma busca sequencial pelo nome do aluno na lista.
    Parâmetros:
      - alunos_list: Lista com os nomes dos alunos.
      - nome_buscado: Nome a ser pesquisado.
    Retorna: O índice do aluno se encontrado, ou -1 caso contrário.
    """
    for i in range(len(alunos_list)):
        if alunos_list[i] == nome_buscado:
            return i
    return -1


def exibir_invertido(alunos_list, av1_list, av2_list, av3_list, n: int):
    """
    Exibe a listagem de alunos e suas notas em ordem inversa através de recursão.
    
    Caso Base: Se n == 0, encerra a execução e apenas retorna.
    Passo Redutor: Exibe o aluno da posição n - 1 e faz a chamada recursiva para n - 1.
    """
    # CASO BASE
    if n == 0:
        return

    # PASSO REDUTOR
    print(f"{n} - {alunos_list[n - 1]} | AV1: {av1_list[n - 1]:.1f} | AV2: {av2_list[n - 1]:.1f} | AV3: {av3_list[n - 1]:.1f}")
    
    # Chamada recursiva
    exibir_invertido(alunos_list, av1_list, av2_list, av3_list, n - 1)


def contar_acima_da_media(av1_list, av2_list, av3_list, media_turma: float) -> int:
    """
    Conta e retorna quantos alunos possuem média individual superior à média geral da turma.
    """
    contador = 0
    for i in range(len(av1_list)):
        media_aluno = calcular_media_aluno(av1_list[i], av2_list[i], av3_list[i])
        if media_aluno > media_turma:
            contador += 1
    return contador


def exibir_submenu_extras(alunos_list, av1_list, av2_list, av3_list):
    """
    Gerencia e exibe o submenu de funcionalidades extras do sistema.
    Parâmetros:
      - alunos_list, av1_list, av2_list, av3_list: Listas paralelas contendo dados e notas.
    """
    voltar = False

    while not voltar:
        print("1 - Buscar aluno pelo nome")
        print("2 - Exibir listagem invertida (recursiva)")
        print("3 - Estatisticas complementares")
        print("0 - Voltar ao menu principal")
        print("\n====================")
        print("Selecione uma opcao: ")
        print("====================\n")

        entrada = input().strip()

        try:
            opcao = int(entrada)
        except ValueError:
            print("=================================================")
            print("Erro de leitura: Digite um numero inteiro valido")
            print("=================================================\n")
            continue

        quantidade = len(alunos_list)

        # VALIDAÇÃO: Bloqueia as opções 1, 2 e 3 caso não existam alunos cadastrados
        if 1 <= opcao <= 3 and quantidade == 0:
            print("Nenhum aluno cadastrado. Utilize a opcao 1 do menu principal primeiro.\n")
            continue

        if opcao == 1:
            print("Insira o nome do aluno:")
            nome_buscado = input().strip()
            indice = buscar_aluno(alunos_list, nome_buscado)

            if indice != -1:
                media = calcular_media_aluno(av1_list[indice], av2_list[indice], av3_list[indice])
                print(f"{alunos_list[indice]} | AV1: {av1_list[indice]:.1f} | AV2: {av2_list[indice]:.1f} | AV3: {av3_list[indice]:.1f} | Média: {media:.1f}\n")
            else:
                print("Aluno nao encontrado.\n")

        elif opcao == 2:
            print("\n--- Listagem invertida ---")
            exibir_invertido(alunos_list, av1_list, av2_list, av3_list, quantidade)
            print()

        elif opcao == 3:
            media_turma = calcular_media_turma(av1_list, av2_list, av3_list)
            total_aprovados = listar_aprovados(alunos_list, av1_list, av2_list, av3_list)
            acima_media = contar_acima_da_media(av1_list, av2_list, av3_list, media_turma)
            percentual = (total_aprovados / quantidade) * 100.0

            print(f"\nAlunos acima da media da turma: {acima_media}")
            print(f"Percentual de aprovacao: {percentual:.2f}%\n")

        elif opcao == 0:
            print("Voltando ao menu principal...\n")
            voltar = True

        else:
            print("==============")
            print("Opcao invalida")
            print("==============\n")


# ==============================================================================
# PROGRAMA PRINCIPAL
# ==============================================================================
def main():
    encerrar = False

    print("\n==============================================")
    print("Bem-vindo ao sistema de gerenciamento de notas")
    print("==============================================\n")

    while not encerrar:
        print("1 - Cadastrar alunos e notas")
        print("2 - Exibir listagem geral de alunos e notas")
        print("3 - Calcular e exibir a média geral da turma")
        print("4 - Identificar a maior e a menor nota registrada")
        print("5 - Contar e listar discentes aprovados")
        print("6 - Emitir estatísticas via funções recursivas")
        print("7 - Funcionalidades Extras - Submenu")
        print("0 - Finalizar programa")
        print("\n====================")
        print("Selecione uma opcao: ")
        print("====================\n")

        entrada = input().strip()

        try:
            opcao = int(entrada)
        except ValueError:
            print("=================================================")
            print("Erro de leitura: Digite um numero inteiro valido")
            print("=================================================\n")
            continue

        if opcao == 1:
            cadastrar_aluno()

        elif opcao == 2:
            exibir_listagem(alunos, av1, av2, av3)

        elif opcao == 3:
            if len(alunos) == 0:
                print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
            else:
                media_turma = calcular_media_turma(av1, av2, av3)
                print(f"\nMédia geral da turma: {media_turma:.2f}\n")

        elif opcao == 4:
            if len(alunos) == 0:
                print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
            else:
                maior, menor, idx_maior, idx_menor = identificar_extremos(av1, av2, av3)
                print(f"\nMaior nota registrada: {maior:.1f} - aluno {alunos[idx_maior]}")
                print(f"Menor nota registrada: {menor:.1f} - aluno {alunos[idx_menor]}\n")

        elif opcao == 5:
            if len(alunos) == 0:
                print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
            else:
                total_aprovados = listar_aprovados(alunos, av1, av2, av3)
                print(f"Total de aprovados: {total_aprovados} de {len(alunos)} alunos\n")

        elif opcao == 6:
            quantidade = len(alunos)
            if quantidade == 0:
                print("\nNenhum aluno cadastrado. Utilize a opção 1 primeiro.\n")
            else:
                soma_medias = somar_medias_recursivo(av1, av2, av3, quantidade)
                total_aprovados = contar_aprovados_recursivo(av1, av2, av3, quantidade)

                media_turma = soma_medias / quantidade
                taxa_aprovacao = (total_aprovados / quantidade) * 100.0

                print("\n--- Estatísticas (cálculo recursivo) ---")
                print(f"Soma das médias: {soma_medias:.2f}")
                print(f"Média geral da turma: {media_turma:.2f}")
                print(f"Total de aprovados: {total_aprovados} de {quantidade}")
                print(f"Taxa de aprovação: {taxa_aprovacao:.2f}%\n")

        elif opcao == 7:
            exibir_submenu_extras(alunos, av1, av2, av3)

        elif opcao == 0:
            print("\n=========================")
            print("Finalizando o programa...")
            print("=========================")
            encerrar = True

        else:
            print("==============")
            print("Opcao invalida")
            print("==============\n")


if __name__ == "__main__":
    main()