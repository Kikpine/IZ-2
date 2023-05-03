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
#include <set>
using namespace std;

typedef struct Tape_Cell {
    char content = 'Х';
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

int main()
{
    setlocale(LC_ALL, "Russian");

    string Input_string;
    vector <Tape_Cell> Tape;
    map<char, vector <Table_Cell>> Table;
    
    bool flag = 1;
    do {
        cout << "Введите входные данные: ";
        cin >> Input_string;

        if (Check_Input(Input_string) == 1) {
            Make_Tape(Input_string, Tape);
            
            cout << "Начальная конфигурация машины:" << endl;
            Print_Tape(Tape);   // Print start position

            Make_Table(Table);
        }
        else {
            cout << "Неправильная строка" << endl;
        }

        Tape.clear();
        
        cout << "Хотите продолжить? ";
        cin >> flag;
    } while (flag == 1);

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
        Temp_cell.content = (*it);
        Temp_cell.knob = 0;
        Tape.push_back(Temp_cell);
    }

    Temp_cell.content = 'X';
    Temp_cell.knob = 0;
    Tape.push_back(Temp_cell);
    
    Tape[1].knob = 1;
}

void Print_Tape(vector <Tape_Cell> &Tape) {
    for (auto it = Tape.begin(); it != Tape.end(); it++) {
        cout << (*it).content;
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
}