#include <Windows.h>
#include "Header.h"
#include <fstream>
#include <locale.h>
#define ch enterStr.find_last_not_of("-0123456789.")
#define ch2 enterStr.find_last_of("-")
#define ch3  enterStr.find_last_of(".")-enterStr.find_first_of(".")

void Encrypt() { //������� ���������� ������
    string inputString, outputString;
    fstream file ("input.txt"); //������� ����� �����
    if (!file.is_open()) {cout << "������ 1: ���� �� ��������. ���������� ��� ������ ��� �������." << endl; return;} //�������� �������� �����
    getline(file, inputString); //������� ������ �� �����
    file.close(); //������� ����
    for (int i = 0, counterSameSimbols; i < inputString.length(); i += counterSameSimbols - 1) { //���� ���������� ������ ��� ����� ������
        counterSameSimbols = 0; 
        outputString += inputString[i]; //������ ������� � �������� ������ 
        for (int i1 = i++; inputString[i] == inputString[i1]; i1++, counterSameSimbols++) {} //������� ���������� ����������� �������
        if (counterSameSimbols == 0) { counterSameSimbols++; } //���� ������ ����� ����, �� ��������� counterSameSimbols �� 1
        if (counterSameSimbols > 1) { //���� �������� ������� ������ 1, �� ���������� �����
            outputString += to_string(counterSameSimbols);
        }
    }
    file.open("output.txt"); //�������� ����� ������
    if (!file.is_open()) { cout << "������ 1: ���� �� ��������. ���������� ��� ������ ��� �������." << endl; return; } //�������� �������� �����
    file << outputString; //�������� ���� � ����
    file.close(); //������� ����
    cout << endl << endl << endl << "��������� ������� ���������" << endl << endl << endl << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int endProgram = 0; 
    while (endProgram == 0) { //���� ������ ���������
        int enterInt;
        string enterStr;
        cout << "1 - ������� ���� � �������� � ���� ������" << endl << "2 - �������������� ����" << endl << "3 - ��������������� ����" << endl << "0 - ����� �� ���������" << endl << "��� ����� = ";
        getline(cin, enterStr);
        if ((ch != -1) or (ch2 != -1 and ch2 != 0) or (ch3 != 0)) { enterInt = 9; } else { enterInt = atof(enterStr.c_str()); }
        switch (enterInt) { //������������� ������� ������������
        case 1: { cout << "������� � ����������" << endl; break; } //������ ������� �������� ������ � ������ � ����
        case 2: { Encrypt(); break; } //������ ������� ��������� �����
        case 3: { cout << "������� � ����������" << endl; break; } //������ ������� ������������ �����
        case 0: { endProgram = 1; break; } //����� �� ���������
        }
    }
}