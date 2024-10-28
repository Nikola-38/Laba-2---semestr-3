#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Array {
    string* data; // Указатель на массив строк
    int size;     // Текущий размер массива
    int capacity; // Максимальная вместимость массива

    // Конструктор для инициализации массива
    Array(int cap) : size(0), capacity(cap) {
        data = new string[capacity];
    }

    // Деструктор для освобождения памяти
    ~Array() {
        delete[] data;
    }

    // Метод для добавления слова в массив
    void add(const string& word) {
        if (size < capacity) {
            data[size++] = word;
        }
    }

    // Метод для проверки наличия слова в массиве
    bool contains(const string& word) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == word) {
                return true;
            }
        }
        return false;
    }
};

// Функция для проверки наличия ровно одного ударения
bool hasExactlyOneStress(const string& word) {
    int stressCount = 0;
    for (char ch : word) {
        if (isupper(ch)) {//проверяет находится ли переданный ей символ в верхнем регистре
            stressCount++;
        }
    }
    return stressCount == 1;
}

int main() {
    int N;
    cin >> N;
    Array dictionary(N); // Создаем массив для словаря

    // Считываем слова в словаре
    string word;
    for (int i = 0; i < N; ++i) {
        cin >> word;
        dictionary.add(word);
    }

    cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода N
    string text;
    getline(cin, text); // Считываем строку текста

    int errorCount = 0;
    istringstream stream(text);
    string currentWord;

    while (stream >> currentWord) {
        if (dictionary.contains(currentWord)) {
            // Слово есть в словаре, оно правильное
            continue; 
        } else {
            // Слово отсутствует в словаре, проверяем количество ударений
            if (!hasExactlyOneStress(currentWord)) {
                errorCount++; // Считаем ошибку, если ударений нет или больше одного
            }
        }
    }

    cout << errorCount << endl;
    return 0;
}
