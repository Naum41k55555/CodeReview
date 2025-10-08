/* 
Дано описание неориентированного графа в текстовом файле с именем FileName. в виде
матрицы смежности. Первая строка файла содержит количество вершин графа (n), а следующие
n строк содержат матрицу смежности (m), m[i][j]=0, если ребра между вершинами i и j не существует. 
Определить степень для каждой вершины графа. Вывести степени вершин, перечисляя их
в порядке возрастания номеров вершин. Если в графе имеются петли, то каждая петля в степени
вершины учитывается дважды.
*/

#include "graf.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string filename;
    std::cout << "Введите имя файла с матрицей смежности: ";
    std::cin >> filename;

    int n;
    std::vector<std::vector<int>> adjacencyMatrix;

    if (!ReadAdjacencyMatrix(filename, n, adjacencyMatrix)) {
        return 1;
    }

    std::vector<int> degrees;
    CalculateDegrees(n, adjacencyMatrix, degrees);

    std::cout << "Степени вершин графа (в порядке возрастания номеров вершин):" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "Степень вершины " << i + 1 << ": " << degrees[i] << std::endl;
    }

    return 0;
}
