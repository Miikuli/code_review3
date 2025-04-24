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

// Функция для генерации случайного символа
char getRandomChar(const std::string& charset) {
    return charset[rand() % charset.size()];
}

// Функция для генерации пароля
std::string generatePassword(int length, const std::string& charset) {
    std::string password;
    for (int i = 0; i < length; ++i) {
        password += getRandomChar(charset);
    }
    return password;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // Определение наборов символов для разных уровней сложности
    const std::string easyChars = "abcdefghijklmnopqrstuvwxyz";
    const std::string mediumChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const std::string hardChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?";

    int choice;
    std::cout << "Выберите уровень сложности пароля:\n";
    std::cout << "1. Легкий (8 символов, только строчные буквы)\n";
    std::cout << "2. Средний (12 символов, строчные и прописные буквы, цифры)\n";
    std::cout << "3. Сложный (16 символов, строчные и прописные буквы, цифры, символы)\n";
    std::cout << "Введите ваш выбор (1, 2 или 3): ";
    std::cin >> choice;

    std::string password;
    switch (choice) {
        case 1:
            password = generatePassword(8, easyChars);
            break;
        case 2:
            password = generatePassword(12, mediumChars);
            break;
        case 3:
            password = generatePassword(16, hardChars);
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3.\n";
            return 1;
    }

    std::cout << "Сгенерированный пароль: " << password << std::endl;
    return 0;
}
