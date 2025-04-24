/*
Напишите генератор паролей. Составьте три уровня сложности генерации паролей (вместе
с их длиной) и спрашивайте у пользователя, какой уровень сложности ему нужен. Проявите свою
изобретательность: надёжные пароли должны состоять из сочетания строчных букв, прописных
букв, цифр и символов. Пароли должны генерироваться случайным образом каждый раз, когда
пользователь запрашивает новый пароль.
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "generator.h"

int main() {
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "Выберите уровень сложности пароля:\n"
        << "1. Легкий (8 символов, только строчные буквы)\n"
        << "2. Средний (12 символов, буквы и цифры)\n"
        << "3. Сложный (16 символов, буквы, цифры, спецсимволы)\n"
        << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    int length = 0;
    std::vector<std::string> charsets;

    switch (choice) {
    case 1:
        length = 8;
        charsets.push_back("abcdefghijklmnopqrstuvwxyz");
        break;
    case 2:
        length = 12;
        charsets = {
            "abcdefghijklmnopqrstuvwxyz",
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            "0123456789"
        };
        break;
    case 3:
        length = 16;
        charsets = {
            "abcdefghijklmnopqrstuvwxyz",
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            "0123456789",
            "!@#$%^&*()-_=+[]{}|;:,.<>?"
        };
        break;
    default:
        std::cout << "Ошибка: некорректный выбор\n";
        return 1;
    }

    std::string password = GeneratePassword(length, charsets);
    std::cout << "Сгенерированный пароль: " << password << "\n";

    return 0;
}
