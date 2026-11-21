# Seminário 3 — Árvores Binárias de Busca (BST) e Árvores AVL

**Disciplina:** Estrutura de Dados II  
**Integrantes:** Julia, Carlos e Gustavo  
**Videoaula:** _link do YouTube (não listado)_

Implementação própria, em C++17, de uma **Árvore Binária de Busca** e de uma **Árvore AVL**,
com um programa de demonstração e as resoluções de 3 exercícios do LeetCode.
O código foi escrito para ser **simples de ler e de explicar**: funções recursivas curtas,
nomes em português e comentários em cada passo.

## Estrutura de pastas

```
Seminario3_BST_AVL/
├── CMakeLists.txt              # projeto CMake (abre direto no CLion)
├── README.md
├── docs/
│   ├── Slides_Seminario3_BST_AVL.pdf
│   └── Lista_Exercicios_BST_AVL.pdf
└── src/
    ├── BST.h                   # declaração da classe BST
    ├── AVL.h                   # declaração da classe AVL
    ├── BST.cpp                 # implementação da BST
    ├── AVL.cpp                 # implementação da AVL
    ├── main.cpp                        # menu com as demonstrações da aula
    ├── Exer01_PercursosBST.cpp         # Questão 1 (beecrowd 1195)
    ├── Exer02_BuscaBST.cpp             # Questão 2 (LeetCode 700)
    └── Exer03_ArvoreAVL.cpp            # Questão 3 (LeetCode 110)
```

## Como rodar

**No CLion:** `File > Open` e escolha a pasta do projeto. O CLion lê o `CMakeLists.txt` sozinho.
No seletor de configurações (canto superior direito) escolha o executável:

| Executável             | O que faz                                   |
|------------------------|---------------------------------------------|
| `Seminario3`                   | menu com as demonstrações de BST e AVL |
| `Exer01_PercursosBST`          | Questão 1                              |
| `Exer02_BuscaBST`              | Questão 2                              |
| `Exer03_ArvoreAVL`             | Questão 3                              |

As questões funcionam como em um juiz on-line: leem da **entrada padrão** e imprimem a saída
exata. No CLion, rode e cole o "Exemplo de Entrada" da lista no console.

**Pelo terminal:**

```bash
cmake -S . -B build
cmake --build build
./build/Seminario3
```

## O que foi implementado

### BST (`src/BST.h`, `src/BST.cpp`)

| Operação                         | Função                         | Complexidade (médio / pior) |
|----------------------------------|--------------------------------|-----------------------------|
| Inserção                         | `inserir`                      | O(log N) / O(N)             |
| Busca                            | `buscar`                       | O(log N) / O(N)             |
| Mínimo / Máximo                  | `minimo`, `maximo`             | O(log N) / O(N)             |
| Sucessor / Antecessor            | `sucessor`, `antecessor`       | O(log N) / O(N)             |
| Remoção por cópia                | `removerPorCopia`              | O(log N) / O(N)             |
| Remoção por fusão                | `removerPorFusao`              | O(log N) / O(N)             |
| Percursos em profundidade        | `emOrdem`, `preOrdem`, `posOrdem` | O(N)                     |
| Percurso em largura              | `emNivel` (usa `std::queue`)   | O(N)                        |
| Altura, tamanho, impressão       | `altura`, `tamanho`, `imprimir`| O(N)                        |

### AVL (`src/AVL.h`, `src/AVL.cpp`)

- Cada nó guarda a sua **altura** (folha = 0, nulo = −1).
- **Fator de Balanceamento:** `FB = altura(esq) − altura(dir)`.
- `rotacaoDireita` e `rotacaoEsquerda` (rotações simples, O(1)).
- `balancear` trata os 4 casos:

| Caso | FB do nó | FB do filho | Correção                              |
|------|----------|-------------|---------------------------------------|
| EE   | +2       | ≥ 0         | rotação simples à direita             |
| DD   | −2       | ≤ 0         | rotação simples à esquerda            |
| ED   | +2       | < 0         | esquerda no filho + direita no nó     |
| DE   | −2       | > 0         | direita no filho + esquerda no nó     |

- `inserir` e `remover` funcionam como na BST e chamam `balancear` na volta da recursão → **O(log N)** sempre.
- Com `setMostrarRotacoes(true)` a árvore imprime cada rotação feita, por exemplo:
  `[DE] no 20 (FB=-2, filho FB=+1): rotacao dupla (direita em 40, esquerda em 20)`.
- `imprimir` desenha a árvore "deitada" no console com o FB de cada nó: `30[-1]`.

### Menu de demonstrações (`src/main.cpp`)

1. **Demo BST** – inserção, os 4 percursos, busca, sucessor/antecessor, remoção por cópia e por fusão.
2. **Demo AVL** – os 4 casos (EE, DD, ED, DE) e a sequência 10, 20, 30, 40, 50, 25.
3. **BST degenerada × AVL** – 1000 inserções em ordem: altura 999 na BST contra 9 na AVL.
4. **BST interativa** e 5. **AVL interativa** – para testar valores ao vivo na aula.

## Exercícios

| # | Arquivo (`src/`) | Problema / Abordagem | Complexidade |
|---|------------------|----------------------|--------------|
| 1 | `Exer01_PercursosBST.cpp` | Inserção na BST e percursos pré, em e pós-ordem ([beecrowd 1195](https://judge.beecrowd.com/pt/problems/view/1195)) | O(N·h) |
| 2 | `Exer02_BuscaBST.cpp` | Busca na BST: SIM/NAO para cada consulta ([LeetCode 700](https://leetcode.com/problems/search-in-a-binary-search-tree/)) | O(h) por busca |
| 3 | `Exer03_ArvoreAVL.cpp` | Altura e verificação do Fator de Balanceamento ([LeetCode 110](https://leetcode.com/problems/balanced-binary-tree/)) | O(N²) pior caso |

Exemplo (Questão 3):

```
Entrada:        Saída:
3               2
10 20 30        NAO
```

Enunciados completos e exemplos de entrada/saída em `docs/Lista_Exercicios_BST_AVL.pdf`; as resoluções comentadas são os arquivos `Exer0*.cpp` em `src/`.
