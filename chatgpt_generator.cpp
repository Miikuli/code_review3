/*
Напишите генератор паролей. Составьте три уровня сложности генерации паролей (вместе
с их длиной) и спрашивайте у пользователя, какой уровень сложности ему нужен. Проявите свою
изобретательность: надёжные пароли должны состоять из сочетания строчных букв, прописных
букв, цифр и символов. Пароли должны генерироваться случайным образом каждый раз, когда
пользователь запрашивает новый пароль.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция генерации случайного пароля
string generatePassword(int length, const string& chars) {
    string password;
    for (int i = 0; i < length; ++i) {
        password += chars[rand() % chars.size()];
    }
    return password;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    int choice;
    cout << "Выберите уровень сложности пароля:\n";
    cout << "1 - Легкий (6 символов, только строчные буквы)\n";
    cout << "2 - Средний (10 символов, буквы и цифры)\n";
    cout << "3 - Сложный (15 символов, буквы, цифры и символы)\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    int length;
    string chars;

    switch (choice) {
        case 1:
            length = 6;
            chars = "abcdefghijklmnopqrstuvwxyz";
            break;
        case 2:
            length = 10;
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            break;
        case 3:
            length = 15;
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            return 1;
    }

    string password = generatePassword(length, chars);
    cout << "Сгенерированный пароль: " << password << endl;

    return 0;
}
