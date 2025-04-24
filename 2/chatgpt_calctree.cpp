#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

// Обозначения операций
enum Operator {
    ADD = -1,
    SUB = -2,
    MUL = -3,
    DIV = -4,
    MOD = -5,
    POW = -6
};

// Узел дерева
struct Node {
    int value; // если операция, то отрицательное значение, если число — от 0 до 9
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int v) : value(v) {}
};

// Проверка — операция ли
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" ||
           token == "/" || token == "%" || token == "^";
}

// Преобразование токена в значение
int tokenToValue(const string& token) {
    if (token == "+") return ADD;
    if (token == "-") return SUB;
    if (token == "*") return MUL;
    if (token == "/") return DIV;
    if (token == "%") return MOD;
    if (token == "^") return POW;
    return stoi(token); // число
}

// Построение дерева из префиксного выражения
Node* buildTree(istringstream& ss) {
    string token;
    if (!(ss >> token)) return nullptr;

    int val = tokenToValue(token);
    Node* node = new Node(val);

    if (val < 0) { // операция
        node->left = buildTree(ss);
        node->right = buildTree(ss);
    }

    return node;
}

// Вычисление значения поддерева, если возможно
bool evaluate(Node*& node) {
    if (!node || node->value >= 0) return true;

    bool leftEval = evaluate(node->left);
    bool rightEval = evaluate(node->right);

    if (leftEval && rightEval && node->left && node->right &&
        node->left->value >= 0 && node->right->value >= 0) {

        int a = node->left->value;
        int b = node->right->value;
        int result = 0;

        switch (node->value) {
            case ADD: result = a + b; break;
            case SUB: result = a - b; break;
            case MUL: result = a * b; break;
            case DIV: if (b == 0) return false; result = a / b; break;
            case MOD: if (b == 0) return false; result = a % b; break;
            case POW: result = pow(a, b); break;
        }

        if (result >= 0 && result <= 9) {
            delete node->left;
            delete node->right;
            node->left = node->right = nullptr;
            node->value = result;
        }

    }

    return true;
}

// Отладочный вывод дерева
void printTree(Node* node, int indent = 0) {
    if (!node) return;

    if (node->right) printTree(node->right, indent + 4);

    if (indent) cout << string(indent, ' ');
    if (node->value < 0)
        cout << "[" << node->value << "]\n";
    else
        cout << node->value << "\n";

    if (node->left) printTree(node->left, indent + 4);
}

// Очистка дерева
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    ifstream file("filename");
    if (!file) {
        cerr << "Не удалось открыть файл!\n";
        return 1;
    }

    string expression;
    getline(file, expression);
    istringstream ss(expression);

    Node* root = buildTree(ss);

    evaluate(root);

    cout << "Дерево после упрощения:\n";
    printTree(root);

    cout << "\nУказатель на корень дерева: " << root << endl;

    deleteTree(root);
    return 0;
}
