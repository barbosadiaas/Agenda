#include "Agenda.hpp"
#include <fstream>
#include <limits>

using namespace std;

ListaEncadeada<Compromisso>* Agenda::buscarMes(int mes, int dia)
{

    // Mes ou dianao existente
    if(mes < 1 || mes > 12 || dia < 1) return NULL;

    // Auxiliar para percorrer a lista
    Mes* aux = meses.inicio();

    // Percorre a lista ate chegar no mes desejado
    while(aux != NULL && mes != 1) {
        aux = meses.proxCel();
        mes--;
    }

    // Dia nao existente
    if(dia > aux->dias) return NULL;

    return &aux->dia[dia-1];

}

Compromisso* Agenda::buscarCompromisso(ListaEncadeada<Compromisso> &c, int hora, int minuto)
{

    // Verifica se existe o horario
    if(hora < 0 || hora > 24 || minuto < 0 || minuto > 59)  return NULL;

    // Auxiliar para percorrer a lista
    Compromisso* aux = c.inicio();

    // Percorre a lista ate chegar no mes desejado
    while(aux != NULL && (aux->hora != hora || aux->minuto != minuto)) {
        aux = c.proxCel();
    }

    // Retorna a descricao do compromisso, caso existente
    if(aux != NULL) return aux;

    // String vazia
    return NULL;

}

void Agenda::buscarCompromisso(int mes, int dia, int hora, int minuto)
{

    ListaEncadeada<Compromisso>* c = buscarMes(mes, dia);

    // Verifica se existe o mes
    if(c != NULL) {

        if(hora < 0 || hora > 24 || minuto < 0 || minuto > 59) {
            cout << "Hora ou minuto nao encontrado\n";
            return;
        }

        Compromisso *comp = buscarCompromisso(*c, hora, minuto);

        // Mostra o compromisso caso existente
        if(comp != NULL) {

            cout << "------ MES " << mes << " ------\n" << "@DIA " << dia << "@\n";

            // Mostra no formato correto a hora
            if(comp->hora < 10)    cout << "0";
            cout << comp->hora << ":";
            // Mostra no formato correto o minuto
            if(comp->minuto < 10)  cout << "0";
            cout << comp->minuto << " - " << comp->descricao << "\n";
        }
        else {
            cout << "Nao existe compromisso agendado na data e horario dado\n";
        }
    }
    else {
        cout << "Mes ou dia invalido\n";
    }

}

void Agenda::insereCompromisso(int mes, int dia, int hora, int minuto, std::string descricao)
{

    // Verifica se existe o mes
    ListaEncadeada<Compromisso> *c = buscarMes(mes, dia);

    if(c != NULL) {

        if(hora < 0 || hora > 24 || minuto < 0 || minuto > 59) {
            cout << "Hora ou minuto nao encontrado\n";
        }
        // Verifica se ja nao existe um compromisso, e entao insere os dados
        else if(buscarCompromisso(*c, hora, minuto) == NULL) {

            Compromisso dados;
            dados.hora = hora;
            dados.minuto = minuto;
            dados.descricao = descricao;
            c->inserir(dados);
            cout << "Dado inserido com sucesso\n";

        }
        else {
            cout << "Ja existe um compromisso nesse dia e hora\n";
        }

    }
    else {
        cout << "Mes ou dia invalido\n";
    }

}

void Agenda::apagaCompromisso(int mes, int dia, int hora, int minuto)
{

    // Verifica se existe o mes
    ListaEncadeada<Compromisso> *c = buscarMes(mes, dia);

    if(c != NULL) {

        if(hora < 0 || hora > 24 || minuto < 0 || minuto > 59) {
            cout << "Hora ou minuto nao encontrado\n";
            return;
        }

        Compromisso* dados = buscarCompromisso(*c, hora, minuto);

        // Verifica se ja nao existe um compromisso, e entao apaga os dados
        if(dados != NULL) {
            c->remover(dados);
        }
        else {
            cout << "Compromisso nao encontrado\n";
        }

    }
    else {
        cout << "Mes ou dia invalido\n";
    }
}

