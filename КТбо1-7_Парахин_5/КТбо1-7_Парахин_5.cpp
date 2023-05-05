/*
МОП ЭВМ ИКТИБ ЮФУ
Программирование и основы теории алгоритмов 2
Парахин А.О. КТбо1-7
Индивидуальное задание №2 Вариант 5
XX.05.2023
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

typedef struct Tape_Cell {
    char symbol = 'X';
    bool knob = false;
} Tape_Cell;

typedef struct Table_Cell {
    char new_symbol;
    char direction;
    int condition;
} Table_Cell;

bool Check_Input(string Input);
void Make_Tape(string Input, vector <Tape_Cell>& Tape);
void Print_Tape(vector <Tape_Cell>& Tape);
void Make_Table(map<char, vector <Table_Cell>>& Table);
void Transition(int& condition, Tape_Cell*& knob, vector <Tape_Cell>& Tape, map<char, vector <Table_Cell>>& Table);

int main()
{
    setlocale(LC_ALL, "Russian");

    string Input_string;
    vector <Tape_Cell> Tape;
    map<char, vector <Table_Cell>> Table;
    
    int flag = 1;
    do {
        cout << "Введите входные данные: ";
        cin >> Input_string;
        cout << endl;
        if (Check_Input(Input_string) == 1) {
            Make_Tape(Input_string, Tape);
            
            cout << "Начальная конфигурация машины:" << endl;
            Print_Tape(Tape);
            cout << endl;

            Make_Table(Table);

            Tape_Cell* knob = &Tape[1];
            int condition = 1;

            while (condition != 0) {
                Transition(condition, knob, Tape, Table);
                Print_Tape(Tape);
                cout << "Текущее состояние машины Тьюринга: " << condition << endl << endl;
            }
            cout << "Машина завершила работу.";
        }
        else {
            cout << "Ошибка. Строка не соответствует условию. Введите целое неотрицательное двоичное число.";
        }

        Tape.clear();
        
        cout << endl << "Хотите ввести входные данные заново или выйти из программы? (1 - Ввести входные данные заново, 0 - Выйти из программы) : ";
        cin >> flag;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        if (flag != 1 && flag != 0) {
            cout << "Введена неизвестная операция. Доступные операции: 1 или 0." << endl;
            break;
        }
    } while (flag != 0);

    cout << "Вы вышли из программы." << endl;
    return 0;
}

bool Check_Input(string Input) {
    bool answer = true;
    for (auto it = Input.begin(); it != Input.end(); it++) {
        if (*it != '0' && *it != '1') {
            answer = false;
        }
    }
    return answer;
}

void Make_Tape(string Input, vector <Tape_Cell>& Tape) {
    Tape_Cell Temp_cell;
    Tape.push_back(Temp_cell);

    for (auto it = Input.begin(); it != Input.end(); it++) {
        Temp_cell.symbol = (*it);
        Temp_cell.knob = 0;
        Tape.push_back(Temp_cell);
    }

    Temp_cell.symbol = 'X';
    Temp_cell.knob = 0;
    Tape.push_back(Temp_cell);
    
    Tape[1].knob = 1;
    return;
}

void Print_Tape(vector <Tape_Cell> &Tape) {
    for (auto it = Tape.begin(); it != Tape.end(); it++) {
        cout << (*it).symbol;
    }
    cout << endl;
    for (auto it = Tape.begin(); it != Tape.end(); it++) {
        if ((*it).knob == true) {
            cout << '^';
        }
        else {
            cout << ' ';
        }
    }
    cout << endl;
    return;
}

void Make_Table(map<char,vector <Table_Cell>>&Table) {
    ifstream fin("Table.txt");
    int table_symbols, table_conditions;
    fin >> table_symbols >> table_conditions;

    Table_Cell Temp_cell;

    char symbol;
    for (int i = 0; i < table_symbols; i++) {
        fin >> symbol;

        Temp_cell.new_symbol = '0';
        Temp_cell.direction = '.';
        Temp_cell.condition = -1;
        Table[symbol].push_back(Temp_cell);

        for (int j = 0; j < table_conditions; j++) {
            fin >> Temp_cell.new_symbol >> Temp_cell.direction >> Temp_cell.condition;
            Table[symbol].push_back(Temp_cell);
        }
    }
    return;
}

void Transition(int &condition, Tape_Cell *&knob, vector <Tape_Cell>& Tape, map<char, vector <Table_Cell>>& Table){
    int condition_old = condition;
    char symbol_old = (*knob).symbol;

    condition = Table[(*knob).symbol][condition].condition;

    (*knob).symbol = Table[(*knob).symbol][condition_old].new_symbol;

    (*knob).knob = 0;
    
    if (knob == &Tape[Tape.size() - 1] && (*knob).symbol != 'X') {
        Tape_Cell Temp_cell;
        Tape.push_back(Temp_cell);
        knob = &Tape[Tape.size() - 2];
    }
    if (knob == &Tape[0] && (*knob).symbol != 'X') {
        Tape_Cell Temp_cell;
        Tape.insert(Tape.begin(), Temp_cell);
        knob = &Tape[1];
    }

    if (Table[symbol_old][condition_old].direction == '>') {
        knob++;
    }
    else if (Table[symbol_old][condition_old].direction == '<') {
        knob--;
    }

    (*knob).knob = 1;

    if (Tape[0].symbol == 'X' && Tape[1].symbol == 'X') {
        Tape.erase(Tape.begin());
        knob = &Tape[1];
    }

    return;
}