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
#include <sstream>
using namespace std;

class TNode {
public:
    int data;
    TNode* next;

    TNode(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    TNode* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() { clearStack(); }

    bool isEmpty() const { return top == nullptr; }

    void push(int value) {
        TNode* newNode = new TNode(value);
        newNode->next = top;
        top = newNode;
    }

    bool pop() {
        if (isEmpty()) return false;

        TNode* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    bool peek(int& value) const {
        if (isEmpty()) return false;
        value = top->data;
        return true;
    }

    string toString() const {
        if (isEmpty()) return "Стек пуст!";

        ostringstream oss;
        oss << "Элементы стека: ";

        TNode* current = top;
        while (current != nullptr) {
            oss << current->data << " ";
            current = current->next;
        }

        return oss.str();
    }

    void clearStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    TNode* getTop() const { return top; }

    friend void addElementAndPrintAddress(Stack& stack, int D);
};

void addElementAndPrintAddress(Stack& stack, int D) {
    stack.push(D);
    cout << "Адрес новой вершины стека: " << stack.getTop() << std::endl;
}
