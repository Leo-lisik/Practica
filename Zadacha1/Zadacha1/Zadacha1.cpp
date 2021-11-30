﻿#include <Windows.h>
#include "Header.h"
#include <fstream>
#include <locale.h>
#include <iostream>
#include <string>
#define ch enterStr.find_last_not_of("-0123456789.")
#define ch2 enterStr.find_last_of("-")
#define ch3  enterStr.find_last_of(".")-enterStr.find_first_of(".")
using namespace std;

void CreateInput() { //Функция создания и ввода в input/output
    fstream file("input.txt");
    int enterInt = 9;
    string forInput, enterStr = "0";
    while (enterStr.find_first_of("0123456789") < -1) { //Пока в строке есть цифры
        cout << "Введите строку для записи в файл = ";
        getline(cin, enterStr);
        cout << endl << endl;
        if (enterStr.find_first_of("0123456789") < -1) { //Вывод ошибки при обнаружении чисел
            cout << "\x1b[31mОшибка 0: Некоректный ввод данных\x1b[0m" << endl; 
        } else { //Сохранение строки в другой переменной и очищение вводной строки для дальнейшего использования
            forInput = enterStr; 
            enterStr.clear(); 
        } 
    }
    if (file) { //Если input открылся
        cout << "Файл input уже существует, хотите перезаписать его?" << endl;
        while (enterInt != 1 and enterInt != 2) { //Пока выбор пользователя некоректный
            cout << "1 - Да" << endl << "2 - Нет" << endl << "Ваш выбор = ";
            getline(cin, enterStr);
            cout << endl << endl;
            if (enterStr.find_last_not_of("12") != -1 or enterStr.length() != 1) { //Проверка на буквы
                cout << "\x1b[31mОшибка 0: Некоректный ввод данных\x1b[0m\n"; 
            } else { 
                enterInt = atof(enterStr.c_str()); 
            } 
            switch (enterInt) { //Переключатель выбора пользователя
            case 1: { file.close(); file.open("input.txt", ios::out); file << forInput; file.close(); cout << "\n" << "\x1b[32mФайл успешно перезаписан\x1b[0m" << "\n\n\n\n"; break; } //Перезаписать input
            case 2: { file.close(); cout << "\n" << "\x1b[33mФайл остался без изменений\x1b[0m" << "\n\n\n\n"; break; } //Закрыть input
            }
        }
    } else { //Если input не открылся - создать
        file.open("input.txt", ios::in | ios::app); 
        file << forInput;  
        file.close(); 
        cout << "\n" << "\x1b[32mФайл успешно записан\x1b[0m" << "\n\n\n\n"; 
    }
    file.open("output.txt");
    if (!file) { //Если output не открылся - создать
        file.open("output.txt", ios::in | ios::app); 
        file.close(); 
        cout << "\n" << "\x1b[32moutput.txt успешно создан\x1b[0m" << "\n\n\n\n"; 
    } 
}

void Archive() { //Функция архивирования строки
    string inputString, outputString;
    fstream file("input.txt"); //Открыть файла ввода
    if (!file) { //Проверка открытия файла
        cout << "\n" << "\x1b[31mОшибка 1: Необходимые файлы не открылись. Попробуйте запустить команду 1\x1b[0m" << "\n\n\n\n"; 
        return;
    } 
    getline(file, inputString); //Считать строку из файла
    file.close(); //Закрыть файл
    for (int i = 0, counterSameSimbols; i < inputString.length(); i += counterSameSimbols) { //Цикл получающий каждый раз новый символ
        counterSameSimbols = 1; 
        outputString += inputString[i]; //Запись символа в итоговую строку 
        for (int i1 = 1; inputString[i] == inputString[i + i1]; i1++, counterSameSimbols++) {} //Счётчик количества одинакового символа 
        if (counterSameSimbols > 1) { //Если повторов символа больше 1, то записывать цифру
            outputString += to_string(counterSameSimbols);
        }
    }
    file.open("output.txt", ios::out); //Открытие файла вывода
    if (!file) { //Проверка открытия файла
        cout << "\n" << "\x1b[31mОшибка 1: Необходимые файлы не открылись. Попробуйте запустить команду 1\x1b[0m" << "\n\n\n\n"; 
        return; 
    } 
    file << outputString; //Записать итог в файл
    file.close(); //Закрыть файл
    cout << "\n" << "\x1b[32mАрхивация успешно выполнена\x1b[0m" << "\n\n\n\n";
}

