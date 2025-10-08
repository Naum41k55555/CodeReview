/*Дан текстовый файл, в первой строке которого хранится число N, а во второй
строке N целых чисел. Необходимо создать упорядоченный по убыванию список, в который
поместить все эти элементы, при этом очередной элемент вставлять в список так, чтобы не
нарушалась его упорядоченность.

Для каждой динамической структуры должен быть предусмотрен стандартный набор методов - 
добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.
*/

#include "linked_list.h"

/**
 * @brief Конструктор по умолчанию
 */
LinkedList::LinkedList() : head(nullptr) {}

/**
 * @brief Деструктор
 */
LinkedList::~LinkedList() {
    Clear();
}

/**
 * @brief Вставка элемента с сохранением упорядоченности (по убыванию)
 * @param value Значение для вставки
 */
void LinkedList::InsertSorted(int value) {
    Node* newNode = new Node(value);
    
    // Вставка в начало или если новый элемент больше головы
    if (head == nullptr || value > head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Поиск места для вставки
    Node* current = head;
    while (current->next != nullptr && current->next->data > value) {
        current = current->next;
    }
    
    // Вставка нового узла
    newNode->next = current->next;
    current->next = newNode;
}

/**
 * @brief Удаление элемента по значению
 * @param value Значение для удаления
 * @return true если элемент найден и удален, false если не найден
 */
bool LinkedList::DeleteValue(int value) {
    if (IsEmpty()) return false;

    // Удаление из головы
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Поиск элемента для удаления
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    // Если элемент не найден
    if (current->next == nullptr) return false;

    // Удаление узла
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

/**
 * @brief Вывод содержимого списка
 */
void LinkedList::Print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * @brief Проверка на пустоту
 * @return true если список пуст, false если содержит элементы
 */
bool LinkedList::IsEmpty() const {
    return head == nullptr;
}

/**
 * @brief Очистка списка
 */
void LinkedList::Clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

/**
 * @brief Чтение данных из файла
 * @param filename Имя файла для чтения
 * @return true если чтение успешно, false при ошибке
 */
bool LinkedList::ReadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }

    int N;
    file >> N;
    if (N <= 0) {
        std::cerr << "Некорректное количество элементов: " << N << std::endl;
        return false;
    }

    Clear(); // Очищаем существующий список

    int value;
    for (int i = 0; i < N; ++i) {
        if (!(file >> value)) {
            std::cerr << "Ошибка чтения данных" << std::endl;
            Clear();
            return false;
        }
        InsertSorted(value); // Вставляем с сохранением порядка
    }

    file.close();
    return true;
}

/**
 * @brief Дружественная функция для чтения из файла
 * @param list Список для заполнения
 * @param filename Имя файла для чтения
 */
bool ReadFromFile(LinkedList& list, const std::string& filename) {
    return list.ReadFromFile(filename);
}
