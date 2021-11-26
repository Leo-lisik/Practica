#include <Windows.h>
#include "Header.h"
#include <fstream>
#include <locale.h>
#define ch enterStr.find_last_not_of("-0123456789.")
#define ch2 enterStr.find_last_of("-")
#define ch3  enterStr.find_last_of(".")-enterStr.find_first_of(".")

void CreateInput() { //������� �������� � ����� � input/output
    fstream File("input.txt");
    int enterInt = 9;
    string enterStr = " 1";
    string forInput;
    while (enterStr.find_first_of("0123456789") < -1) { //���� � ������ ���� �����
        cout << "������� ������ ��� ������ � ���� = ";
        getline(cin, enterStr);
        cout << endl << endl;
        if (enterStr.find_first_of("0123456789") < -1) { cout << "\x1b[31m���������� ������� ������ ��� �����\x1b[0m" << endl; } //����� ������ ��� ����������� �����
        else { forInput = enterStr; enterStr.clear(); } //���������� ������ � ������ ���������� � �������� ������� ������ ��� ����������� �������������
    }
    if (File) { //���� input ��������
        cout << "���� input ��� ����������, ������ ������������ ���?" << endl;
        while (enterInt != 1 and enterInt != 2) { //���� ����� ������������ �����������
            cout << "1 - ��" << endl << "2 - ���" << endl;
            getline(cin, enterStr);
            cout << endl << endl;
            if ((ch != -1) or (ch2 != -1 and ch2 != 0) or (ch3 != 0)) { cout << "\x1b[31m���������� ������� ���������� �����\x1b[0m" << endl; enterInt = 9; } //�������� �� �����
            else { enterInt = atof(enterStr.c_str()); } 
            enterStr.clear(); //������� enterStr
            if (enterInt != 1 and enterInt != 2) { cout << "\x1b[31m���������� ������� ���������� �����\x1b[0m" << endl; } //�������� �� ���������� �����
            switch (enterInt) { //������������� ������ ������������
            case 1: { File.close(); remove("input.txt"); File.open("input.txt", ios::out | ios::app); File << forInput; File.close(); } //������������ input
            case 2: { File.close(); } //������� input
            }
        }
    } else { File.open("input.txt", ios::in | ios::app); File << forInput;  File.close(); } //���� input �� �������� - �������
    File.open("output.txt");
    if (!File) { File.open("output.txt", ios::in | ios::app); File.close(); } //���� output �� �������� - �������
}

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
    cout << endl << "��������� ������� ���������" << endl << endl << endl << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    CreateInput();
}