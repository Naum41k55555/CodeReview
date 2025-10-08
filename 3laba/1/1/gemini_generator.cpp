/*
Напишите генератор паролей. Составьте три уровня сложности генерации паролей (вместе
с их длиной) и спрашивайте у пользователя, какой уровень сложности ему нужен. Проявите свою
изобретательность: надёжные пароли должны состоять из сочетания строчных букв, прописных
букв, цифр и символов. Пароли должны генерироваться случайным образом каждый раз, когда
пользователь запрашивает новый пароль.
*/

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <limits>

using namespace std;

// Функция для генерации случайного пароля заданной длины и набора символов
string generate_password(int length, const string& char_set) {
    
    //Источник недетерминированных случайных чисел,
    // который обычно использует аппаратные средства (если доступны) для получения
    // случайных значений.
    random_device random_device;
    
    // Mersenne Twister 19937 это один из наиболее распространенных
    // и качественных генераторов псевдослучайных чисел. Мы инициализируем его с помощью
    // значения, полученного от random_device. Это гарантирует, что каждая новая
    // инициализация генератора будет начинаться с действительно случайного "зерна",
    // что делает последовательность случайных чисел менее предсказуемой.
    mt19937 generator(random_device());

    // Создаем объект uniform_int_distribution. Это распределение позволяет нам получать
    // случайные целые числа, равномерно распределенные в заданном диапазоне.
    // В данном случае диапазон от 0 (индекс первого символа в char_set) до
    // char_set.length() - 1 (индекс последнего символа в char_set). Это нужно для того,
    // чтобы случайным образом выбирать индекс символа из строки char_set.
    uniform_int_distribution<> distribution(0, char_set.length() - 1);

    string password = "";
    for (int i = 0; i < length; ++i) {
        password += char_set[distribution(generator)];
    }
    return password;
}

int main() {
    int complexity;
    int length;

    cout << "Выберите уровень сложности пароля:" << endl;
    cout << "1. Легкий (только строчные буквы)" << endl;
    cout << "2. Средний (строчные и прописные буквы, цифры)" << endl;
    cout << "3. Сложный (строчные и прописные буквы, цифры, символы)" << endl;

    // Проверка ввода уровня сложности
    while (!(cin >> complexity) || complexity < 1 || complexity > 3) {
        cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 3." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите желаемую длину пароля: ";

    // Проверка ввода длины пароля
    while (!(cin >> length) || length <= 0) {
        cout << "Некорректный ввод. Пожалуйста, введите положительное число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string char_set;
    switch (complexity) {
        case 1:
            char_set = "abcdefghijklmnopqrstuvwxyz";
            break;
        case 2:
            char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            break;
        case 3:
            char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+=-`~[]\\{}|;':\",./<>?";
            break;
    }

    string password = generate_password(length, char_set);
    cout << "Сгенерированный пароль: " << password << endl;

    return 0;
}
