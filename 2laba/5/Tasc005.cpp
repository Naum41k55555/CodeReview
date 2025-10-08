/* Элементами контейнеров являются целые числа. Для
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


#include <vector>
#include <ctime>
#include <deque>
#include <list>
#include <fstream>
#include <iostream>
using namespace std;
template <typename Container>
void Input(Container& N, int n)//Заполнение контейнеров
{
    int m, x;
    cout << "Выберете способ заполнения контейнера: " << endl;
    cout << "1)Ввод с клавиатуры." << endl;
    cout << "2)Ввод с помощью рандомайзера." << endl;
    cout << "3)Ввод данных из текстового файла." << endl;
    cin >> m;
    if (n < 2 || n % 2 != 0)
    {
        cout << "Ошибка. Недопустимый размер." << endl;
        return;
    }
    switch (m)
    {
    case 1:
    {
        for (int i = 0; i < n;i++)
        {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> x;
            N.insert(N.end(),x);
        }
        break;
    }
    case 2:
    {
        srand(time(0));
        for (int i = 0;i < n;i++)
            N.insert(N.end(), rand() % 101 - 50);
        break;
    }
    case 3:
    {
        ifstream file("a.txt", ios::in); // a.txt {2 4 98 6 39 0 -2 3 7 -38 24 100 27 -8 -11 -25 33 47 -30 -41 -8 3 -13 -29 -21 10 -33 -38 -18}
        if (!file)
        {
            cout << "Ошибка. Файл не был открыт.";
            return;
        }
        for (int i = 0; i < n;i++)
        {
            file >> x;
            N.insert(N.end(),x);
        }
        file.close();
        break;
    }
    default:
    {
        cout << "Ошибка ввода." << endl;
        break;
    }
    }
}
template <typename Container>
void Print(const Container& N)//Вывод содержимого контейнеров
{
    for (auto it = N.begin(); it != N.end(); it++)
        cout << *it << " ";
    cout << endl;
}
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
template <typename Container>
void MiddleElement(Container& N)//Меняет значения двух средних элементов контейнера
{
    auto it = N.begin();
    auto size = N.size();
    for (int i = 0; i < size / 2 - 1;i++)
        ++it;
    auto average1 = it;
    ++it;
    auto average2 = it;
    Swap(*average1, *average2);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n1, n2, n3;
    vector <int> V;
    deque <int> D;
    list <int> L;
    cout << "Введите размерность вектора n1 (n1 >= 2, n1-чётное): ";
    cin >> n1;
    Input(V, n1);
    cout << "Введите размерность дека n2 (n2 >= 2, n2-чётное): ";
    cin >> n2;
    Input(D, n2);
    cout << "Введите размерность списка n3 (n3 >= 2, n3-чётное): ";
    cin >> n3;
    Input(L, n3);
    cout << "Изначальное содержимое контейнеров." << endl;
    cout << "Вектор: ";
    Print(V);
    cout << "Дек: ";
    Print(D);
    cout << "Список: ";
    Print(L);
    MiddleElement(V);
    MiddleElement(D);
    MiddleElement(L);
    cout << "Изменённое содержание контейнеров." << endl;
    cout << "Вектор: ";
    Print(V);
    cout << "Дек: ";
    Print(D);
    cout << "Список: ";
    Print(L);
    cout << "      /\\     /\\  " << endl;
    cout << "     {  `---'  } " << endl;
    cout << "     {  O   O  } " << endl;
    cout << "     ~~>  V  <~~ " << endl;
    return 0;
}
