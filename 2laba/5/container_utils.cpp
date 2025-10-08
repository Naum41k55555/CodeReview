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

#include "containers.h"
#include <limits> // Для использования numeric_limits

/*
 * Функция заполнения контейнера данными
 * Параметры:
 *   Container& container - ссылка на контейнер (vector, deque или list)
 *   size_t size - требуемый размер контейнера
 *   InputMethod method - способ заполнения (1-клавиатура, 2-рандом, 3-файл)
 * Возвращает:
 *   bool - true при успешном заполнении, false при ошибке
 */
template<typename Container>
bool ContainerUtils::FillContainer(Container& container, size_t size, InputMethod method) {
    // Очищаем контейнер перед заполнением
    container.clear();

    // Проверка корректности размера:
    // - должен быть четным числом (size % 2 == 0)
    // - должен быть не меньше 2
    if (size < 2 || size % 2 != 0) {
        std::cerr << "Error: Size must be even and >= 2\n";
        return false;
    }

    // Блок try-catch для обработки возможных исключений
    try {
        // Выбор способа заполнения контейнера
        switch (method) {
            case KEYBOARD: {  // 1. Ручной ввод с клавиатуры
                std::cout << "Enter " << size << " integer elements:\n";
                
                // Цикл ввода каждого элемента
                for (size_t i = 0; i < size; ++i) {
                    int value; // Переменная для хранения вводимого числа
                    
                    // Защита от некорректного ввода:
                    // Цикл продолжается пока не будет введено целое число
                    while (!(std::cin >> value)) {
                        // Сброс флагов ошибок ввода
                        std::cin.clear();
                        // Очистка буфера ввода до конца строки
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cerr << "Invalid input. Please enter an integer: ";
                    }
                    // Вставка числа в конец контейнера
                    container.insert(container.end(), value);
                }
                break;
            }
            case RANDOM: {  // 2. Автоматическая генерация случайных чисел
                // Инициализация генератора случайных чисел
                std::srand(static_cast<unsigned>(std::time(nullptr)));
                
                // Генерация size случайных чисел в диапазоне 0-99:
                // - std::back_inserter создает итератор для вставки в конец
                // - Лямбда-функция генерирует случайное число
                std::generate_n(std::back_inserter(container), size, []() {
                    return std::rand() % 100;
                });
                std::cout << "Generated " << size << " random elements\n";
                break;
            }
            case FILE_INPUT: {  // 3. Чтение данных из файла
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;

                // Открытие файла для чтения
                std::ifstream file(filename);
                if (!file.is_open()) {
                    std::cerr << "Error: Cannot open file " << filename << "\n";
                    return false;
                }

                int value;      // Переменная для хранения читаемых чисел
                size_t count = 0; // Счетчик прочитанных элементов
                
                // Чтение чисел из файла:
                // - Читаем пока не достигнем нужного количества или конца файла
                while (file >> value && count < size) {
                    container.insert(container.end(), value);
                    count++;
                }

                // Проверка что прочитали достаточно чисел
                if (count < size) {
                    std::cerr << "Error: File contains only " << count << " elements\n";
                    container.clear();
                    return false;
                }
                break;
            }
            default:  // Обработка неверного выбора метода
                std::cerr << "Error: Invalid input method\n";
                return false;
        }
        return true;  // Успешное завершение
    } 
    catch (...) {  // Перехват любых исключений
        std::cerr << "Error: Exception occurred during container filling\n";
        return false;
    }
}

/*
 * Функция вывода элементов контейнера в прямом порядке
 * Параметры:
 *   const Container& container - контейнер для вывода
 */
template<typename Container>
void ContainerUtils::PrintContainer(const Container& container) {
    // Использование алгоритма std::copy для вывода:
    // - container.begin()/end() - итераторы начала и конца
    // - ostream_iterator - адаптер для вывода в поток cout
    std::copy(container.begin(), container.end(), 
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";  // Переход на новую строку
}

/*
 * Функция вывода элементов в обратном порядке
 * Параметры:
 *   const Container& container - контейнер для вывода
 */
template<typename Container>
void ContainerUtils::PrintReverse(const Container& container) {
    // Использование обратных итераторов rbegin()/rend()
    std::copy(container.rbegin(), container.rend(), 
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

/*
 * Функция обмена двух средних элементов контейнера
 * Параметры:
 *   Container& container - контейнер для обработки
 * Возвращает:
 *   bool - true при успехе, false при ошибке
 */
template<typename Container>
bool ContainerUtils::SwapMiddleElements(Container& container) {
    // Проверка корректности размера контейнера
    if (container.size() < 2 || container.size() % 2 != 0) {
        std::cerr << "Error: Container size must be even and >= 2\n";
        return false;
    }

    try {
        // Создаем итератор на начало контейнера
        typename Container::iterator mid1 = container.begin();
        
        // Перемещаем итератор на первый средний элемент:
        // Для контейнера из 4 элементов это будет позиция 1 (индексация с 0)
        std::advance(mid1, container.size()/2 - 1);
        
        // Создаем второй итератор, указывающий на следующий элемент
        typename Container::iterator mid2 = mid1;
        std::advance(mid2, 1);
        
        // Обмен значений элементов через итераторы
        std::iter_swap(mid1, mid2);
        return true;
    } 
    catch (...) {  // Перехват исключений
        std::cerr << "Error: Exception during swap operation\n";
        return false;
    }
}

// Явные инстанциации шаблонов для поддержки раздельной компиляции:

// Для функции FillContainer с разными типами контейнеров:
template bool ContainerUtils::FillContainer(std::vector<int>&, size_t, InputMethod);
template bool ContainerUtils::FillContainer(std::deque<int>&, size_t, InputMethod);
template bool ContainerUtils::FillContainer(std::list<int>&, size_t, InputMethod);

// Для функции PrintContainer:
template void ContainerUtils::PrintContainer(const std::vector<int>&);
template void ContainerUtils::PrintContainer(const std::deque<int>&);
template void ContainerUtils::PrintContainer(const std::list<int>&);

// Для функции PrintReverse:
template void ContainerUtils::PrintReverse(const std::vector<int>&);
template void ContainerUtils::PrintReverse(const std::deque<int>&);
template void ContainerUtils::PrintReverse(const std::list<int>&);

// Для функции SwapMiddleElements:
template bool ContainerUtils::SwapMiddleElements(std::vector<int>&);
template bool ContainerUtils::SwapMiddleElements(std::deque<int>&);
template bool ContainerUtils::SwapMiddleElements(std::list<int>&);
