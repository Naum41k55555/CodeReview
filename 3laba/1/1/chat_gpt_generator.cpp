#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для генерации пароля
string generatePassword(int length, int difficulty) {
    string lowercase = "abcdefghijklmnopqrstuvwxyz";
    string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string digits = "0123456789";
    string symbols = "!@#$%^&*()-_=+<>?";

    string charSet;

    // Формируем набор символов в зависимости от уровня сложности
    switch (difficulty) {
        case 1:
            charSet = lowercase;
            break;
        case 2:
            charSet = lowercase + uppercase + digits;
            break;
        case 3:
            charSet = lowercase + uppercase + digits + symbols;
            break;
        default:
            cout << "Некорректный уровень сложности. Используется простой уровень.\n";
            charSet = lowercase;
            break;
    }

    string password = "";
    for (int i = 0; i < length; i++) {
        int index = rand() % charSet.size();
        password += charSet[index];
    }

    return password;
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int difficulty, length;

    cout << "Выберите уровень сложности пароля:\n";
    cout << "1 - Простой (только строчные буквы)\n";
    cout << "2 - Средний (буквы и цифры)\n";
    cout << "3 - Сложный (буквы, цифры и символы)\n";
    cout << "Введите уровень сложности (1-3): ";
    cin >> difficulty;

    cout << "Введите желаемую длину пароля: ";
    cin >> length;

    if (length <= 0) {
        cout << "Длина пароля должна быть больше 0.\n";
        return 1;
    }

    string password = generatePassword(length, difficulty);
    cout << "Сгенерированный пароль: " << password << endl;

    return 0;
}
