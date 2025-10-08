/* Дан двусвязный линейный список и указатель первый элемент этого 
списка. Все элементы списка хранят различные между собой значения. Необходимо 
вывести значения элементов списка, которые находятся между наименьшим и 
наибольшим элементами списка, в том порядке, в каком они находятся в исходном 
списке. Использовать процедуры. 

Все динамические структуры данных реализовывать через классы. Не использовать STL.  
Для каждой динамической структуры должен быть предусмотрен
стандартный набор методов - добавления/удаления/вывода элементов. 
Во всех задачах обязательно наличие дружественного интерфейса. Ввод данных с клавиатуры.*/

#include <iostream>
using namespace std;

// Структура узла двусвязного списка
struct Uzel {
    int Znachenie;         // Значение узла
    Uzel* Predydushiy;      // Указатель на предыдущий узел
    Uzel* Sleduyushiy;      // Указатель на следующий узел
};

// Класс для работы с двусвязным списком
class Spisok {
private:
    Uzel* PerviyElement;    // Указатель на первый элемент списка

public:
    // Инициализация списка
    void Initsializatsiya() {
        PerviyElement = nullptr;
    }

    // Очистка списка
    void Ochistka() {
        Uzel* Tekushiy = PerviyElement;
        while (Tekushiy != nullptr) {
            Uzel* Vremenniy = Tekushiy;
            Tekushiy = Tekushiy->Sleduyushiy;
            delete Vremenniy;
        }
        PerviyElement = nullptr;
    }

    // Добавление элемента в конец списка
    void DobavitElement(int Znachenie) {
        Uzel* Noviy = new Uzel;
        Noviy->Znachenie = Znachenie;
        Noviy->Predydushiy = nullptr;
        Noviy->Sleduyushiy = nullptr;

        if (PerviyElement == nullptr) {
            PerviyElement = Noviy;
        }
        else {
            Uzel* Tekushiy = PerviyElement;
            while (Tekushiy->Sleduyushiy != nullptr) {
                Tekushiy = Tekushiy->Sleduyushiy;
            }
            Tekushiy->Sleduyushiy = Noviy;
            Noviy->Predydushiy = Tekushiy;
        }
    }

    // Вывод всех элементов списка
    void VivodSpiska() {
        Uzel* Tekushiy = PerviyElement;
        while (Tekushiy != nullptr) {
            cout << Tekushiy->Znachenie << " ";
            Tekushiy = Tekushiy->Sleduyushiy;
        }
        cout << endl;
    }

    // Поиск минимального и максимального элементов
    void PoiskMinMax(Uzel*& Min, Uzel*& Max) {
        if (PerviyElement == nullptr) return;

        Min = Max = PerviyElement;
        Uzel* Tekushiy = PerviyElement->Sleduyushiy;

        while (Tekushiy != nullptr) {
            if (Tekushiy->Znachenie < Min->Znachenie) Min = Tekushiy;
            if (Tekushiy->Znachenie > Max->Znachenie) Max = Tekushiy;
            Tekushiy = Tekushiy->Sleduyushiy;
        }
    }

    // Проверка, какой элемент встречается раньше
    bool ProverkaPoryadka(Uzel* A, Uzel* B) {
        Uzel* Tekushiy = PerviyElement;
        while (Tekushiy != nullptr) {
            if (Tekushiy == A) return true;
            if (Tekushiy == B) return false;
            Tekushiy = Tekushiy->Sleduyushiy;
        }
        return false;
    }

    // Вывод элементов между минимальным и максимальным
    void VivodMezhduMinMax() {
        Uzel* Min = nullptr;
        Uzel* Max = nullptr;
        PoiskMinMax(Min, Max);

        if (Min == nullptr || Max == nullptr || Min == Max) {
            cout << "Нет элементов для вывода!" << endl;
            return;
        }

        bool MinPerviy = ProverkaPoryadka(Min, Max);
        Uzel* Start = MinPerviy ? Min : Max;
        Uzel* End = MinPerviy ? Max : Min;

        cout << "Элементы между " << Min->Znachenie << " и " << Max->Znachenie << ": ";
        Uzel* Tekushiy = Start->Sleduyushiy;
        bool EstElementy = false;

        while (Tekushiy != nullptr && Tekushiy != End) {
            cout << Tekushiy->Znachenie << " ";
            EstElementy = true;
            Tekushiy = Tekushiy->Sleduyushiy;
        }

        if (!EstElementy) cout << "Отсутствуют";
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Spisok Spisok;
    Spisok.Initsializatsiya();

    cout << "Введите количество элементов: ";
    int N;
    cin >> N;

    if (N <= 0) {
        cout << "Некорректное число!" << endl;
        return 0;
    }

    cout << "Вводите элементы:" << endl;
    for (int i = 0; i < N; i++) {
        int Chislo;
        if (!(cin >> Chislo)) {
            cout << "Ошибка ввода!" << endl;
            return 0;
        }
        Spisok.DobavitElement(Chislo);
    }

    cout << "Список: ";
    Spisok.VivodSpiska();
    Spisok.VivodMezhduMinMax();
    Spisok.Ochistka();

    return 0;
}
