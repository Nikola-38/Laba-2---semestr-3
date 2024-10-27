#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Узел стека
struct NodeS {
    int data;
    NodeS* next;
};

// Стек
struct Stack {
    NodeS* head = nullptr;
};

// Добавление элемента в стек (push)
void pushS(Stack* stack, int data) {
    NodeS* new_NodeS = new NodeS{data, nullptr};
    new_NodeS->next = stack->head;
    stack->head = new_NodeS;
}

// Удаление элемента из стека (pop)
int popS(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return 0;
    }

    NodeS* temp = stack->head;
    int data = temp->data;
    stack->head = stack->head->next;
    delete temp;
    return data;
}

// Функция для определения приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для конвертации выражения в постфиксное
string infixToPostfix(const string& expression) {
    string result;
    Stack operators; // Используем собственный стек для операторов
    operators.head = nullptr; // Инициализация

    for (size_t i = 0; i < expression.length(); i++) {
        char token = expression[i];

        // Если символ - число, добавляем его к результату
        if (isdigit(token)) {
            while (i < expression.length() && isdigit(expression[i])) {
                result += expression[i++];
            }
            result += ' '; // Добавляем пробел между числами
            i--; // Вернуться на один шаг назад, так как цикл увеличивает i
        }
        // Если оператор, обрабатываем его
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (operators.head != nullptr && precedence(operators.head->data) >= precedence(token)) {
                result += (char)operators.head->data;
                result += ' ';
                popS(&operators);
            }
            pushS(&operators, token);
        }
    }

    // Добавляем оставшиеся операторы
    while (operators.head != nullptr) {
        result += (char)operators.head->data;
        result += ' ';
        popS(&operators);
    }

    return result;
}

// Функция для вычисления постфиксного выражения
int evaluatePostfix(const string& expression) {
    Stack stack;
    string token;
    size_t pos = 0;

    while (pos < expression.length()) {
        size_t end = expression.find(' ', pos);
        if (end == string::npos) {
            end = expression.length();
        }

        token = expression.substr(pos, end - pos);
        pos = end + 1;

        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            pushS(&stack, stoi(token));
        } else if (!token.empty()) {
            int operand2 = popS(&stack);
            int operand1 = popS(&stack);
            int result = 0;

            if (token == "+") result = operand1 + operand2;
            else if (token == "-") result = operand1 - operand2;
            else if (token == "*") result = operand1 * operand2;
            else if (token == "/") {
                if (operand2 == 0) {
                    cout << "Ошибка: деление на ноль!" << endl;
                    return 0;
                }
                result = operand1 / operand2;
            }
            pushS(&stack, result);
        }

        if (end >= expression.length()) {
            break;
        }
    }

    return popS(&stack);
}

int main() {
    system("chcp 65001");
    string infixExpression;

    cout << "Введите выражение: ";
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Постфиксное выражение: " << postfixExpression << endl;

    int result = evaluatePostfix(postfixExpression);
    cout << "Результат: " << result << endl;

    return 0;
}
