// Questão 2 - Busca em uma Árvore Binária de Busca
// Fonte: Adaptado de LeetCode #700 (Search in a Binary Search Tree)
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esq = nullptr;
    No* dir = nullptr;
};

No* inserir(No* no, int valor) {
    if (no == nullptr) {
        No* novo = new No;
        novo->valor = valor;
        return novo;
    }
    if (valor < no->valor) no->esq = inserir(no->esq, valor);
    else                   no->dir = inserir(no->dir, valor);
    return no;
}

// Busca: igual à inserção, mas em vez de criar o nó, responde true/false.
bool buscar(No* no, int valor) {
    if (no == nullptr) return false;
    if (valor == no->valor) return true;
    if (valor < no->valor) return buscar(no->esq, valor);
    return buscar(no->dir, valor);
}

int main() {
    int n;
    cin >> n;
    No* raiz = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        raiz = inserir(raiz, x);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (buscar(raiz, x)) cout << "SIM" << endl;
        else                 cout << "NAO" << endl;
    }
    return 0;
}
