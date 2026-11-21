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

// Altura = 1 + a maior altura entre os dois filhos
int altura(No* no) {
    if (no == nullptr) return -1;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    if (he > hd) return he + 1;
    return hd + 1;
}

// Verifica o FB de TODOS os nós
bool ehAVL(No* no) {
    if (no == nullptr) return true;

    int fb = altura(no->esq) - altura(no->dir);
    if (fb < -1 || fb > 1) return false;

    return ehAVL(no->esq) && ehAVL(no->dir);
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
    cout << altura(raiz) << endl;
    if (ehAVL(raiz)) cout << "SIM" << endl;
    else             cout << "NAO" << endl;
    return 0;
}
