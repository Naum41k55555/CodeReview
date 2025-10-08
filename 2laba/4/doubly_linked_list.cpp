#include "doubly_linked_list.h"
#include <iostream>

/**
 * @brief Конструктор по умолчанию
 */
DoublyLinkedList::DoublyLinkedList() : head(nullptr) {}

/**
 * @brief Деструктор
 */
DoublyLinkedList::~DoublyLinkedList() {
    Clear();
}

/**
 * @brief Добавляет элемент в конец списка
 * @param value Значение для добавления
 */
void DoublyLinkedList::Append(int value) {
    Node* newNode = new Node{value, nullptr, nullptr};

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

/**
 * @brief Выводит элементы списка
 */
void DoublyLinkedList::Print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * @brief Находит минимальный и максимальный элементы
 * @param[out] min Указатель на минимальный элемент
 * @param[out] max Указатель на максимальный элемент
 */
void DoublyLinkedList::FindMinMax(Node*& min, Node*& max) const {
    if (head == nullptr) return;

    min = max = head;
    Node* current = head->next;

    while (current != nullptr) {
        if (current->value < min->value) min = current;
        if (current->value > max->value) max = current;
        current = current->next;
    }
}

/**
 * @brief Проверяет порядок элементов
 * @param first Первый элемент
 * @param second Второй элемент
 * @return true если first встречается раньше second
 */
bool DoublyLinkedList::IsFirstBeforeSecond(Node* first, Node* second) const {
    Node* current = head;
    while (current != nullptr) {
        if (current == first) return true;
        if (current == second) return false;
        current = current->next;
    }
    return false;
}

/**
 * @brief Выводит элементы между минимальным и максимальным
 */
void DoublyLinkedList::PrintBetweenMinMax() const {
    Node* min = nullptr;
    Node* max = nullptr;
    FindMinMax(min, max);

    if (min == nullptr || max == nullptr || min == max) {
        std::cout << "Нет элементов для вывода!" << std::endl;
        return;
    }

    bool minFirst = IsFirstBeforeSecond(min, max);
    Node* start = minFirst ? min : max;
    Node* end = minFirst ? max : min;

    std::cout << "Элементы между " << min->value << " и " << max->value << ": ";
    Node* current = start->next;
    bool hasElements = false;

    while (current != nullptr && current != end) {
        std::cout << current->value << " ";
        hasElements = true;
        current = current->next;
    }

    if (!hasElements) std::cout << "Отсутствуют";
    std::cout << std::endl;
}

/**
 * @brief Очищает список
 */
void DoublyLinkedList::Clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

/**
 * @brief Дружественная функция для демонстрации
 */
void DemonstrateDoublyLinkedList() {
    DoublyLinkedList list;
    int size, value;

    std::cout << "Введите количество элементов (не менее 2): ";
    std::cin >> size;

    if (size < 2) {
        std::cerr << "Недостаточно элементов!" << std::endl;
        return;
    }

    std::cout << "Введите " << size << " уникальных целых чисел:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> value;
        list.Append(value);
    }

    std::cout << "\nСписок: ";
    list.Print();

    std::cout << "\nЭлементы между минимальным и максимальным:\n";
    list.PrintBetweenMinMax();
}
