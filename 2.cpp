#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    string data; // Данные узла
    Node* next;  // Указатель на следующий узел
};

struct HashSet {
    Node** table; // Указатель на массив указателей на узлы
    int size;     // Размер хеш-таблицы

    // Конструктор
    HashSet(int tableSize) : size(tableSize) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr; // Инициализация указателей
        }
    }

    // Деструктор
    ~HashSet() {
        clear(); // Освобождение памяти в деструкторе
        delete[] table; // Освобождение массива указателей
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp; // Освобождаем память текущего узла
            }
            table[i] = nullptr; // Обнуляем указатель
        }
    }

    bool contains(const string& value) const {
        int index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->data == value) {
                return true; // Элемент найден
            }
            current = current->next;
        }
        return false; // Элемент не найден
    }

    void add(const string& value) {
        if (contains(value)) {
            cout << "Уже есть значение в set:" << value << endl;
            return; // Если элемент уже существует, ничего не делаем
        }

        int index = hash(value);
        Node* newNode = new Node{value, nullptr};

        // Вставка в начало цепочки
        if (table[index] == nullptr) {
            table[index] = newNode; 
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    void remove(const string& value) {
        int index = hash(value);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next; // Удаляем узел
                } else {
                    table[index] = current->next; // Удаляем первый узел
                }
                delete current; // Освобождаем память
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void loadFromFile(const string& filePath) {
        ifstream file(filePath);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filePath << endl;
            return;
        }
        string value;
        while (getline(file, value)) {
            add(value); // Добавляем каждую строку в множество
        }
        file.close();
    }

    void saveToFile(const string& filePath) {
        ofstream file(filePath);
        if (!file) {
            cerr << "Ошибка открытия файла для записи: " << filePath << endl;
            return;
        }
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                file << current->data << endl; // Записываем данные в файл
                current = current->next;
            }
        }
        file.close();
    }

private:
    int hash(const string& value) const {
        int hashValue = 0;
        for (char c : value) {
            hashValue = (hashValue * 31 + c) % size; 
        }
        return hashValue;
    }
};

void processQuery(HashSet& mySet, const string& operation, const string& value) {
    if (operation == "SETADD") {
        mySet.add(value);
    } else if (operation == "SETDEL") {
        mySet.remove(value);
        cout << "Удалено: " << value << endl;
    } else if (operation == "SET_AT") {
        cout << "Содержит " << value << ": " << (mySet.contains(value) ? "Да" : "Нет") << endl;
    } else {
        cout << "Неизвестная операция: " << operation << endl;
    }
}

int main(int argc, char* argv[]) {
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

    HashSet mySet(100); // Создаем хеш-таблицу с размером 100
    mySet.loadFromFile(filePath); // Загружаем множество из файла

    // Обработка запроса
    processQuery(mySet, operation, value);

    mySet.saveToFile(filePath); // Сохраняем множество в файл

    return 0;
}
