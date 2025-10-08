/* 
Дано описание неориентированного графа в текстовом файле с именем FileName. в виде
матрицы смежности. Первая строка файла содержит количество вершин графа (n), а следующие
n строк содержат матрицу смежности (m), m[i][j]=0, если ребра между вершинами i и j не существует.
Определить степень для каждой вершины графа. Вывести степени вершин, перечисляя их
в порядке возрастания номеров вершин. Если в графе имеются петли, то каждая петля в степени
вершины учитывается дважды.
*/

#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Читает матрицу смежности неориентированного графа из файла.
 * @param filename Имя файла для чтения.
 * @param n Возвращает количество вершин графа.
 * @param adjacencyMatrix Возвращает матрицу смежности графа.
 * @return true, если чтение прошло успешно, false в случае ошибки.
 */
bool ReadAdjacencyMatrix(const std::string& filename, int& n, std::vector<std::vector<int>>& adjacencyMatrix);

/**
 * @brief Вычисляет степени каждой вершины неориентированного графа
 * @param n Количество вершин графа.
 * @param adjacencyMatrix Матрица смежности графа.
 * @param degrees Вектор для хранения степеней вершин.
 */
void CalculateDegrees(int n, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& degrees);

#endif // GRAPH_UTILS_H
