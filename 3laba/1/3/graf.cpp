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
#include <fstream>
#include <vector>
#include <string>

bool ReadAdjacencyMatrix(const std::string& filename, int& n, std::vector<std::vector<int>>& adjacencyMatrix) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }

    if (!(inputFile >> n) || n <= 0) {
        std::cerr << "Некорректный формат файла: отсутствует количество вершин или оно неверно." << std::endl;
        inputFile.close();
        return false;
    }

    adjacencyMatrix.resize(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(inputFile >> adjacencyMatrix[i][j])) {
                std::cerr << "Некорректный формат файла: ошибка при чтении матрицы смежности." << std::endl;
                inputFile.close();
                return false;
            }
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                std::cerr << "Некорректный формат файла: матрица смежности должна содержать только 0 и 1." << std::endl;
                inputFile.close();
                return false;
            }
        }
    }

    inputFile.close();
    return true;
}

void CalculateDegrees(int n, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& degrees) {
    degrees.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                if (i == j) {
                    degrees[i] += 2;
                } else {
                    degrees[i]++;
                }
            }
        }
    }
}
