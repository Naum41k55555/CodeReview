#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Функция для генерации пароля заданной сложности и длины
string generatePassword(int complexity, int length) {
    // Наборы символов для разных уровней сложности
    const string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    string charSet;
    vector<string> requiredSets;
    
    // Определяем набор символов в зависимости от сложности
    switch (complexity) {
        case 1: // Простой - только строчные буквы
            charSet = lowercase;
            requiredSets = {lowercase};
            break;
        case 2: // Средний - буквы (строчные и прописные) и цифры
            charSet = lowercase + uppercase + digits;
            requiredSets = {lowercase, uppercase, digits};
            break;
        case 3: // Сложный - все возможные символы
            charSet = lowercase + uppercase + digits + symbols;
            requiredSets = {lowercase, uppercase, digits, symbols};
            break;
        default:
            throw invalid_argument("Неверный уровень сложности");
    }
    
    // Инициализация генератора случайных чисел
    srand(time(0));
    
    string password;
    bool meetsRequirements;
    
    // Генерируем пароль, пока он не будет соответствовать требованиям
    do {
        password.clear();
        for (int i = 0; i < length; ++i) {
            password += charSet[rand() % charSet.size()];
        }
        
        // Проверяем, содержит ли пароль хотя бы один символ из каждого обязательного набора
        meetsRequirements = true;
        for (const auto& set : requiredSets) {
            bool containsCharFromSet = false;
            for (char c : set) {
                if (password.find(c) != string::npos) {
                    containsCharFromSet = true;
                    break;
                }
            }
            if (!containsCharFromSet) {
                meetsRequirements = false;
                break;
            }
        }
    } while (!meetsRequirements);
    
    return password;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "Генератор паролей" << endl;
    cout << "=================" << endl << endl;
    
    // Выбор уровня сложности
    int complexity;
    cout << "Выберите уровень сложности пароля:" << endl;
    cout << "1. Простой (только строчные буквы)" << endl;
    cout << "2. Средний (строчные, прописные буквы и цифры)" << endl;
    cout << "3. Сложный (строчные, прописные буквы, цифры и специальные символы)" << endl;
    cout << "Ваш выбор (1-3): ";
    cin >> complexity;
    
    if (complexity < 1 || complexity > 3) {
        cout << "Неверный выбор сложности!" << endl;
        return 1;
    }
    
    // Ввод длины пароля
    int length;
    cout << "Введите длину пароля: ";
    cin >> length;
    
    if (length < 1) {
        cout << "Длина пароля должна быть положительным числом!" << endl;
        return 1;
    }
    
    // Генерация и вывод пароля
    string password = generatePassword(complexity, length);
    cout << endl << "Ваш пароль: " << password << endl;
    
    return 0;
}
