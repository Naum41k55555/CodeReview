/*
Дан текстовый файл, в первой строке которого хранится число N, а во второй
строке N целых чисел. Необходимо создать упорядоченный по убыванию список, в который
поместить все эти элементы, при этом очередной элемент вставлять в список так, чтобы не
нарушалась его упорядоченность.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <string>
#include <iostream>
#include <fstream>

/**
 * @struct Node
 * @brief Узел связного списка
 */
struct Node {
    int data;       ///< Целочисленное значение узла
    Node* next;     ///< Указатель на следующий узел

    /**
     * @brief Конструктор узла
     * @param value Значение для узла
     */
    explicit Node(int value) : data(value), next(nullptr) {}
};

/**
 * @class LinkedList
 * @brief Класс упорядоченного списка (по убыванию)
 */
class LinkedList {
public:
    /**
     * @brief Конструктор по умолчанию
     */
    LinkedList();
    
    /**
     * @brief Деструктор
     */
    ~LinkedList();
    
    /**
     * @brief Вставка элемента с сохранением порядка
     * @param value Значение для вставки
     */
    void InsertSorted(int value);
    
    /**
     * @brief Удаление элемента по значению
     * @param value Значение для удаления
     * @return true если элемент был найден и удалён, false иначе
     */
    bool DeleteValue(int value);
    
    /**
     * @brief Вывод списка в консоль
     */
    void Print() const;
    
    /**
     * @brief Проверка на пустоту списка
     * @return true если список пуст, false иначе
     */
    bool IsEmpty() const;
    
    /**
     * @brief Очистка списка
     */
    void Clear();
    
    /**
     * @brief Чтение данных из файла
     * @param filename Имя файла для чтения
     * @return true если файл успешно прочитан, false иначе
     */
    bool ReadFromFile(const std::string& filename);

private:
    Node* head;     ///< Указатель на голову списка
};

#endif // LINKED_LIST_H_
