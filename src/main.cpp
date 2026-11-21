// main.cpp  -  Demonstrações para a videoaula (BST e AVL)
#include <iostream>
#include "BST.h"
#include "AVL.h"

using namespace std;

void linha() { cout << "------------------------------------------------------------" << endl; }

// DEMO 1: BST - inserção, percursos, busca, sucessor/antecessor, remoções
void demoBST() {
    BST arvore;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};

    cout << "\n=== DEMO BST ===\nInserindo: ";
    for (int v : valores) { cout << v << " "; arvore.inserir(v); }
    cout << "\n\nArvore (gire a cabeca 90 graus para a esquerda):\n";
    arvore.imprimir();

    linha();
    cout << "Em ordem  (E-R-D): "; arvore.emOrdem();
    cout << "Pre-ordem (R-E-D): "; arvore.preOrdem();
    cout << "Pos-ordem (E-D-R): "; arvore.posOrdem();
    cout << "Em nivel (largura): "; arvore.emNivel();

    linha();
    cout << "Buscar 45: " << (arvore.buscar(45) ? "encontrado" : "nao encontrado") << endl;
    cout << "Buscar 99: " << (arvore.buscar(99) ? "encontrado" : "nao encontrado") << endl;
    cout << "Minimo: " << arvore.minimo() << "  |  Maximo: " << arvore.maximo() << endl;

    int r;
    if (arvore.sucessor(30, r))   cout << "Sucessor de 30 (tem filho direito): " << r << endl;
    if (arvore.sucessor(45, r))   cout << "Sucessor de 45 (sobe ao ancestral): " << r << endl;
    if (arvore.antecessor(60, r)) cout << "Antecessor de 60: " << r << endl;
    cout << "Altura: " << arvore.altura() << "  |  Nos: " << arvore.tamanho() << endl;

    linha();
    cout << "Remover 20 (folha) por COPIA:\n";
    arvore.removerPorCopia(20);
    arvore.imprimir();

    linha();
    cout << "Remover 30 (dois filhos) por COPIA -> 30 recebe o sucessor 35:\n";
    arvore.removerPorCopia(30);
    arvore.imprimir();

    linha();
    BST outra;
    for (int v : valores) outra.inserir(v);
    cout << "Na arvore original, remover 30 por FUSAO\n"
            "-> maior da esquerda (20) recebe a subarvore direita (40...):\n";
    outra.removerPorFusao(30);
    outra.imprimir();
    cout << "Altura depois da fusao: " << outra.altura()
         << " (a fusao pode aumentar a altura; a copia tende a preservar)\n";
}

// DEMO 2: os 4 casos de desbalanceamento da AVL
void mostrarCaso(const char* titulo, int a, int b, int c) {
    AVL avl;
    avl.setMostrarRotacoes(true);
    cout << "\n" << titulo << "  - inserindo " << a << ", " << b << ", " << c << endl;
    avl.inserir(a);
    avl.inserir(b);
    avl.inserir(c);
    cout << "Resultado:\n";
    avl.imprimir();
}

void demoAVL() {
    cout << "\n=== DEMO AVL: OS 4 CASOS ===   (valor[FB])\n";
    mostrarCaso("Caso EE", 30, 20, 10);
    mostrarCaso("Caso DD", 10, 20, 30);
    mostrarCaso("Caso ED", 30, 10, 20);
    mostrarCaso("Caso DE", 10, 30, 20);

    linha();
    cout << "Sequencia maior: 10 20 30 40 50 25\n";
    AVL avl;
    avl.setMostrarRotacoes(true);
    int valores[] = {10, 20, 30, 40, 50, 25};
    for (int v : valores) {
        cout << "inserir " << v << endl;
        avl.inserir(v);
    }
    avl.imprimir();
    cout << "Em ordem: "; avl.emOrdem();
    cout << "Em nivel: "; avl.emNivel();

    linha();
    cout << "Remover 10, 25 e 20 (a ultima remocao gera rotacao):\n";
    avl.remover(10);
    avl.remover(25);
    avl.remover(20);
    avl.imprimir();
}

