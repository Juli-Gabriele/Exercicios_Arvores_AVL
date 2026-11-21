
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct No {
    int valor;
    No* esq;
    No* dir;
    explicit No(int v) : valor(v), esq(nullptr), dir(nullptr) {}
};

// Monta a árvore a partir da lista em nível (mesmo formato do LeetCode).
// Usa uma FILA: cada nó retirado recebe os próximos dois símbolos como filhos.
No* montarArvore(const vector<string>& simbolos) {
    if (simbolos.empty() || simbolos[0] == "null") return nullptr;

    No* raiz = new No(stoi(simbolos[0]));
    queue<No*> fila;
    fila.push(raiz);
    size_t i = 1;

    while (!fila.empty() && i < simbolos.size()) {
        No* atual = fila.front();
        fila.pop();

        if (i < simbolos.size() && simbolos[i] != "null") {   // filho esquerdo
            atual->esq = new No(stoi(simbolos[i]));
            fila.push(atual->esq);
        }
        i++;
        if (i < simbolos.size() && simbolos[i] != "null") {   // filho direito
            atual->dir = new No(stoi(simbolos[i]));
            fila.push(atual->dir);
        }
        i++;
    }
    return raiz;
}

// Verifica se todos os valores da subárvore estão no intervalo (minimo, maximo).
// Os limites são long long para que INT_MIN e INT_MAX possam aparecer na árvore.
bool valida(No* no, long long minimo, long long maximo) {
    if (no == nullptr) return true;                   // subárvore vazia é válida

    if (no->valor <= minimo || no->valor >= maximo)   // saiu do intervalo
        return false;

    return valida(no->esq, minimo, no->valor)         // esquerda: tudo < valor
        && valida(no->dir, no->valor, maximo);        // direita:  tudo > valor
}

// Libera a memória em pós-ordem (filhos antes do pai)
void destruir(No* no) {
    if (no == nullptr) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

int main() {
    int n;
    while (cin >> n) {                        // aceita vários casos de teste
        vector<string> simbolos(n);
        for (int i = 0; i < n; i++) cin >> simbolos[i];

        No* raiz = montarArvore(simbolos);
        cout << (valida(raiz, LLONG_MIN, LLONG_MAX) ? "true" : "false") << endl;
        destruir(raiz);
    }
    return 0;
}
