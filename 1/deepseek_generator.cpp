/*
Напишите генератор паролей. Составьте три уровня сложности генерации паролей (вместе
с их длиной) и спрашивайте у пользователя, какой уровень сложности ему нужен. Проявите свою
изобретательность: надёжные пароли должны состоять из сочетания строчных букв, прописных
букв, цифр и символов. Пароли должны генерироваться случайным образом каждый раз, когда
пользователь запрашивает новый пароль.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Функция для получения случайного символа из заданного набора
char getRandomChar(const string& charset) {
    return charset[rand() % charset.size()];
}

// Генерация пароля в зависимости от уровня сложности
string generatePassword(int level) {
    string password;
    string lowercase = "abcdefghijklmnopqrstuvwxyz";
    string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numbers = "0123456789";
    string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    string charset;
    int length;

    switch (level) {
        case 1: // Лёгкий
            charset = lowercase;
            length = 8;
            break;
        case 2: // Средний
            charset = lowercase + uppercase + numbers;
            length = 12;
            break;
        case 3: // Сложный
            charset = lowercase + uppercase + numbers + symbols;
            length = 16;
            break;
        default:
            return "Неверный уровень сложности!";
    }

    for (int i = 0; i < length; ++i) {
        password += getRandomChar(charset);
    }

    return password;
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    cout << "Выберите уровень сложности пароля:\n";
    cout << "1. Лёгкий (8 символов, только строчные буквы)\n";
    cout << "2. Средний (12 символов, буквы + цифры)\n";
    cout << "3. Сложный (16 символов, буквы + цифры + спецсимволы)\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    string password = generatePassword(choice);
    cout << "Ваш пароль: " << password << endl;

    return 0;
}
