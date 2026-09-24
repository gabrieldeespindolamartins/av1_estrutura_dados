# Sistema de Gerenciamento de Notas — C e Python
 
Sistema de gerenciamento de notas acadêmicas com interface textual dirigida por menu, implementado de forma equivalente em **C** e em **Python**. Os nomes dos alunos e as respectivas notas são mantidos em **vetores paralelos** (C) e **listas paralelas** (Python), com correspondência posicional direta entre os índices.
 
Projeto desenvolvido para a avaliação **A1 — Avaliação Prática em Equipe** da disciplina de Estruturas de Dados.
 
- **Instituição:** FMP — Faculdade Municipal de Palhoça
- **Curso:** Análise e Desenvolvimento de Sistemas
- **Professor:** Sérgio Murilo Schütz
- **Semestre:** 2026/2
---
 
## Funcionalidades
 
O sistema opera em laço contínuo, exibindo o seguinte menu:
 
| Opção | Descrição | Abordagem |
|---|---|---|
| 1 | Cadastrar alunos e notas (vetores paralelos) | Iterativa |
| 2 | Exibir listagem geral de alunos e notas | Iterativa |
| 3 | Calcular e exibir a média geral da turma | Iterativa |
| 4 | Identificar a maior e a menor nota registrada | Iterativa |
| 5 | Contar e listar discentes aprovados (nota >= 7.0) | Iterativa |
| 6 | Emitir estatísticas via funções recursivas | Recursiva |
| 7 | Funcionalidades extras (submenu) | Mista |
| 0 | Encerrar aplicação | — |
 
### Submenu de funcionalidades extras
 
- Busca sequencial de aluno pelo nome
- Estatísticas complementares (alunos acima da média e percentual de aprovação)
- Listagem invertida dos cadastros, implementada de forma recursiva
### Validações
 
- O nome aceita apenas letras e espaços, e não pode ser vazio.
- As notas aceitam apenas valores numéricos entre `0.0` e `10.0`.
- Entradas inválidas no menu e no submenu são tratadas sem interromper a execução.
- Operações sobre um cadastro vazio são bloqueadas, evitando divisão por zero.
---
 
## Estrutura do repositório
 
```
av1_estrutura_dados/
├── README.md     # Este arquivo
├── main.c        # Implementação em linguagem C
└── main.py       # Implementação em Python
```
 
### Branches
 
| Branch | Finalidade |
|---|---|
| `main` | Versão integrada e final do projeto |
| `dev_c` | Desenvolvimento da versão em C |
| `dev_py` | Desenvolvimento da versão em Python |
 
Os commits seguem o padrão `n° da etapa - descrição rápida do que foi executado`, por exemplo: `3 - calcular e exibir média geral da turma`.
 
---
 
## Como executar
 
### Versão em C
 
Requer um compilador C (GCC recomendado).
 
```bash
gcc -Wall -Wextra main.c -o main
./main
```
 
No Windows, com PowerShell:
 
```powershell
gcc -Wall -Wextra main.c -o main.exe
.\main.exe
```
 
### Versão em Python
 
Requer Python 3.10 ou superior, por causa da estrutura `match`.
 
```bash
python main.py
```
 
---
 
## Arquitetura
 
O sistema é dividido em funções modulares, cada uma com responsabilidade única e parâmetros explícitos. As rotinas que precisam devolver mais de um valor usam **passagem por referência** em C (ponteiros) e **retorno múltiplo** em Python.
 
### Funções recursivas
 
Duas funções recursivas puras compõem a opção 6 do menu:
 
- `somar_medias_recursivo` — acumula a soma das médias individuais.
- `contar_aprovados_recursivo` — conta os alunos com média maior ou igual a 7.0.
Ambas recebem o tamanho `n` do vetor, processam a posição `n-1` e chamam a si mesmas com `n - 1`, até o caso base `n == 0`. Como `n` decresce a cada invocação e parte de no máximo `MAX_ALUNOS` (100), o caso base é sempre alcançado, sem risco de estouro de pilha. As funções não contêm laços, não realizam entrada ou saída de dados e não alteram os vetores recebidos.
 
O submenu conta ainda com a rotina recursiva auxiliar `exibir_invertido`.
 
---
 
## Testes
 
O sistema foi validado por teste de mesa com 5 registros acadêmicos, confrontando os resultados do programa com os cálculos apurados manualmente. As duas versões compilam e executam sem erros e produzem resultados idênticos para a mesma amostra.
 
Também foram testados os tratamentos de entrada inválida (nomes com dígitos, notas fora do intervalo permitido e opções inexistentes) e a execução do sistema sem registros cadastrados.
 
---
 
## Equipe
 
| Integrante | Papel | Etapas desenvolvidas |
|---|---|---|
| Gustavo Silva de Sordi | Desenvolvedor de módulos | 4 e 5 |
| Gabriel Calegari Rodrigues | Desenvolvedor de módulos | 2, 6 e 7 |
| Gabriel de Espíndola Martins | Coordenador técnico | 3, 8, 9 e 10 |
| Isabella Trento Lohn | Testes e documentação | 1 e 8 |
 
A divisão do trabalho foi organizada **por módulo, e não por linguagem**: cada integrante implementou as suas etapas simultaneamente em C e em Python, garantindo a equivalência algorítmica entre as versões.
 
---
 
## Uso acadêmico
 
Este repositório contém material produzido para avaliação acadêmica. A reprodução de trechos de código entre equipes distintas caracteriza anulação da avaliação, conforme a política de originalidade da disciplina.
