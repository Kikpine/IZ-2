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

typedef struct Cell {
    char content = 'Х';
    bool knob = false;
} Cell;

bool Check_Input(string Input);
void Make_Tape(string Input, vector <Cell>& Tape);
void Print_Tape(vector <Cell>& Tape);

int main()
{
    setlocale(LC_ALL, "Russian");

    string Input_string;
    vector <Cell> Tape;
    
    bool flag = 1;
    do {
        cout << "Введите входные данные: ";
        cin >> Input_string;

        if (Check_Input(Input_string) == 1) {
            Make_Tape(Input_string, Tape);
            
            cout << "Начальная конфигурация машины:" << endl;
            Print_Tape(Tape);   // Print start position

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

void Make_Tape(string Input, vector <Cell>& Tape) {
    Cell Temp_cell;
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

void Print_Tape(vector <Cell> &Tape) {
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