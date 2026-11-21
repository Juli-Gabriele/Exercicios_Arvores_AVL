
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esq;
    No* dir;
    explicit No(int v) : valor(v), esq(nullptr), dir(nullptr) {}
};

// Inserção recursiva da BST: menor vai para a esquerda, maior para a direita
No* inserir(No* no, int valor) {
    if (no == nullptr) return new No(valor);
    if (valor < no->valor)      no->esq = inserir(no->esq, valor);
    else if (valor > no->valor) no->dir = inserir(no->dir, valor);
    return no;
}

// Percurso em ordem completo (usado só para imprimir a linha 1 da saída)
void emOrdem(No* no, bool& primeiro) {
    if (no == nullptr) return;
    emOrdem(no->esq, primeiro);
    if (!primeiro) cout << " ";
    cout << no->valor;
    primeiro = false;
    emOrdem(no->dir, primeiro);
}

// Percurso em ordem com CONTADOR: para assim que encontra o K-ésimo.
// contador e resposta são passados por referência (compartilhados entre chamadas).
void kesimo(No* no, int k, int& contador, int& resposta) {
    if (no == nullptr || contador >= k) return;   // fim ou já encontrado

    kesimo(no->esq, k, contador, resposta);       // 1) esquerda (menores)

    contador++;                                   // 2) visita o nó atual
    if (contador == k) {
        resposta = no->valor;
        return;
    }

    kesimo(no->dir, k, contador, resposta);       // 3) direita (maiores)
}

void destruir(No* no) {
    if (no == nullptr) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        No* raiz = nullptr;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            raiz = inserir(raiz, x);
        }

        bool primeiro = true;
        emOrdem(raiz, primeiro);
        cout << endl;

        int contador = 0, resposta = 0;
        kesimo(raiz, k, contador, resposta);
        cout << resposta << endl;

        destruir(raiz);
    }
    return 0;
}
