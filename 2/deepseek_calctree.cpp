/*
В текстовом файле с именем filename дано арифметическое выражение в префиксной
форме. Операндами в выражении являются целые числа из промежутка от 0 до 9. Используемые
операции: сложение(+), вычитание(-), умножение(*), деление нацело(/), целочисленный остаток
от деления(%) и возведение в степень(^). Постройте дерево, соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1), вычитание(-2), умножение(-3), деление(-
4), остаток от деления(-5), возведение в степень (-6). Преобразуйте дерево, вычислив значения
всех поддеревьев, для которых результат вычислений является числом из промежутка от 0 до 9
(замените такие поддеревья их значениями). Выведите указатель на корень полученного дерева
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <cmath> // для pow()

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Функция для проверки, является ли токен оператором
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
}

// Преобразование оператора в числовой код
int opToCode(const string& op) {
    if (op == "+") return -1;
    if (op == "-") return -2;
    if (op == "*") return -3;
    if (op == "/") return -4;
    if (op == "%") return -5;
    if (op == "^") return -6;
    return 0; // Не должно случиться
}

// Построение дерева из префиксного выражения
TreeNode* buildTree(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) return nullptr;

    string token = tokens[index++];
    TreeNode* node;

    if (isOperator(token)) {
        node = new TreeNode(opToCode(token));
        node->left = buildTree(tokens, index);
        node->right = buildTree(tokens, index);
    } else {
        node = new TreeNode(stoi(token));
    }

    return node;
}

// Вычисление значения поддерева
int computeSubtree(TreeNode* node) {
    if (!node) return 0;

    // Если это лист (число), возвращаем его
    if (node->val >= 0) return node->val;

    // Рекурсивно вычисляем левое и правое поддеревья
    int leftVal = computeSubtree(node->left);
    int rightVal = computeSubtree(node->right);

    // Выполняем операцию
    switch (node->val) {
        case -1: return leftVal + rightVal;
        case -2: return leftVal - rightVal;
        case -3: return leftVal * rightVal;
        case -4: return leftVal / rightVal; // Целочисленное деление
        case -5: return leftVal % rightVal;
        case -6: return pow(leftVal, rightVal);
        default: return 0;
    }
}

// Оптимизация дерева (замена вычисляемых поддеревьев)
TreeNode* optimizeTree(TreeNode* root) {
    if (!root) return nullptr;

    // Если это лист, возвращаем его
    if (root->val >= 0) return root;

    // Рекурсивно оптимизируем поддеревья
    root->left = optimizeTree(root->left);
    root->right = optimizeTree(root->right);

    // Проверяем, можно ли вычислить текущее поддерево
    int result = computeSubtree(root);
    if (result >= 0 && result <= 9) {
        delete root->left;
        delete root->right;
        return new TreeNode(result);
    }

    return root;
}

// Чтение выражения из файла
vector<string> readExpression(const string& filename) {
    ifstream file(filename);
    vector<string> tokens;
    string token;

    while (file >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// Вывод дерева (для отладки)
void printTree(TreeNode* root, int depth = 0) {
    if (!root) return;

    printTree(root->right, depth + 1);
    cout << string(depth * 4, ' ') << root->val << endl;
    printTree(root->left, depth + 1);
}

int main() {
    string filename = "expression.txt"; // Пример: "^ + 3 4 2" → (3 + 4)^2 = 49 → не заменяем (49 > 9)
    vector<string> tokens = readExpression(filename);
    int index = 0;

    TreeNode* root = buildTree(tokens, index);
    cout << "Исходное дерево:" << endl;
    printTree(root);

    root = optimizeTree(root);
    cout << "\nОптимизированное дерево:" << endl;
    printTree(root);

    return 0;
}
