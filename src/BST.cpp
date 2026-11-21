// BST.cpp  -  Implementação da Árvore Binária de Busca
#include "BST.h"
#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

BST::BST() : raiz(nullptr) {}

BST::~BST() { destruir(raiz); }

// Libera a memória em PÓS-ORDEM: primeiro os filhos, depois o próprio nó.
void BST::destruir(NoBST* no) {
    if (no == nullptr) return;
    destruir(no->esq);
    destruir(no->dir);
    delete no;
}

bool BST::vazia() const { return raiz == nullptr; }

// INSERÇÃO  -  O(h)
void BST::inserir(int valor) { raiz = inserir(raiz, valor); }

NoBST* BST::inserir(NoBST* no, int valor) {
    if (no == nullptr)
        return new NoBST(valor);

    if (valor < no->valor)
        no->esq = inserir(no->esq, valor);
    else if (valor > no->valor)
        no->dir = inserir(no->dir, valor);
    // valor igual: já existe, não faz nada

    return no;
}

// BUSCA  -  O(h)
bool BST::buscar(int valor) const { return buscar(raiz, valor); }

bool BST::buscar(NoBST* no, int valor) const {
    if (no == nullptr) return false;
    if (valor == no->valor) return true;
    if (valor < no->valor) return buscar(no->esq, valor);
    return buscar(no->dir, valor);
}

// MÍNIMO e MÁXIMO
int BST::minimo() const {
    if (raiz == nullptr) throw runtime_error("arvore vazia");
    NoBST* atual = raiz;
    while (atual->esq != nullptr) atual = atual->esq;
    return atual->valor;
}

int BST::maximo() const {
    if (raiz == nullptr) throw runtime_error("arvore vazia");
    NoBST* atual = raiz;
    while (atual->dir != nullptr) atual = atual->dir;
    return atual->valor;
}

// SUCESSOR (próximo maior valor)
bool BST::sucessor(int valor, int& resposta) const {
    NoBST* atual = raiz;
    NoBST* ancestral = nullptr;

    // 1) procura o nó, guardando o último lugar onde viramos à esquerda
    while (atual != nullptr && atual->valor != valor) {
        if (valor < atual->valor) {
            ancestral = atual;
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    if (atual == nullptr) return false;

    // 2) Caso 1: tem subárvore direita
    if (atual->dir != nullptr) {
        NoBST* p = atual->dir;
        while (p->esq != nullptr) p = p->esq;
        resposta = p->valor;
        return true;
    }
    // 3) Caso 2: usa o ancestral
    if (ancestral == nullptr) return false;
    resposta = ancestral->valor;
    return true;
}

// ANTECESSOR: é o "espelho" do sucessor (troca esquerda <-> direita).
bool BST::antecessor(int valor, int& resposta) const {
    NoBST* atual = raiz;
    NoBST* ancestral = nullptr;

    while (atual != nullptr && atual->valor != valor) {
        if (valor > atual->valor) {
            ancestral = atual;
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    if (atual == nullptr) return false;

    if (atual->esq != nullptr) {
        NoBST* p = atual->esq;
        while (p->dir != nullptr) p = p->dir;
        resposta = p->valor;
        return true;
    }
    if (ancestral == nullptr) return false;
    resposta = ancestral->valor;
    return true;
}

// REMOÇÃO POR CÓPIA  -  O(h)
void BST::removerPorCopia(int valor) { raiz = removerPorCopia(raiz, valor); }

NoBST* BST::removerPorCopia(NoBST* no, int valor) {
    if (no == nullptr) return nullptr;

    if (valor < no->valor) {
        no->esq = removerPorCopia(no->esq, valor);
    } else if (valor > no->valor) {
        no->dir = removerPorCopia(no->dir, valor);
    } else {
        if (no->esq == nullptr) {
            NoBST* filho = no->dir;
            delete no;
            return filho;
        }
        if (no->dir == nullptr) {
            NoBST* filho = no->esq;
            delete no;
            return filho;
        }
        // caso C: dois filhos
        NoBST* suc = no->dir;
        while (suc->esq != nullptr) suc = suc->esq;
        no->valor = suc->valor;
        no->dir = removerPorCopia(no->dir, suc->valor);
    }
    return no;
}

// REMOÇÃO POR FUSÃO  -  O(h)
void BST::removerPorFusao(int valor) { raiz = removerPorFusao(raiz, valor); }

NoBST* BST::removerPorFusao(NoBST* no, int valor) {
    if (no == nullptr) return nullptr;

    if (valor < no->valor) {
        no->esq = removerPorFusao(no->esq, valor);
        return no;
    }
    if (valor > no->valor) {
        no->dir = removerPorFusao(no->dir, valor);
        return no;
    }

    NoBST* novoTopo;
    if (no->esq == nullptr) {
        novoTopo = no->dir;
    } else if (no->dir == nullptr) {
        novoTopo = no->esq;
    } else {
        NoBST* maiorEsq = no->esq;
        while (maiorEsq->dir != nullptr) maiorEsq = maiorEsq->dir;
        maiorEsq->dir = no->dir;
        novoTopo = no->esq;
    }
    delete no;
    return novoTopo;
}

// PERCURSOS EM PROFUNDIDADE (recursivos)  -  O(n)
void BST::emOrdem() const  { emOrdem(raiz);  cout << endl; }
void BST::preOrdem() const { preOrdem(raiz); cout << endl; }
void BST::posOrdem() const { posOrdem(raiz); cout << endl; }

void BST::emOrdem(NoBST* no) const {
    if (no == nullptr) return;
    emOrdem(no->esq);
    cout << no->valor << " ";
    emOrdem(no->dir);
}

void BST::preOrdem(NoBST* no) const {
    if (no == nullptr) return;
    cout << no->valor << " ";
    preOrdem(no->esq);
    preOrdem(no->dir);
}

void BST::posOrdem(NoBST* no) const {
    if (no == nullptr) return;
    posOrdem(no->esq);
    posOrdem(no->dir);
    cout << no->valor << " ";
}

// PERCURSO EM LARGURA (level-order)  -  O(n)
void BST::emNivel() const {
    if (raiz == nullptr) { cout << endl; return; }
    queue<NoBST*> fila;
    fila.push(raiz);
    while (!fila.empty()) {
        NoBST* atual = fila.front();
        fila.pop();
        cout << atual->valor << " ";
        if (atual->esq) fila.push(atual->esq);
        if (atual->dir) fila.push(atual->dir);
    }
    cout << endl;
}

// ALTURA e TAMANHO
int BST::altura() const { return altura(raiz); }

int BST::altura(NoBST* no) const {
    if (no == nullptr) return -1;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    return 1 + (he > hd ? he : hd);
}

int BST::tamanho() const { return tamanho(raiz); }

int BST::tamanho(NoBST* no) const {
    if (no == nullptr) return 0;
    return 1 + tamanho(no->esq) + tamanho(no->dir);
}

// IMPRESSÃO "DEITADA": a raiz fica à esquerda, a direita fica em cima.
void BST::imprimir() const {
    if (raiz == nullptr) cout << "(arvore vazia)" << endl;
    else imprimir(raiz, 0);
}

void BST::imprimir(NoBST* no, int nivel) const {
    if (no == nullptr) return;
    imprimir(no->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "      ";
    cout << no->valor << endl;
    imprimir(no->esq, nivel + 1);
}
