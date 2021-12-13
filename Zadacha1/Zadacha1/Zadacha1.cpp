#include <Windows.h>
#include <fstream>
#include <locale.h>
#include <iostream>
#include <string>
using namespace std;

void CreateInput() { //������� �������� � ����� � input/output
    fstream file("input.txt");
    int enterInt = 9;
    string forInput, enterStr = "0";
    while (enterStr.find_first_of("0123456789") != -1) { //���� � ������ ���� �����
        cout << "������� ������ ��� ������ � ���� = ";
        getline(cin, enterStr);
        cout << endl << endl;
        if (enterStr.find_first_of("0123456789") < -1) { //����� ������ ��� ����������� �����
            cout << "\x1b[31m������ 0: ����������� ���� ������\x1b[0m" << endl; 
        } else { //���������� ������ � ������ ���������� � �������� ������� ������ ��� ����������� �������������
            forInput = enterStr; 
            enterStr.clear(); 
        } 
    }
    if (file) { //���� input ��������
        cout << "���� input ��� ����������, ������ ������������ ���?" << endl;
        while (enterInt != 1 and enterInt != 2) { //���� ����� ������������ �����������
            cout << "1 - ��" << endl << "2 - ���" << endl << "��� ����� = ";
            getline(cin, enterStr);
            cout << endl << endl;
            if (enterStr.find_last_not_of("12") != -1 or enterStr.length() != 1) { //�������� �� �����
                cout << "\x1b[31m������ 0: ����������� ���� ������\x1b[0m\n"; 
                continue;
            } else { 
                enterInt = atof(enterStr.c_str()); 
            } 
            switch (enterInt) { //������������� ������ ������������
            case 1: { 
                file.close();
                file.open("input.txt", ios::out); 
                file << forInput; file.close(); 
                cout << "\n" << "\x1b[32m���� ������� �����������\x1b[0m" << "\n\n\n\n";  
                break; 
            } //������������ input
            case 2: { 
                file.close(); 
                cout << "\n" << "\x1b[33m���� ������� ��� ���������\x1b[0m" << "\n\n\n\n"; 
                break; 
            } //������� input
            }
        }
    } else { //���� input �� �������� - �������
        file.open("input.txt", ios::in | ios::app); 
        file << forInput;  
        file.close(); 
        cout << "\n" << "\x1b[32m���� ������� �������\x1b[0m" << "\n\n\n\n"; 
    }
    file.open("input.txt", ios::in);
    getline(file, forInput);
    cout << "\n\x1b[33m� ����� input.txt ���������: \x1b[0m\n" << forInput << "\n\n\n\n";
    file.close();
    file.open("output.txt", ios::in | ios::app); 
    file.close(); 
    cout << "\n" << "\x1b[32moutput.txt ������� ������\x1b[0m" << "\n\n\n\n"; 
}

void Archive() { //������� ������������� ������
    string inputString, outputString;
    fstream file("input.txt"); //������� ����� �����
    if (!file) { //�������� �������� �����
        cout << "\n" << "\x1b[31m������ 1: ����������� ����� �� ���������. ���������� ��������� ������� 1\x1b[0m" << "\n\n\n\n"; 
        return;
    } 
    getline(file, inputString); //������� ������ �� �����
    file.close(); //������� ����
    for (int i = 0, counterSameSimbols; i < inputString.length(); i += counterSameSimbols) { //���� ���������� ������ ��� ����� ������
        counterSameSimbols = 1; 
        outputString += inputString[i]; //������ ������� � �������� ������ 
        for (int i1 = 1; inputString[i] == inputString[i + i1]; i1++, counterSameSimbols++) {} //������� ���������� ����������� ������� 
        if (counterSameSimbols > 1) { //���� �������� ������� ������ 1, �� ���������� �����
            outputString += to_string(counterSameSimbols);
        }
    }
    file.open("output.txt", ios::out); //�������� ����� ������
    if (!file) { //�������� �������� �����
        cout << "\n" << "\x1b[31m������ 1: ����������� ����� �� ���������. ���������� ��������� ������� 1\x1b[0m" << "\n\n\n\n"; 
        return; 
    } 
    file << outputString; //�������� ���� � ����
    file.close(); //������� ����
    cout << "\n" << "\x1b[32m��������� ������� ���������\x1b[0m" << "\n\n\n\n";
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << inputString;
    cout << "\n==========================";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << outputString << "\n\n\n";
}

