# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: *PEDRO GUEDES DANTAS TEIXEIRA DE SOUZA*
- Email: *pedroguedescs@gmail.com*
- Turma: *EDB1 - DIM0119*

# Indique quais itens da avaliação foram realizados

- [x] Valida corretamente arquivo de entrada (20 pontos)

- [ ] Simulador apenas sugere direções randômicas para cobra (10 pontos)
OU
- [x] Simulador direciona a cobra corretamente para a comida (50 pontos)

- [x] Apresentar e manipula corretamente os estados da simulação (30 pontos)

- [x] **Extra**: simulação gera o menor caminho (por meio do BFS)
- [x] **Extra**: algoritmo BFS (Breadth-First Search)
- [x] **Extra**: algoritmo DFS (Depth-First Search)
- [x] **Extra**: algoritmo GBFS (Greedy Best-First Search)
- [x] **Extra**: algoritmo A* (A star)
- [x] **Extra**: visualização das posições exploradas pela IA para resolver o labirinto (use o commando "--exploration-view"). Essa funcionalidade foi implementada com o intuito de distinguir melhor o comportamento de cada algoritmo

--------
# Passo a passo para compilar o projeto

## 1. Acesse a pasta do código-fonte
cd source

## 2. Compile todos os arquivos necessários
g++ algorithmUtils.cpp ArgumentParser.cpp PlayerAI.cpp Snake.cpp SnakeGame.cpp utils.cpp Maze.cpp main.cpp -o SnakeGameExe

## 3. Execute o jogo
./SnakeGameExe


&copy; DIMAp/UFRN 2021.
