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

Node::Node(int value) : data(value), next(nullptr) {}

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    ClearStack();
}

void Stack::Push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    std::cout << "Элемент " << value << " добавлен в стек." << std::endl;
}

void Stack::Pop() {
    if (top == nullptr) {
        std::cout << "Стек пуст! Невозможно удалить элемент." << std::endl;
        return;
    }
    Node* temp = top;
    top = top->next;
    std::cout << "Элемент " << temp->data << " удален из стека." << std::endl;
    delete temp;
}

void Stack::Print() {
    if (top == nullptr) {
        std::cout << "Стек пуст!" << std::endl;
        return;
    }
    Node* current = top;
    std::cout << "Элементы стека: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

Node* Stack::GetTop() {
    return top;
}

void Stack::ClearStack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    std::cout << "Стек очищен." << std::endl;
}

void AddElementAndPrintAddress(Stack& stack, int D) {
    stack.Push(D);
    std::cout << "Адрес новой вершины стека: " << stack.GetTop() << std::endl;
}