void Dearchive() {
    string inputString, fullNumberStr, outputString;
    int fullNumber;
    fstream file("output.txt", ios::in);
    if (!file) { //Проверка открытия файла
        cout << "\n" << "\x1b[31mОшибка 1: Необходимые файлы не открылись. Попробуйте запустить команду 1\x1b[0m" << "\n\n\n\n";
        return;
    }
    getline(file, inputString);
    file.close();
    for (int i = 0; i < inputString.length(); i += fullNumberStr.length() + 1) { //Цикл перебирает каждый символ
        fullNumberStr.clear(); //Очистка fullNumberStr после предыдущей итерации
        //if (inputString[i] >= '0' and inputString[i] <= '9' and inputString[i - 1] >= '0' and inputString[i - 1] <= '9') { //Если предыдущий символ число и текущий, то пропустить итерацию
        //    continue; 
        //}
        cout << "what" << endl;
        if (inputString[i] >= '0' and inputString[i] <= '9' and i == 0) { //Если первый символ цифра
            cout << "\n" << "\x1b[31mОшибка 2: Первый символ цифра\x1b[0m" << "\n\n\n\n";
            return; 
        }
        if (inputString[i] >= '0' and inputString[i] <= '9') { //Если символ - цифра
            fullNumberStr += inputString[i]; //добавляем к строке fullNumberStr текущее число
            for (int i1 = 1; inputString[i + i1] >= '0' and inputString[i + i1] <= '9'; i1++) { //Пока текущий символ - число
                fullNumberStr += inputString[i + i1]; //Добавлять число в строку полного числа
            }
            fullNumber = stoi(fullNumberStr); //перевод всех чисел в единую цифру
            for (int i1 = 1; i1 < fullNumber; i1++) { //Пока количество букв меньше уже поставленных
                outputString += inputString[i - 1]; //Добавлять букву в итог
            }
        } else { 
            outputString += inputString[i]; //Добавить текущую букву в итог
        }
    }
    file.open("output.txt", ios::out); 
    if (!file) { //Проверка открытия файла
        cout << "\n" << "\x1b[31mОшибка 1: Необходимые файлы не открылись. Попробуйте запустить команду 1\x1b[0m" << "\n\n\n\n";
        return;
    }
    file << outputString; //Записать итог в файл
    file.close(); 
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int endProgram = 0;
    while (endProgram == 0) { //Цикл работы программы
        int enterInt;
        string enterStr;
        cout << "1 - Создать файлы и записать строку" << endl << "2 - Заархивировать файл" << endl << "3 - Разархивировать файл" << endl << "0 - Выход из программы" << endl << "Ваш выбор = ";
        getline(cin, enterStr);
        cout << endl << endl;
        if ((ch != -1) or (ch2 != -1 and ch2 != 0) or (ch3 != 0) or (enterStr.empty()) or (ch2 == 0)) { cout << "\x1b[31mОшибка 0: Некоректный ввод данных\x1b[0m" << endl; continue; }
        else { enterInt = atof(enterStr.c_str()); }
        if (enterInt < 0 or enterInt > 3) { cout << "\x1b[31mОшибка 0: Некоректный ввод данных\x1b[0m" << endl; }
        switch (enterInt) { //Переключатель выбора пользователя
        case 1: { CreateInput(); break; } //Запуск функции создания файлов
        case 2: { Archive(); break; } //Запуск функции зашифровки файлов
        case 3: { Dearchive(); break; } //Запуск функции расшифровки файла
        case 0: { endProgram = 1; break; } //Выключение программы
        }
    }
}