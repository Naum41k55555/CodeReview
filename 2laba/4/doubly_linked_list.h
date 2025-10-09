#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

/**
 * @struct Node
 * @brief Узел двусвязного списка
 */
struct Node {
    int value;          ///< Значение узла
    Node* prev;         ///< Указатель на предыдущий узел
    Node* next;         ///< Указатель на следующий узел
};

/**
 * @class DoublyLinkedList
 * @brief Класс двусвязного списка
 */
class DoublyLinkedList {
public:
    /**
     * @brief Конструктор по умолчанию
     */
    DoublyLinkedList();
    
    /**
     * @brief Деструктор
     */
    ~DoublyLinkedList();
    
    /**
     * @brief Добавление элемента в конец списка
     * @param value Значение для добавления
     */
    void Append(int value);
    
    /**
     * @brief Вывод всех элементов списка
     */
    void Print() const;
    
    /**
     * @brief Поиск минимального и максимального элементов
     * @param[out] min Указатель на минимальный элемент
     * @param[out] max Указатель на максимальный элемент
     */
    void FindMinMax(Node*& min, Node*& max) const;
    
    /**
     * @brief Проверка порядка элементов
     * @param first Первый элемент
     * @param second Второй элемент
     * @return true если first встречается раньше second
     */
    bool IsFirstBeforeSecond(Node* first, Node* second) const;
    
    /**
     * @brief Вывод элементов между минимальным и максимальным
     */
    void PrintBetweenMinMax() const;
    
    /**
     * @brief Очистка списка
     */
    void Clear();

private:
    Node* head;         ///< Указатель на первый элемент списка
};

#endif // DOUBLY_LINKED_LIST_H
