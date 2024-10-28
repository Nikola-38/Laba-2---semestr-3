#include <iostream>
#include <algorithm>
#include "windows.h"

using namespace std;

struct AVLNode {
    int data = 0;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int balance = 0;
};

// Функция для вычисления высоты узла
int HeightAVL(AVLNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return max(HeightAVL(root->left), HeightAVL(root->right)) + 1;
}

// Функция для установки баланса узла
void SetBalanceAVL(AVLNode* root) {
    if (root != nullptr) {
        root->balance = HeightAVL(root->left) - HeightAVL(root->right);
    }
}

// Функция для вращения вправо
AVLNode* RotateRight(AVLNode* root) {
    AVLNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    SetBalanceAVL(root);
    SetBalanceAVL(newRoot);
    return newRoot;
}

// Функция для вращения влево
AVLNode* RotateLeft(AVLNode* root) {
    AVLNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    SetBalanceAVL(root);
    SetBalanceAVL(newRoot);
    return newRoot;
}

// Функция для вставки узла
AVLNode* InsertAVL(AVLNode* root, int value) {
    if (root == nullptr) {
        return new AVLNode{value};
    }
    if (value < root->data) {
        root->left = InsertAVL(root->left, value);
    } else if (value > root->data) {
        root->right = InsertAVL(root->right, value);
    } else {
        return root; // Дубликаты не добавляем
    }

    SetBalanceAVL(root);

    // Проверка баланса и выполнение вращений
    if (root->balance > 1) {
        if (root->left->balance < 0) {
            root->left = RotateLeft(root->left); // Левый правый случай
        }
        return RotateRight(root); // Левый левый случай
    }
    if (root->balance < -1) {
        if (root->right->balance > 0) {
            root->right = RotateRight(root->right); // Правый левый случай
        }
        return RotateLeft(root); // Правый правый случай
    }

    return root; // Возвращаем неизменённый корень
}

// Функция для проверки сбалансированности дерева
bool IsBalanced(AVLNode* root) {
    if (root == nullptr) return true;

    int leftHeight = HeightAVL(root->left);
    int rightHeight = HeightAVL(root->right);

    return (abs(leftHeight - rightHeight) <= 1) &&
           IsBalanced(root->left) &&
           IsBalanced(root->right);
}

int main() {
    system("chcp 65001");
    AVLNode* root = nullptr;
    int value;

    cout << "Введите числа (нечисло для завершения): ";
    while (cin >> value) {
        root = InsertAVL(root, value);
    }

    // Проверка сбалансированности дерева
    if (IsBalanced(root)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}