// DEMO 3: pior caso da BST (vira lista) x AVL
void demoComparacao() {
    cout << "\n=== BST DEGENERADA x AVL ===\nInserindo 1, 2, 3, ..., 7 em ordem crescente\n";
    BST bst;
    AVL avl;
    for (int i = 1; i <= 7; i++) { bst.inserir(i); avl.inserir(i); }

    cout << "\nBST (virou uma LISTA -> busca O(n)):\n";
    bst.imprimir();
    cout << "Altura BST = " << bst.altura() << endl;

    cout << "\nAVL (continua baixinha -> busca O(log n)):\n";
    avl.imprimir();
    cout << "Altura AVL = " << avl.altura() << endl;

    linha();
    BST bstGrande;
    AVL avlGrande;
    for (int i = 1; i <= 1000; i++) { bstGrande.inserir(i); avlGrande.inserir(i); }
    cout << "Com 1000 valores em ordem: altura BST = " << bstGrande.altura()
         << "  |  altura AVL = " << avlGrande.altura() << endl;
}

// MODO INTERATIVO (para testar valores na hora da aula)
void interativoAVL() {
    AVL avl;
    avl.setMostrarRotacoes(true);
    int op, v;
    do {
        cout << "\n[AVL] 1-Inserir 2-Remover 3-Buscar 4-Percursos 0-Voltar: ";
        if (!(cin >> op)) return;
        if (op == 1) { cout << "Valor: "; cin >> v; avl.inserir(v); avl.imprimir(); }
        else if (op == 2) { cout << "Valor: "; cin >> v; avl.remover(v); avl.imprimir(); }
        else if (op == 3) { cout << "Valor: "; cin >> v;
                            cout << (avl.buscar(v) ? "Encontrado" : "Nao encontrado") << endl; }
        else if (op == 4) {
            cout << "Em ordem: "; avl.emOrdem();
            cout << "Pre:      "; avl.preOrdem();
            cout << "Pos:      "; avl.posOrdem();
            cout << "Nivel:    "; avl.emNivel();
        }
    } while (op != 0);
}

void interativoBST() {
    BST bst;
    int op, v;
    do {
        cout << "\n[BST] 1-Inserir 2-Remover(copia) 3-Remover(fusao) 4-Buscar 5-Percursos 0-Voltar: ";
        if (!(cin >> op)) return;
        if (op == 1) { cout << "Valor: "; cin >> v; bst.inserir(v); bst.imprimir(); }
        else if (op == 2) { cout << "Valor: "; cin >> v; bst.removerPorCopia(v); bst.imprimir(); }
        else if (op == 3) { cout << "Valor: "; cin >> v; bst.removerPorFusao(v); bst.imprimir(); }
        else if (op == 4) { cout << "Valor: "; cin >> v;
                            cout << (bst.buscar(v) ? "Encontrado" : "Nao encontrado") << endl; }
        else if (op == 5) {
            cout << "Em ordem: "; bst.emOrdem();
            cout << "Pre:      "; bst.preOrdem();
            cout << "Pos:      "; bst.posOrdem();
            cout << "Nivel:    "; bst.emNivel();
        }
    } while (op != 0);
}

int main() {
    int opcao;
    do {
        cout << "\n========== SEMINARIO 3 - BST e AVL ==========\n"
             << "1 - Demo BST (insercao, percursos, remocoes)\n"
             << "2 - Demo AVL (4 casos de rotacao)\n"
             << "3 - BST degenerada x AVL\n"
             << "4 - BST interativa\n"
             << "5 - AVL interativa\n"
             << "0 - Sair\n"
             << "Opcao: ";
        if (!(cin >> opcao)) break;

        switch (opcao) {
            case 1: demoBST(); break;
            case 2: demoAVL(); break;
            case 3: demoComparacao(); break;
            case 4: interativoBST(); break;
            case 5: interativoAVL(); break;
        }
    } while (opcao != 0);
    return 0;
}