void Agenda::listarCompromissos()
{

    // Auxiliares para percorrer as listas
    ListaEncadeada<Compromisso> *lc;
    Mes* m;
    Compromisso* c;

    m = meses.inicio();

    // Percorre os meses
    for(int i = 1, j; m != NULL; i++) {

        cout << "------ MES " << i << " ------\n";

        // Percorre os dias
        for(j = 1; j <= m->dias; j++) {

            lc = &m->dia[j-1];

            if(lc->quantCel() > 0) {

                c = lc->inicio();

                cout << "@DIA " << j << "@\n";

                // Mostra os compromissos armazenados
                while(c != NULL) {

                    // Mostra no formato correto a hora
                    if(c->hora < 10)    cout << "0";
                    cout << c->hora << ":";
                    // Mostra no formato correto o minuto
                    if(c->minuto < 10)  cout << "0";
                    cout << c->minuto << " - " << c->descricao << "\n";

                    c = lc->proxCel();
                }

            }
        }

        // Proximo mes
        m = meses.proxCel();
    }

}

void Agenda::abreAgenda()
{

    // Auxiliares para percorrer as listas
    ListaEncadeada<Compromisso> *lc;
    Mes* m;
    Compromisso c;

    int quantidade;

    int i, j;

    // Arquivo de entrada
    ifstream f;
    f.open("agenda.txt");

    // Arquivo nao foi aberto
    if(!f) return;

    m = meses.inicio();

    // Percorre os meses
    while(m != NULL) {

        // Percorre os dias
        for(i = 0; i < m->dias; i++) {

            // Dia atual
            lc = &m->dia[i];
            // Reinicia a lista antiga
            lc->apagaLista();

            // Mostra a quantidade de dados de um dia
            f >> quantidade;

            // Mostra os compromissos armazenados
            for(j = 0; j < quantidade; j++) {

                // Obtem os dados
                f >> c.hora >> c.minuto >> ws;
                getline(f, c.descricao);

                // Insere
                lc->inserir(c);
            }

        }

        m = meses.proxCel();

    }

    // Fecha o arquivo
    f.close();

    // Agenda foi aberta
    agendaAberta = true;

}

bool Agenda::fechaAgenda()
{

    if(!agendaAberta) {
        int opcao;

        do {

            cout << "A agenda nao foi aberta. Tem certeza que deseja salvar esta agenda?\n1 - SIM | 2 - NAO\n";
            cin >> opcao;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(opcao != 1 && opcao != 2) {
                cout << "Valor invalido\n";
            }

        } while(opcao != 1 && opcao != 2);

        // Nao salva a agenda
        if(opcao == 2)  return false;
    }

    // Auxiliares para percorrer as listas
    ListaEncadeada<Compromisso> *lc;
    Mes* m;
    Compromisso* c;

    int i, j;

    // Arquivo de saida
    ofstream f;

    f.open("agenda.txt");

    m = meses.inicio();

    // Percorre os meses
    while(m != NULL) {

        // Percorre os dias
        for(i = 0; i < m->dias; i++) {

            lc = &m->dia[i];

            // Mostra a quantidade de dados de um dia
            f << lc->quantCel() << " ";

            c = lc->inicio();

            // Mostra os compromissos armazenados
            for(j = 0; j < lc->quantCel(); j++) {

                // Mostra no formato correto a hora
                f << c->hora << " " << c->minuto << "\n" << c->descricao << "\n";
                c = lc->proxCel();
            }

        }

        // Proximo mes
        m = meses.proxCel();

    }

    // Fecha o arquivo
    f.close();

    return true;
}

// Construtor
Agenda::Agenda()
{
    // Estrutura do mes
    Mes estmes;

    //////// Armazena os meses do ano ////////

    //Janeiro
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Fevereiro
    estmes.dias = 29;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Marco
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Abril
    estmes.dias = 30;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Maio
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Junho
    estmes.dias = 30;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Julho
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Agosto
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Setembro
    estmes.dias = 30;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Outubro
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Novembro
    estmes.dias = 30;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    //Dezembro
    estmes.dias = 31;
    estmes.dia = new ListaEncadeada<Compromisso>[estmes.dias];
    meses.inserir(estmes);

    // Agenda ainda nao foi aberta
    agendaAberta = false;

}

// Destrutor
Agenda::~Agenda()
{

    Mes* m = meses.inicio();

    for(int i = 0; m != NULL; i++) {

        delete[] m->dia;

        m = meses.proxCel();
    }

}
