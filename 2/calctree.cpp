/*
В текстовом файле с именем filename дано арифметическое выражение в префиксной
форме. Операндами в выражении являются целые числа из промежутка от 0 до 9. Используемые
операции: сложение(+), вычитание(-), умножение(*), деление нацело(/), целочисленный остаток
от деления(%) и возведение в степень(^). Постройте дерево, соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1), вычитание(-2), умножение(-3), деление(-
4), остаток от деления(-5), возведение в степень (-6). Преобразуйте дерево, вычислив значения
всех поддеревьев, для которых результат вычислений является числом из промежутка от 0 до 9
(замените такие поддеревья их значениями). Выведите указатель на корень полученного дерева
*/

#include "calctree.h"
#include <fstream>
#include <cmath>
#include <cctype>

CalcTree::CalcTree(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        errorFlag = true;
        return;
    }

    std::string expr;
    getline(file, expr);
    file.close();

    ss = std::istringstream(expr);
    root = BuildTree();
}

std::unique_ptr<Node> CalcTree::BuildTree() {
    std::string token;
    if (!(ss >> token)) return nullptr;

    if (token == "+" || token == "-" || token == "*" ||
        token == "/" || token == "%" || token == "^") {
        std::unique_ptr<Node> node(new Node(0));
        if (token == "+") node->value = ADD;
        else if (token == "-") node->value = SUB;
        else if (token == "*") node->value = MUL;
        else if (token == "/") node->value = DIV;
        else if (token == "%") node->value = MOD;
        else if (token == "^") node->value = POW;

        node->left = BuildTree();
        node->right = BuildTree();
        return node;
    }

    bool isNumber = true;
    for (char c : token) {
        if (!std::isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    if (!isNumber) {
        errorFlag = true;
        return std::make_unique<Node>(0);
    }

    int value = std::stoi(token);
    if (value < 0 || value > 9) {
        errorFlag = true;
        value = 0;
    }

    return std::make_unique<Node>(value);
}

bool CalcTree::Evaluate(std::unique_ptr<Node>& node) {
    if (!node || node->value >= 0) return false;

    bool changed = false;
    changed |= Evaluate(node->left);
    changed |= Evaluate(node->right);

    if (node->left && node->right &&
        node->left->value >= 0 && node->right->value >= 0) {
        int result;
        if (Compute(node->left->value, node->right->value,
            static_cast<Operation>(node->value), result)) {
            if (result >= 0 && result <= 9) {
                node = std::make_unique<Node>(result);
                return true;
            }
        }
        else {
            errorFlag = true;
        }
    }
    return changed;
}

bool CalcTree::Compute(int a, int b, Operation op, int& result) const {
    switch (op) {
    case ADD: result = a + b; return true;
    case SUB: result = a - b; return true;
    case MUL: result = a * b; return true;
    case DIV:
        if (b == 0) return false;
        result = a / b;
        return true;
    case MOD:
        if (b == 0) return false;
        result = a % b;
        return true;
    case POW:
        result = static_cast<int>(pow(a, b));
        return true;
    default:
        return false;
    }
}

void CalcTree::Simplify() {
    while (Evaluate(root)) {}
}
