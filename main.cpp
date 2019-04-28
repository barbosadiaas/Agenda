#include <iostream>
#include <limits>
#include "Agenda.hpp"

using namespace std;

int main()
{

    // Objeto de agenda
    Agenda a;

    // leitura
    int entrada, mes, dia, hora, minuto;
    string descricao;

    // Fechar agenda
    bool fechar = false;

    // Menu
    do {

        cout << "1. Abrir a Agenda\n2. Insere compromisso\n3. Remove compromisso\n4. Lista compromissos\n";
        cout << "5. Verifica se existe compromisso agendado\n6. Fecha Agenda\n";
        cin >> entrada;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(entrada) {

            case 1:
                a.abreAgenda();
                cout << "AGENDA ABERTA\n";
                break;
            case 2:
                cout << "Digite o mes e o dia (em numeral)\n";
                cin >> mes >> dia;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite a hora e o minuto no formato HH MM\n";
                cin >> hora >> minuto;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite a descricao do compromisso\n";
                getline(cin, descricao);
                a.insereCompromisso(mes, dia, hora, minuto, descricao);
                break;
            case 3:
                cout << "Digite o mes e o dia (em numeral)\n";
                cin >> mes >> dia;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite a hora e o minuto no formato HH MM\n";
                cin >> hora >> minuto;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                a.apagaCompromisso(mes, dia, hora, minuto);
                break;
            case 4:
                a.listarCompromissos();
                break;
            case 5:
                cout << "Digite o mes e o dia (em numeral)\n";
                cin >> mes >> dia;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite a hora e o minuto no formato HH MM\n";
                cin >> hora >> minuto;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                a.buscarCompromisso(mes, dia, hora, minuto);
                break;
            case 6:
                fechar = a.fechaAgenda();
                break;
            // Valor diferente das opcoes do menu
            default:
                cout << "Valor invalido\n";
                cin.clear();
                break;
        }

        cout << endl;

    // Sai da agenda
    } while(!fechar);

    return 0;
}
