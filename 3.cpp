#include <iostream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* next;
};

struct MySet {
    Node* head;

    MySet() : head(nullptr) {}

    ~MySet() {
        while (head) {
            Node* temp = head; // Сохраняем текущий узел
            head = head->next; // Переходим к следующему
            delete temp;       // Удаляем текущий узел
        }
    }

    void insert(const string& s) {
        if (!contains(s)) {
            Node* newNode = new Node{s, head};
            head = newNode;
        }
    }

    bool contains(const string& s) const {
        Node* current = head;
        while (current) {
            if (current->value == s) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int degreeOfSimilarity(const string& genome1, const string& genome2) {
    MySet pairs1, pairs2;

    // Считаем пары для первого генома
    for (size_t i = 0; i < genome1.length() - 1; ++i) {
        string pair;
        pair += genome1[i];     // Первый символ
        pair += genome1[i + 1]; // Второй символ
        pairs1.insert(pair);
    }

    // Считаем пары для второго генома
    for (size_t i = 0; i < genome2.length() - 1; ++i) {
        string pair;
        pair += genome2[i];     // Первый символ
        pair += genome2[i + 1]; // Второй символ
        pairs2.insert(pair);
    }

    // Подсчитываем степень близости
    int similarityCount = 0;
    Node* current = pairs1.head;
    while (current) {
        if (pairs2.contains(current->value)) {
            ++similarityCount;
        }
        current = current->next;
    }

    return similarityCount;
}

int main() {
    string genome1, genome2;
    cin >> genome1 >> genome2;

    int result = degreeOfSimilarity(genome1, genome2);
    cout << result << endl;

    return 0;
}


