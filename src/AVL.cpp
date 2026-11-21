// AVL.cpp  -  Implementação da Árvore AVL
#include "AVL.h"
#include <iostream>
#include <queue>

using namespace std;

AVL::AVL() : raiz(nullptr), mostrarRotacoes(false) {}

AVL::~AVL() { destruir(raiz); }

void AVL::destruir(NoAVL* no) {
    if (no == nullptr) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

bool AVL::vazia() const { return raiz == nullptr; }

// ALTURA e FATOR DE BALANCEAMENTO
int AVL::altura(NoAVL* no) const {
    return (no == nullptr) ? -1 : no->altura;
}

// FB = altura da esquerda - altura da direita
int AVL::fatorBalanceamento(NoAVL* no) const {
    if (no == nullptr) return 0;
    return altura(no->esq) - altura(no->dir);
}

// altura do nó = 1 + maior altura entre os filhos
void AVL::atualizarAltura(NoAVL* no) {
    int he = altura(no->esq);
    int hd = altura(no->dir);
    no->altura = 1 + (he > hd ? he : hd);
}

int AVL::altura() const { return altura(raiz); }

// ROTAÇÃO SIMPLES À DIREITA  (resolve o caso EE)
NoAVL* AVL::rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esq;
    NoAVL* B = x->dir;

    x->dir = y;
    y->esq = B;

    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

// ROTAÇÃO SIMPLES À ESQUERDA  (resolve o caso DD) - espelho da anterior
NoAVL* AVL::rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->dir;
    NoAVL* B = y->esq;

    y->esq = x;
    x->dir = B;

    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

// BALANCEAR: verifica o FB e aplica a rotação correta (4 casos)
NoAVL* AVL::balancear(NoAVL* no) {
    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    if (fb > 1) {
        if (fatorBalanceamento(no->esq) >= 0) {
            // Caso EE (Esquerda-Esquerda): rotação simples à direita
            if (mostrarRotacoes)
                cout << "  [EE] no " << no->valor << " (FB=+2): rotacao simples a DIREITA" << endl;
            return rotacaoDireita(no);
        } else {
            // Caso ED (Esquerda-Direita): rotação dupla
            if (mostrarRotacoes)
                cout << "  [ED] no " << no->valor << " (FB=+2, filho FB=-1): rotacao dupla "
                     << "(esquerda em " << no->esq->valor << ", direita em " << no->valor << ")" << endl;
            no->esq = rotacaoEsquerda(no->esq);
            return rotacaoDireita(no);
        }
    }

    if (fb < -1) {
        if (fatorBalanceamento(no->dir) <= 0) {
            // Caso DD (Direita-Direita): rotação simples à esquerda
            if (mostrarRotacoes)
                cout << "  [DD] no " << no->valor << " (FB=-2): rotacao simples a ESQUERDA" << endl;
            return rotacaoEsquerda(no);
        } else {
            // Caso DE (Direita-Esquerda): rotação dupla
            if (mostrarRotacoes)
                cout << "  [DE] no " << no->valor << " (FB=-2, filho FB=+1): rotacao dupla "
                     << "(direita em " << no->dir->valor << ", esquerda em " << no->valor << ")" << endl;
            no->dir = rotacaoDireita(no->dir);
            return rotacaoEsquerda(no);
        }
    }

    return no;
}

// INSERÇÃO  -  O(log n)
void AVL::inserir(int valor) { raiz = inserir(raiz, valor); }

NoAVL* AVL::inserir(NoAVL* no, int valor) {
    if (no == nullptr) return new NoAVL(valor);

    if (valor < no->valor)
        no->esq = inserir(no->esq, valor);
    else if (valor > no->valor)
        no->dir = inserir(no->dir, valor);
    else
        return no;

    return balancear(no);
}

// REMOÇÃO  -  O(log n)
void AVL::remover(int valor) { raiz = remover(raiz, valor); }

NoAVL* AVL::remover(NoAVL* no, int valor) {
    if (no == nullptr) return nullptr;

    if (valor < no->valor) {
        no->esq = remover(no->esq, valor);
    } else if (valor > no->valor) {
        no->dir = remover(no->dir, valor);
    } else {
        if (no->esq == nullptr || no->dir == nullptr) {
            NoAVL* filho = (no->esq != nullptr) ? no->esq : no->dir;
            delete no;
            return filho;
        }
        // dois filhos: copia o sucessor e remove ele da direita
        NoAVL* suc = no->dir;
        while (suc->esq != nullptr) suc = suc->esq;
        no->valor = suc->valor;
        no->dir = remover(no->dir, suc->valor);
    }
    return balancear(no);
}

// BUSCA  -  igual à BST (iterativa aqui, para variar)
bool AVL::buscar(int valor) const {
    NoAVL* atual = raiz;
    while (atual != nullptr) {
        if (valor == atual->valor) return true;
        atual = (valor < atual->valor) ? atual->esq : atual->dir;
    }
    return false;
}

// PERCURSOS
void AVL::emOrdem() const  { emOrdem(raiz);  cout << endl; }
void AVL::preOrdem() const { preOrdem(raiz); cout << endl; }
void AVL::posOrdem() const { posOrdem(raiz); cout << endl; }

void AVL::emOrdem(NoAVL* no) const {
    if (!no) return;
    emOrdem(no->esq); cout << no->valor << " "; emOrdem(no->dir);
}
void AVL::preOrdem(NoAVL* no) const {
    if (!no) return;
    cout << no->valor << " "; preOrdem(no->esq); preOrdem(no->dir);
}
void AVL::posOrdem(NoAVL* no) const {
    if (!no) return;
    posOrdem(no->esq); posOrdem(no->dir); cout << no->valor << " ";
}

void AVL::emNivel() const {
    if (!raiz) { cout << endl; return; }
    queue<NoAVL*> fila;
    fila.push(raiz);
    while (!fila.empty()) {
        NoAVL* atual = fila.front(); fila.pop();
        cout << atual->valor << " ";
        if (atual->esq) fila.push(atual->esq);
        if (atual->dir) fila.push(atual->dir);
    }
    cout << endl;
}

// IMPRESSÃO "DEITADA" mostrando o FB de cada nó entre colchetes
void AVL::imprimir() const {
    if (raiz == nullptr) cout << "(arvore vazia)" << endl;
    else imprimir(raiz, 0);
}

void AVL::imprimir(NoAVL* no, int nivel) const {
    if (no == nullptr) return;
    imprimir(no->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "        ";
    int fb = fatorBalanceamento(no);
    cout << no->valor << "[" << (fb > 0 ? "+" : "") << fb << "]" << endl;
    imprimir(no->esq, nivel + 1);
}
