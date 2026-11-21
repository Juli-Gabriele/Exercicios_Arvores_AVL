
using namespace std;

struct No {
    int valor;
    int altura;   // preenchido pela função calcular()
    int fb;       // fator de balanceamento, também preenchido por calcular()
    No* esq;
    No* dir;
    explicit No(int v) : valor(v), altura(0), fb(0), esq(nullptr), dir(nullptr) {}
};

// Monta a árvore a partir da lista em nível (mesmo formato do LeetCode).
No* montarArvore(const vector<string>& simbolos) {
    if (simbolos.empty() || simbolos[0] == "null") return nullptr;

    No* raiz = new No(stoi(simbolos[0]));
    queue<No*> fila;
    fila.push(raiz);
    size_t i = 1;

    while (!fila.empty() && i < simbolos.size()) {
        No* atual = fila.front();
        fila.pop();

        if (i < simbolos.size() && simbolos[i] != "null") {
            atual->esq = new No(stoi(simbolos[i]));
            fila.push(atual->esq);
        }
        i++;
        if (i < simbolos.size() && simbolos[i] != "null") {
            atual->dir = new No(stoi(simbolos[i]));
            fila.push(atual->dir);
        }
        i++;
    }
    return raiz;
}

// PÓS-ORDEM: calcula altura e FB de cada nó e devolve a altura da subárvore.
// O parâmetro "balanceada" vira false se algum nó tiver |FB| > 1.
int calcular(No* no, bool& balanceada) {
    if (no == nullptr) return -1;                 // altura do nulo

    int he = calcular(no->esq, balanceada);       // 1) esquerda
    int hd = calcular(no->dir, balanceada);       // 2) direita

    no->fb = he - hd;                             // 3) Fator de Balanceamento
    no->altura = 1 + (he > hd ? he : hd);

    if (no->fb > 1 || no->fb < -1)                // FB = +2 ou -2: viola a AVL
        balanceada = false;

    return no->altura;
}

// Imprime o FB de cada nó em nível (mesma ordem da entrada), usando uma fila
void imprimirFBs(No* raiz) {
    if (raiz == nullptr) { cout << endl; return; }
    queue<No*> fila;
    fila.push(raiz);
    bool primeiro = true;
    while (!fila.empty()) {
        No* atual = fila.front();
        fila.pop();
        if (!primeiro) cout << " ";
        cout << atual->fb;
        primeiro = false;
        if (atual->esq) fila.push(atual->esq);
        if (atual->dir) fila.push(atual->dir);
    }
    cout << endl;
}

void destruir(No* no) {
    if (no == nullptr) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

int main() {
    int n;
    while (cin >> n) {
        vector<string> simbolos(n);
        for (int i = 0; i < n; i++) cin >> simbolos[i];

        No* raiz = montarArvore(simbolos);
        bool balanceada = true;
        calcular(raiz, balanceada);

        imprimirFBs(raiz);
        cout << (balanceada ? "true" : "false") << endl;
        destruir(raiz);
    }
    return 0;
}
