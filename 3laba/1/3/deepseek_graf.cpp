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
    // Открываем файл для чтения
    ifstream inputFile("FileName.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл FileName.txt" << endl;
        return 1;
    }

    int n;
    inputFile >> n; // Читаем количество вершин

    vector<vector<int>> adjacencyMatrix(n, vector<int>(n));
    vector<int> degrees(n, 0);

    // Читаем матрицу смежности
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> adjacencyMatrix[i][j];
        }
    }
    inputFile.close();

    // Вычисляем степени вершин
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                degrees[i]++; // Учитываем ребро
                if (i == j) degrees[i]++; // Учитываем петлю второй раз
            }
        }
    }

    // Выводим степени вершин в порядке возрастания их номеров
    for (int i = 0; i < n; ++i) {
        cout << "Вершина " << i + 1 << ": степень = " << degrees[i] << endl;
    }

    return 0;
}
