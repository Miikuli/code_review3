/*
Напишите генератор паролей. Составьте три уровня сложности генерации паролей (вместе
с их длиной) и спрашивайте у пользователя, какой уровень сложности ему нужен. Проявите свою
изобретательность: надёжные пароли должны состоять из сочетания строчных букв, прописных
букв, цифр и символов. Пароли должны генерироваться случайным образом каждый раз, когда
пользователь запрашивает новый пароль.
*/

#include "generator.h"
#include <cstdlib>
#include <algorithm>

char GetRandomChar(const std::string& charset) {
    return charset[rand() % charset.size()];
}

void ShuffleString(std::string& str) {
    std::random_shuffle(str.begin(), str.end());
}

std::string GeneratePassword(int length, const std::vector<std::string>& charsets) {
    std::string password;
    for (size_t i = 0; i < charsets.size(); ++i) {
        password += GetRandomChar(charsets[i]);
    }

    std::string allChars;
    for (size_t i = 0; i < charsets.size(); ++i) {
        allChars += charsets[i];
    }

    for (int i = static_cast<int>(charsets.size()); i < length; ++i) {
        password += GetRandomChar(allChars);
    }

    ShuffleString(password);
    return password;
}
