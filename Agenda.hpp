#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include "Lista.cpp"

struct Compromisso
{

    int hora, minuto;       // Hora do compromisso
    std::string descricao;       // Descricao do compromisso

};

struct Mes
{

    int dias;   // Numero de dias do mes
    ListaEncadeada<Compromisso> *dia;       // Compromissos de cada dia

};

class Agenda
{

private:

    // Meses do ano
    ListaEncadeada<Mes> meses;

    // Busca um mes e dia
    // Retorna a lista de compromissos do dia
    ListaEncadeada<Compromisso>* buscarMes(int mes, int dia);

    // Busca um compromisso e o retorna
    Compromisso* buscarCompromisso(ListaEncadeada<Compromisso> &c, int hora, int minuto);

    bool agendaAberta;

public:

    // Insere um compromisso
    void insereCompromisso(int mes, int dia, int hora, int minuto, std::string descricao);

    // Apaga um compromisso
    void apagaCompromisso(int mes, int dia, int hora, int minuto);

    // Verifica se existe um compromisso
    void buscarCompromisso(int mes, int dia, int hora, int minuto);

    // Lista os compromissos
    void listarCompromissos();

    // Abre a agenda
    void abreAgenda();

    // Fecha a agenda
    // Retorna se a agenda foi ou nao fechada
    bool fechaAgenda();

    // Construtor
    Agenda();

    // Destrutor
    ~Agenda();

};

#endif
