/*
Элементами контейнеров являются целые числа. Для
заполнения контейнера использовать итератор и конструктор соответствующего контейнера,
для вывода элементов использовать итератор (для вывода элементов в обратном порядке
использовать обратные итераторы, возвращаемые функциями-членами rbegin и rend)
Обязательно наличие дружественного интерфейса. Ввод данных организовать 
разными способами (с клавиатуры, рандом, из файла)

Даны вектор V, дек D и список L. Каждый исходный контейнер содержит не менее
двух элементов, количество элементов является четным. Поменять значения двух средних
элементов каждого из исходных контейнеров. Использовать алгоритм swap (не путать его с
одноименной функцией-членом контейнера).
*/

#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iterator>

/**
 * @class ContainerUtils
 * @brief Класс-утилита для работы с контейнерами STL
 * 
 * Предоставляет методы для заполнения, вывода и обработки контейнеров.
 * Поддерживает три типа контейнеров: vector, deque и list.
 */
class ContainerUtils {
public:
    /**
     * @enum InputMethod
     * @brief Методы ввода данных в контейнер
     */
    enum InputMethod { 
        KEYBOARD = 1,   ///< Ввод с клавиатуры
        RANDOM = 2,     ///< Генерация случайных чисел
        FILE_INPUT = 3  ///< Чтение из файла
    };

    /**
     * @brief Заполняет контейнер данными
     * @tparam Container Тип контейнера (vector, deque или list)
     * @param[out] container Контейнер для заполнения
     * @param[in] size Количество элементов (должно быть четным и >= 2)
     * @param[in] method Метод ввода данных (KEYBOARD, RANDOM или FILE_INPUT)
     * @return true при успешном заполнении, false при ошибке
     * 
     * @note При FILE_INPUT данные читаются из файла "input.txt"
     */
    template<typename Container>
    static bool FillContainer(Container& container, size_t size, InputMethod method);

    /**
     * @brief Выводит элементы контейнера
     * @tparam Container Тип контейнера (vector, deque или list)
     * @param[in] container Контейнер для вывода
     */
    template<typename Container>
    static void PrintContainer(const Container& container);

    /**
     * @brief Выводит элементы контейнера в обратном порядке
     * @tparam Container Тип контейнера (vector, deque или list)
     * @param[in] container Контейнер для вывода
     */
    template<typename Container>
    static void PrintReverse(const Container& container);

    /**
     * @brief Меняет местами два средних элемента контейнера
     * @tparam Container Тип контейнера (vector, deque или list)
     * @param[in,out] container Контейнер для обработки
     * @return true при успешном выполнении, false при ошибке
     * 
     * @note Использует алгоритм std::iter_swap для обмена элементов
     */
    template<typename Container>
    static bool SwapMiddleElements(Container& container);
};

#endif // CONTAINERS_H
