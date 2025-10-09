#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

/**
 * @struct Node
 * @brief Узел очереди
 * 
 * Содержит данные и указатель на следующий узел
 */
struct Node {
    int value;      ///< Значение узла
    Node* next;     ///< Указатель на следующий узел
};

/**
 * @class Queue
 * @brief Класс очереди, реализованный на связном списке
 * 
 * Предоставляет стандартные операции работы с очередью: enqueue, dequeue и другие
 */
class Queue {
public:
    /**
     * @brief Конструктор очереди
     */
    Queue();
    
    /**
     * @brief Деструктор очереди
     * 
     * Автоматически очищает память при уничтожении очереди
     */
    ~Queue();
    
    /**
     * @brief Инициализация очереди
     */
    void Initialize();
    
    /**
     * @brief Добавление элемента в конец очереди
     * @param number Значение для добавления
     */
    void Enqueue(int number);
    
    /**
     * @brief Удаление элемента из начала очереди
     */
    void Dequeue();
    
    /**
     * @brief Вывод всех элементов очереди
     */
    void Print();
    
    /**
     * @brief Вывод указателей на начало и конец очереди
     */
    void PrintPointers();

private:
    Node* head;     ///< Указатель на начало очереди
    Node* tail;     ///< Указатель на конец очереди
};

#endif // QUEUE_H
