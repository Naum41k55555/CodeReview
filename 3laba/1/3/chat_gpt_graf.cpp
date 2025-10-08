/* 
Дано описание неориентированного графа в текстовом файле с именем FileName. в виде
матрицы смежности. Первая строка файла содержит количество вершин графа (n), а следующие
n строк содержат матрицу смежности (m), m[i][j]=0, если ребра между вершинами i и j не существует. 
Определить степень для каждой вершины графа. Вывести степени вершин, перечисляя их
в порядке возрастания номеров вершин. Если в графе имеются петли, то каждая петля в степени
вершины учитывается дважды.
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream input("FileName.txt");

    if (!input.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    int n;
    input >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    vector<int> degrees(n, 0);

    // Чтение матрицы смежности
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            input >> matrix[i][j];

    input.close();

    // Подсчёт степени вершин
    for (int i = 0; i < n; ++i) {
        int degree = 0;
        for (int j = 0; j < n; ++j) {
            degree += matrix[i][j];
        }
        // Если есть петля, она считается дважды
        if (matrix[i][i] == 1)
            degree += 1;

        degrees[i] = degree;
    }

    // Вывод степеней
    cout << "Степени вершин:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Вершина " << i << ": " << degrees[i] << endl;
    }

    return 0;
}
