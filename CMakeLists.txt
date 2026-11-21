cmake_minimum_required(VERSION 3.16)
project(Seminario3_BST_AVL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Programa principal com as demonstrações de BST e AVL
add_executable(Seminario3
        src/main.cpp
        src/BST.cpp
        src/AVL.cpp)

# Cada questão da lista é um executável separado (escolha no seletor do CLion).
# Elas leem da entrada padrão: digite a entrada no console ou cole os exemplos.
add_executable(Exer01_PercursosBST   src/Exer01_PercursosBST.cpp)
add_executable(Exer02_BuscaBST       src/Exer02_BuscaBST.cpp)
add_executable(Exer03_ArvoreAVL      src/Exer03_ArvoreAVL.cpp)
