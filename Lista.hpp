#ifndef LISTA_H
#define LISTA_H

// Classe da lista encadeada
template <typename T>
class ListaEncadeada {
private:

    struct Celula
    {

        T dados;                // Dados da celula
        Celula* prox;    // Proxima celula

    };

    // Conjunto de celulas da lista
    Celula* lista;

    // Posicao atual na lista
    Celula* posatual;

    // Quantidade de celulas
    int quantidade;

public:

    // Quantidade de celulas
    int quantCel();

    // Insere na lista
    void inserir(T dados);

     // Remove na lista
    void remover(T* dados);

    // Apaga a lista
    void apagaLista();

    // Retorna os dados da proxima celula
    T* proxCel();

    // Retorna os dados da primeira celula valida
    T* inicio();

    // Construtor
    ListaEncadeada();

    // Destrutor
    ~ListaEncadeada();
};

#endif