void Dearchive() {
    string inputString, fullNumberStr, outputString;
    int fullNumber;
    fstream file("output.txt", ios::in);
    if (!file) { //�������� �������� �����
        cout << "\n" << "\x1b[31m������ 1: ����������� ����� �� ���������. ���������� ��������� ������� 1\x1b[0m" << "\n\n\n\n";
        return;
    }
    getline(file, inputString);
    file.close();
    for (int i = 0; i < inputString.length(); i += fullNumberStr.length()) { //���� ���������� ����� � �����
        fullNumberStr.clear(); //������� fullNumberStr ����� ���������� ��������
        if (inputString[i] >= '0' and inputString[i] <= '9' and i == 0) { //���� ������ ������ �����
            cout << "\n" << "\x1b[31m������ 2: ������ ������ �����\x1b[0m" << "\n\n\n\n";
            return; 
        }
        if (inputString[i] >= '0' and inputString[i] <= '9') { //���� ������ - �����
            fullNumberStr += inputString[i]; //��������� � ������ fullNumberStr ������� �����
            for (int i1 = 1; inputString[i + i1] >= '0' and inputString[i + i1] <= '9'; i1++) { //���� ������� ������ - �����
                fullNumberStr += inputString[i + i1]; //��������� ����� � ������ ������� �����
            }
            fullNumber = stoi(fullNumberStr); //������� ���� ����� � ������ �����
            for (int i1 = 1; i1 < fullNumber; i1++) { //���� ���������� ���� ������ ��� ������������
                outputString += inputString[i - 1]; //��������� ����� � ����
            }
        } else { 
            outputString += inputString[i]; //�������� ������� ����� � ����
            fullNumberStr = '1';
        }
    }
    file.open("output.txt", ios::out); 
    if (!file) { //�������� �������� �����
        cout << "\n" << "\x1b[31m������ 1: ����������� ����� �� ���������. ���������� ��������� ������� 1\x1b[0m" << "\n\n\n\n";
        return;
    }
    file << outputString; //�������� ���� � ����
    file.close(); 
    cout << "\n" << "\x1b[32m����������� ������� ���������\x1b[0m" << "\n\n\n\n";
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << inputString;
    cout << "\n==========================";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << outputString << "\n\n\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int enterInt, endProgram = 0;
    string enterStr;
    while (endProgram == 0) { //���� ������ ���������
        cout << "1 - ������� ����� � �������� ������\n" << "2 - �������������� ����\n" << "3 - ��������������� ����\n" << "0 - ����� �� ���������\n" << "��� ����� = ";
        getline(cin, enterStr);
        cout << "\n\n";
        if ((enterStr.find_last_not_of("0123") != -1) or (enterStr.empty())) { cout << "\x1b[31m������ 0: ����������� ���� ������\x1b[0m" << endl; continue; }
        else { enterInt = atof(enterStr.c_str()); }
        if (enterInt < 0 or enterInt > 3) { cout << "\x1b[31m������ 0: ����������� ���� ������\x1b[0m" << endl; continue; }
        switch (enterInt) { //������������� ������ ������������
        case 1: { CreateInput(); break; } //������ ������� �������� ������
        case 2: { Archive(); break; } //������ ������� ���������� ������
        case 3: { Dearchive(); break; } //������ ������� ����������� �����
        case 0: { endProgram = 1; break; } //���������� ���������
        }
    }
}