#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

struct RomanNumeral {
    int value;            // Значение римского символа
    const char* symbol;   // Римский символ
};

// Хэш-таблица римских цифр
struct HashTable {
    RomanNumeral table[13];

    // Конструктор
    HashTable() {
        // Заполнение таблицы
        table[0] = {1000, "M"};
        table[1] = {900, "CM"};
        table[2] = {500, "D"};
        table[3] = {400, "CD"};
        table[4] = {100, "C"};
        table[5] = {90, "XC"};
        table[6] = {50, "L"};
        table[7] = {40, "XL"};
        table[8] = {10, "X"};
        table[9] = {9, "IX"};
        table[10] = {5, "V"};
        table[11] = {4, "IV"};
        table[12] = {1, "I"};
    }
};

string intToRoman(int num, const HashTable& hashTable) {
    string result;

    // Проходим по хэш-таблице
    for (int i = 0; i < 13; ++i) {
        while (num >= hashTable.table[i].value) {
            result += hashTable.table[i].symbol; // Добавляем римский символ
            num -= hashTable.table[i].value;     // Уменьшаем число
        }
    }
    return result;
}

int main() {
    system("chcp 65001");
    int number;
    cout << "Введите целое число (1-3999): ";
    cin >> number;

    if (number <= 0 || number > 3999) {
        cout << "Пожалуйста, введите число в диапазоне от 1 до 3999." << endl;
        return 1;
    }

    HashTable hashTable; // Создаем экземпляр хэш-таблицы
    string roman = intToRoman(number, hashTable);
    cout << "Римская цифра: " << roman << endl;

    return 0;
}


