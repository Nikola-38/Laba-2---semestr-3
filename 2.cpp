#include <iostream>
#include <string>
#include "windows.h"
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    string data;
    Node* next;
};

struct Set {
    Node* head;

    Set() : head(nullptr) {}

    ~Set() {
        clear();
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp; // Освобождаем память текущего узла
        }
    }

    bool contains(const string& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(const string& value) {
        if (contains(value)) return; // Если элемент уже существует, ничего не делаем

        Node* newNode = new Node{value, nullptr};

        if (!head || head->data > value) {
            // Вставка в начало списка
            newNode->next = head;
            head = newNode;
            return;
        }

        // Поиск позиции для вставки
        Node* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(const string& value) {
        if (!head) return;

        if (head->data == value) {
            Node* temp = head;
            head = head->next; // Удаляем первый элемент
            delete temp; // Освобождаем память
            return;
        }

        Node* current = head;
        while (current->next) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next; // Удаляем узел
                delete temp; // Освобождаем память
                return;
            }
            current = current->next;
        }
    }

    void saveToFile(const string& filePath) const {
        ofstream outFile(filePath);
        if (outFile.is_open()) {
            Node* current = head;
            while (current) {
                outFile << current->data << endl;
                current = current->next;
            }
        } else {
            cerr << "Не удалось открыть файл для записи: " << filePath << endl;
        }
    }

    void loadFromFile(const string& filePath) {
        ifstream inFile(filePath);
        if (inFile.is_open()) {
            clear();  // Очистка текущего множества
            string value;
            while (getline(inFile, value)) {
                add(value);
            }
        } else {
            cerr << "Не удалось открыть файл для чтения: " << filePath << endl;
        }
    }
};

void processQuery(Set& mySet, const string& operation, const string& value) {
    if (operation == "SETADD") {
        mySet.add(value);
        cout << "Добавлено: " << value << endl;
    } else if (operation == "SETDEL") {
        mySet.remove(value);
        cout << "Удалено: " << value << endl;
    } else if (operation == "SET_AT") {
        if (mySet.contains(value)) {
            cout << "Элемент " << value << " находится в множестве." << endl;
        } else {
            cout << "Элемент " << value << " не найден в множестве." << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    system("chcp 65001");
    string filePath;
    string operation;
    string value;

    for (int i = 1; i < argc; i += 2) {
        if (string(argv[i]) == "--file") {
            filePath = argv[i + 1];
        } else if (string(argv[i]) == "--query") {
            istringstream iss(argv[i + 1]);
            iss >> operation >> value;
        }
    }

    Set mySet;
    mySet.loadFromFile(filePath); // Загружаем множество из файла

    // Обработка запроса
    processQuery(mySet, operation, value);

    mySet.saveToFile(filePath); // Сохраняем множество в файл

    return 0;
}


