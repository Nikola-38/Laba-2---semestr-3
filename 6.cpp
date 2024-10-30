#include <iostream>
#include <string>

using namespace std;

struct RomanNumeral {
    int value;            // Значение римского символа
    const char* symbol;   // Римский символ
};

struct HashNode {
    RomanNumeral numeral;
    HashNode* next;
};

class HashTable {
private:
    HashNode* table[13]; // Массив указателей на узлы

public:
    // Конструктор
    HashTable() {
        // Инициализация таблицы
        for (int i = 0; i < 13; ++i) {
            table[i] = nullptr;
        }
        // Заполнение таблицы
        insert(1000, "M");
        insert(900, "CM");
        insert(500, "D");
        insert(400, "CD");
        insert(100, "C");
        insert(90, "XC");
        insert(50, "L");
        insert(40, "XL");
        insert(10, "X");
        insert(9, "IX");
        insert(5, "V");
        insert(4, "IV");
        insert(1, "I");
    }

    // Метод для вставки узла в хэш-таблицу
    void insert(int value, const char* symbol) {
        HashNode* newNode = new HashNode{{value, symbol}, nullptr};
        for (int i = 0; i < 13; ++i) {
            if (table[i] == nullptr) {
                table[i] = newNode;
                return;
            }
        }
    }

    // Метод для получения римского символа по его значению
    const char* getSymbol(int value) {
        for (int i = 0; i < 13; ++i) {
            if (table[i] != nullptr && table[i]->numeral.value == value) {
                return table[i]->numeral.symbol;
            }
        }
        return nullptr; // Если не найдено
    }

    // Деструктор для освобождения памяти
    ~HashTable() {
        for (int i = 0; i < 13; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }
};

string intToRoman(int num, HashTable& hashTable) {
    string result;

    // Проходим по хэш-таблице
    for (int value : {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}) {
        while (num >= value) {
            result += hashTable.getSymbol(value); // Добавляем римский символ
            num -= value;                         // Уменьшаем число
        }
    }
    return result;
}

int main() {
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
