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
#include <sstream>
#include <string>
#include <stack>
#include <cmath>

// Структура для узла дерева
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для создания нового узла
TreeNode* createNode(int value) {
    return new TreeNode(value);
}

// Функция для вычисления значения поддерева
int evaluate(TreeNode* root) {
    if (!root) return 0;
    if (root->value >= 0) return root->value; // Если это лист (операнд)

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->value) {
        case -1: return leftVal + rightVal;
        case -2: return leftVal - rightVal;
        case -3: return leftVal * rightVal;
        case -4: return leftVal / rightVal;
        case -5: return leftVal % rightVal;
        case -6: return static_cast<int>(pow(leftVal, rightVal));
        default: return 0;
    }
}

// Функция для преобразования дерева
TreeNode* transformTree(TreeNode* root) {
    if (!root) return nullptr;

    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    if (root->left && root->right) {
        int result = evaluate(root);
        if (result >= 0 && result <= 9) {
            TreeNode* newNode = createNode(result);
            delete root->left;
            delete root->right;
            delete root;
            return newNode;
        }
    }

    return root;
}

// Функция для построения дерева из префиксного выражения
TreeNode* buildTree(const std::string& expression, int& index) {
    if (index >= expression.size()) return nullptr;

    char token = expression[index];
    index++;

    TreeNode* node;
    if (isdigit(token)) {
        node = createNode(token - '0');
    } else {
        node = createNode(getOperationCode(token));
        node->left = buildTree(expression, index);
        node->right = buildTree(expression, index);
    }

    return node;
}

// Функция для получения кода операции
int getOperationCode(char op) {
    switch (op) {
        case '+': return -1;
        case '-': return -2;
        case '*': return -3;
        case '/': return -4;
        case '%': return -5;
        case '^': return -6;
        default: return 0;
    }
}

// Функция для вывода дерева (для отладки)
void printTree(TreeNode* root) {
    if (!root) return;
    std::cout << root->value << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    std::string filename = "expression.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    std::string expression;
    file >> expression;
    file.close();

    int index = 0;
    TreeNode* root = buildTree(expression, index);

    root = transformTree(root);

    std::cout << "Указатель на корень дерева: " << root << std::endl;
    std::cout << "Дерево: ";
    printTree(root);
    std::cout << std::endl;

    // Освобождение памяти (необязательно для этого примера, но хорошая практика)
    // deleteTree(root);

    return 0;
}
