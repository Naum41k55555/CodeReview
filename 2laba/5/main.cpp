// Функция для отображения меню выбора способа ввода данных
// Показывает пользователю доступные варианты заполнения контейнера
void printMenu() {
    std::cout << "\nChoose input method:\n"
              << "1. Keyboard input - ручной ввод чисел с клавиатуры\n"
              << "2. Random generation - автоматическая генерация случайных чисел\n"
              << "3. Read from file - чтение чисел из текстового файла\n"
              << "Your choice (введите цифру 1-3): ";
}

// Основная функция обработки контейнера
// containerName - название типа контейнера ("vector", "deque" или "list")
void processContainer(const std::string& containerName) {
    // Создаем три разных типа контейнеров:
    std::vector<int> vec;  // Вектор - динамический массив с быстрым доступом
    std::deque<int> deq;   // Дек - двусторонняя очередь
    std::list<int> lst;    // Список - двусвязный список

    size_t size;  // Переменная для хранения размера контейнера
    int method;   // Переменная для выбора метода ввода (1-3)

    // Начинаем обработку контейнера
    std::cout << "\n=== Processing " << containerName << " ===";
    
    // Запрашиваем размер контейнера с проверкой:
    while (true) {
        std::cout << "\nEnter size (even >=2): ";
        // Проверяем что введено число, оно >=2 и четное
        if (!(std::cin >> size) || size < 2 || size % 2 != 0) {
            // Если ошибка - очищаем флаги ошибок ввода
            std::cin.clear();
            // Удаляем ошибочные символы из буфера ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid size. Must be even number >= 2\n";
            continue;  // Повторяем запрос
        }
        break;  // Выходим из цикла при корректном вводе
    }

    // Запрашиваем метод ввода данных:
    while (true) {
        printMenu();  // Показываем меню выбора
        if (!(std::cin >> method) || method < 1 || method > 3) {
            // Обработка неверного ввода
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid choice. Please enter number 1-3\n";
            continue;
        }
        break;
    }

    // Заполняем соответствующий контейнер данными:
    bool success = false;  // Флаг успешного заполнения
    
    // Выбираем нужный контейнер по имени
    if (containerName == "vector") {
        // Для вектора вызываем FillContainer с параметрами:
        // vec - контейнер, size - размер, method - способ заполнения
        success = ContainerUtils::FillContainer(vec, size, static_cast<ContainerUtils::InputMethod>(method));
    } 
    else if (containerName == "deque") {
        success = ContainerUtils::FillContainer(deq, size, static_cast<ContainerUtils::InputMethod>(method));
    } 
    else {
        success = ContainerUtils::FillContainer(lst, size, static_cast<ContainerUtils::InputMethod>(method));
    }

    // Проверяем успешность заполнения
    if (!success) {
        std::cerr << "Failed to fill container\n";
        return;  // Выходим при ошибке
    }

    // Выводим информацию о контейнере:
    std::cout << "\n" << containerName << " contents:\n";
    
    // Обрабатываем каждый тип контейнера отдельно
    if (containerName == "vector") {
        // 1. Выводим элементы в прямом порядке
        ContainerUtils::PrintContainer(vec);  
        
        // 2. Выводим элементы в обратном порядке
        std::cout << "Reversed order: ";
        ContainerUtils::PrintReverse(vec);    
        
        // 3. Меняем местами два средних элемента
        ContainerUtils::SwapMiddleElements(vec);  
        
        // 4. Выводим результат после обмена
        std::cout << "After swapping middle elements: ";
        ContainerUtils::PrintContainer(vec);  
    } 
    // Аналогично для дека и списка
    else if (containerName == "deque") {
        ContainerUtils::PrintContainer(deq);
        std::cout << "Reversed order: ";
        ContainerUtils::PrintReverse(deq);
        ContainerUtils::SwapMiddleElements(deq);
        std::cout << "After swapping middle elements: ";
        ContainerUtils::PrintContainer(deq);
    } 
    else {
        ContainerUtils::PrintContainer(lst);
        std::cout << "Reversed order: ";
        ContainerUtils::PrintReverse(lst);
        ContainerUtils::SwapMiddleElements(lst);
        std::cout << "After swapping middle elements: ";
        ContainerUtils::PrintContainer(lst);
    }
}

// Точка входа в программу
int main() {
    // Приветствие
    std::cout << "=== Container Processing Program ===\n";
    std::cout << "This program demonstrates working with three container types:\n";
    std::cout << "- vector (dynamic array)\n";
    std::cout << "- deque (double-ended queue)\n";
    std::cout << "- list (doubly-linked list)\n\n";

    // Обрабатываем все три типа контейнеров последовательно
    std::cout << "===== VECTOR DEMONSTRATION =====\n";
    processContainer("vector");
    
    std::cout << "\n===== DEQUE DEMONSTRATION =====\n";
    processContainer("deque");
    
    std::cout << "\n===== LIST DEMONSTRATION =====\n";
    processContainer("list");

    // Завершение программы
    std::cout << "\nProgram completed successfully.\n";
    return 0;
}
