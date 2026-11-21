// BST.h  -  Árvore Binária de Busca (Binary Search Tree)
#ifndef BST_H
#define BST_H

// Um nó da árvore: guarda o valor e dois ponteiros para os filhos.
struct NoBST {
    int valor;
    NoBST* esq;
    NoBST* dir;

    explicit NoBST(int v) : valor(v), esq(nullptr), dir(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    void inserir(int valor);
    bool buscar(int valor) const;
    void removerPorCopia(int valor);
    void removerPorFusao(int valor);

    int minimo() const;
    int maximo() const;
    bool sucessor(int valor, int& resposta) const;
    bool antecessor(int valor, int& resposta) const;

    void emOrdem() const;
    void preOrdem() const;
    void posOrdem() const;
    void emNivel() const;

    int altura() const;
    int tamanho() const;
    bool vazia() const;
    void imprimir() const;
    NoBST* getRaiz() const { return raiz; }

private:
    NoBST* raiz;

    // Funções auxiliares recursivas (recebem o nó atual)
    NoBST* inserir(NoBST* no, int valor);
    bool   buscar(NoBST* no, int valor) const;
    NoBST* removerPorCopia(NoBST* no, int valor);
    NoBST* removerPorFusao(NoBST* no, int valor);
    void   emOrdem(NoBST* no) const;
    void   preOrdem(NoBST* no) const;
    void   posOrdem(NoBST* no) const;
    int    altura(NoBST* no) const;
    int    tamanho(NoBST* no) const;
    void   imprimir(NoBST* no, int nivel) const;
    void   destruir(NoBST* no);
};

#endif
