// Questão 1 - Árvore Binária de Busca: inserção e percursos
// Fonte: Adaptado de beecrowd #1195 (Árvore Binária de Busca)
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esq = nullptr;
    No* dir = nullptr;
};

// Inserção: menor vai para a esquerda, maior para a direita.
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

void preOrdem(No* no) {
    if (no == nullptr) return;
    cout << " " << no->valor;
    preOrdem(no->esq);
    preOrdem(no->dir);
}

void emOrdem(No* no) {
    if (no == nullptr) return;
    emOrdem(no->esq);
    cout << " " << no->valor;
    emOrdem(no->dir);
}

void posOrdem(No* no) {
    if (no == nullptr) return;
    posOrdem(no->esq);
    posOrdem(no->dir);
    cout << " " << no->valor;
}

int main() {
    int casos;
    cin >> casos;
    for (int c = 1; c <= casos; c++) {
        int n;
        cin >> n;
        No* raiz = nullptr;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            raiz = inserir(raiz, x);
        }
        cout << "Case " << c << ":" << endl;
        cout << "Pre.:"; preOrdem(raiz); cout << endl;
        cout << "In..:"; emOrdem(raiz);  cout << endl;
        cout << "Post:"; posOrdem(raiz); cout << endl;
        cout << endl;
    }
    return 0;
}
