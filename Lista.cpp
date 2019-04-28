#include <iostream>
#include "Lista.hpp"

// Insere na lista
template <typename T>
int ListaEncadeada<T>::quantCel()
{
    return quantidade;
}

// Insere na lista
template <typename T>
void ListaEncadeada<T>::inserir(T dados)
{

    // Auxiliar para percorrer a lista
    Celula* aux = lista;

    // Percorre ate que se chegue no final da lista
    while(aux->prox != NULL) {
        aux = aux->prox;
    }

    // Aloca uma nova celula
    aux->prox = new Celula;
    aux->prox->dados = dados;
    aux->prox->prox = NULL;

    // Aumenta a quantidade
    quantidade++;

}

// Remove na lista
template <typename T>
void ListaEncadeada<T>::remover(T* dados)
{

    // Auxiliar para percorrer a lista
    Celula* aux = lista;
    Celula* aux2;

    // Percorre ate que se chegue no final da lista
    while(aux->prox != NULL && &aux->prox->dados != dados) {
        aux = aux->prox;
    }

    // Apaga o item de lista, caso encontrado
    if(aux->prox != NULL) {


        // Armazena a celula a ser deletada
        aux2 = aux->prox;

        // Se a posicao atual percorrida e a ser deletada, retorna uma posicao
        if(posatual == aux2) posatual = aux;

        // Aponta para proxima posicao
        aux->prox = aux2->prox;

        // Deleta a celula
        delete aux2;

        // Diminui a lista
        quantidade--;

    }

}

// Apaga a lista
template <typename T>
void ListaEncadeada<T>::apagaLista()
{

    // Auxiliar para percorrer a lista
    Celula* aux = lista->prox;
    Celula* aux2;

    // Apaga cade elemento da lista
    while(aux != NULL) {

        aux2 = aux->prox;
        delete aux;
        aux = aux2;

    }

    posatual = lista;

    // Zera a lista
    quantidade = 0;

}

// Dados da celula atual
template <typename T>
T* ListaEncadeada<T>::proxCel()
{

    if(posatual->prox == NULL) return NULL;

    // Muda a posicao atual para proxima
    posatual = posatual->prox;

    return &posatual->dados;

}

// Retorna a celula cabeca
template <typename T>
T* ListaEncadeada<T>::inicio() {

    // Vai para a primeira celula valida, e verifica se existe
    posatual = lista->prox;

    if(posatual == NULL) return NULL;

    return &posatual->dados;

}

// Construtor
template <typename T>
ListaEncadeada<T>::ListaEncadeada()
{

    // Cria celula cabeca
    lista = new Celula();
    lista->prox = NULL;
    posatual = lista;

    // Coloca a quantidade de elementos como 0
    quantidade = 0;

}

// Destrutor
template <typename T>
ListaEncadeada<T>::~ListaEncadeada()
{

    // Apaga a lista
    apagaLista();
    delete lista;

}
