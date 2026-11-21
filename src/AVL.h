// AVL.h  -  Árvore AVL (Adelson-Velsky e Landis)
#ifndef AVL_H
#define AVL_H

struct NoAVL {
    int valor;
    int altura;
    NoAVL* esq;
    NoAVL* dir;

    explicit NoAVL(int v) : valor(v), altura(0), esq(nullptr), dir(nullptr) {}
};

class AVL {
public:
    AVL();
    ~AVL();

    void inserir(int valor);
    void remover(int valor);
    bool buscar(int valor) const;

    void emOrdem() const;
    void preOrdem() const;
    void posOrdem() const;
    void emNivel() const;

    int altura() const;
    bool vazia() const;
    void imprimir() const;

    // Se true, imprime no console cada rotação feita (ótimo para a aula)
    void setMostrarRotacoes(bool mostrar) { mostrarRotacoes = mostrar; }

private:
    NoAVL* raiz;
    bool mostrarRotacoes;

    int  altura(NoAVL* no) const;
    int  fatorBalanceamento(NoAVL* no) const;
    void atualizarAltura(NoAVL* no);

    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    NoAVL* balancear(NoAVL* no);

    NoAVL* inserir(NoAVL* no, int valor);
    NoAVL* remover(NoAVL* no, int valor);
    void   emOrdem(NoAVL* no) const;
    void   preOrdem(NoAVL* no) const;
    void   posOrdem(NoAVL* no) const;
    void   imprimir(NoAVL* no, int nivel) const;
    void   destruir(NoAVL* no);
};

#endif
