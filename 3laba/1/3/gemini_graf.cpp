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
#include <string>
#include <sstream>

using namespace std;

int main() {
    string filename;
    cout << "Введите имя файла с матрицей смежности: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    if (inputFile.fail() || n <= 0) {
        cerr << "Некорректный формат файла: отсутствует количество вершин или оно неверно." << endl;
        inputFile.close();
        return 1;
    }

    vector<vector<int>> adjacencyMatrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(inputFile >> adjacencyMatrix[i][j])) {
                cerr << "Некорректный формат файла: ошибка при чтении матрицы смежности." << endl;
                inputFile.close();
                return 1;
            }
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                cerr << "Некорректный формат файла: матрица смежности должна содержать только 0 и 1." << endl;
                inputFile.close();
                return 1;
            }
        }
    }

    inputFile.close();

    vector<int> degrees(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                if (i == j) {
                    degrees[i] += 2; // Учитываем петлю дважды
                } else {
                    degrees[i]++; // Учитываем ребро
                }
            }
        }
    }

    cout << "Степени вершин графа (в порядке возрастания номеров вершин):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Степень вершины " << i + 1 << ": " << degrees[i] << endl;
    }

    return 0;
}
