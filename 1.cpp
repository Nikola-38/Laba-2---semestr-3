#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Узел стека
struct NodeS {
    bool isOperator; // Флаг, указывающий, является ли элемент оператором
    union {
        int number;   // Для хранения числа
        char op;      // Для хранения оператора
    };
    NodeS* next;
};

// Стек
struct Stack {
    NodeS* head = nullptr;
};

// Добавление числа в стек
void pushNumber(Stack* stack, int number) {
    NodeS* newNode = new NodeS;
    newNode->isOperator = false;
    newNode->number = number;
    newNode->next = stack->head;
    stack->head = newNode;
}

// Добавление оператора в стек
void pushOperator(Stack* stack, char op) {
    NodeS* newNode = new NodeS;
    newNode->isOperator = true;
    newNode->op = op;
    newNode->next = stack->head;
    stack->head = newNode;
}

// Удаление элемента из стека
NodeS* pop(Stack* stack) {
    if (stack->head == nullptr) {
        cout << "Стек пуст!" << endl;
        return nullptr;
    }

    NodeS* temp = stack->head;
    stack->head = stack->head->next;
    return temp;
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
    Stack operators;

    for (size_t i = 0; i < expression.length(); i++) {
        char token = expression[i];

        // Если символ - число, добавляем его к результату
        if (isdigit(token)) {
            while (i < expression.length() && isdigit(expression[i])) {
                result += expression[i++];
            }
            result += ' '; // Добавляем пробел между числами
            i--; // Вернуться на один шаг назад
        }
        // Если оператор
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (operators.head != nullptr && precedence(operators.head->op) >= precedence(token)) {
                result += operators.head->op;
                result += ' ';
                pop(&operators);
            }
            pushOperator(&operators, token);
        }
        // Если открывающая скобка
        else if (token == '(') {
            pushOperator(&operators, token);
        }
        // Если закрывающая скобка
        else if (token == ')') {
            while (operators.head != nullptr && operators.head->op != '(') {
                result += operators.head->op;
                result += ' ';
                pop(&operators);
            }
            pop(&operators); // Удаляем '(' из стека
        }
    }

    // Добавляем оставшиеся операторы
    while (operators.head != nullptr) {
        result += operators.head->op;
        result += ' ';
        pop(&operators);
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

        if (isdigit(token[0])) {
            pushNumber(&stack, stoi(token));
        } else if (!token.empty()) {
            NodeS* operand2Node = pop(&stack);
            NodeS* operand1Node = pop(&stack);
            if (operand1Node && operand2Node) {
                int operand2 = operand2Node->number;
                int operand1 = operand1Node->number;
                int result = 0;

                if (token == "+") result = operand1 + operand2;
                else if (token == "-") result = operand1 - operand2;
                else if (token == "*") result = operand1 * operand2;
                else if (token == "/") {
                    if (operand2 == 0) {
                        cout << "Ошибка: деление на ноль!" << endl;
                        delete operand1Node;
                        delete operand2Node;
                        return 0;
                    }
                    result = operand1 / operand2;
                }
                pushNumber(&stack, result);
                delete operand1Node;
                delete operand2Node; // Освобождаем память
            }
        }

        if (end >= expression.length()) {
            break;
        }
    }

    int finalResult = pop(&stack)->number;
    delete stack.head; // Освобождаем память
    return finalResult;
}

int main() {
    string infixExpression;

    cout << "Введите выражение: ";
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Постфиксное выражение: " << postfixExpression << endl;

    int result = evaluatePostfix(postfixExpression);
    cout << "Результат: " << result << endl;

    return 0;
}
