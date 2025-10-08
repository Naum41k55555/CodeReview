/*Дано число D и указатель P1 на вершину непустого стека. 
Добавить элемент со значением D в стек и вывести адрес P2 новой вершины стека.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.

В заданиях подгруппы структура «стек» (stack) моделируется цепочкой связанных
узлов-записей типа TNode. Поле Next последнего элемента цепочки равно nullptr. Вершиной
стека (top) считается первый элемент цепочки. Для доступа к стеку используется указатель на
его вершину (для пустого стека данный указатель полагается равным nullptr). Значением
элемента стека считается значение его поля Data*/

#include "stack.h"
#include <iostream>

int getValidInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите целое число.\n";
    }
}

void displayMenu() {
    std::cout << "\nМеню:\n"
              << "1. Добавить элемент в стек\n"
              << "2. Удалить элемент из стека\n"
              << "3. Вывести элементы стека\n"
              << "4. Очистить стек\n"
              << "5. Выйти\n";
}

int main() {
    Stack stack;
    
    while (true) {
        displayMenu();
        int choice = getValidInput("Введите ваш выбор: ");
        
        switch (choice) {
            case 1: {
                int value = getValidInput("Введите число для добавления в стек: ");
                addElementAndPrintAddress(stack, value);
                break;
            }
            case 2:
                if (!stack.pop()) {
                    std::cout << "Стек пуст! Удаление невозможно.\n";
                }
                break;
            case 3:
                std::cout << stack.toString() << std::endl;
                break;
            case 4:
                stack.clearStack();
                std::cout << "Стек очищен.\n";
                break;
            case 5:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Неверный выбор! Пожалуйста, попробуйте снова.\n";
        }
    }
}
