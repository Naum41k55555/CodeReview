/*
В текстовом файле с именем FN1 дано арифметическое выражение в инфиксной
форме. В выражении могут использоваться операции: сложение(+), вычитание(-), умножение(*),
деление нацело(/), остаток от деления(%), возведение в степень(^), а так же целые числа из промежутка [1; 30]
и переменная x. Для операции возведения в степень показатель степени неотрицательное целое число. Постройте дерево выражения.
После этого вычислите значение выражения при заданном значении переменной x и выведите результат в текстовый файл с именем FN2.
Преобразуйте дерево, заменив все поддеревья вида x*A на A*x, где A - некоторое поддерево, а x
- переменная. Распечатайте дерево после преобразования в файл FN2 используя многострочный
формат, в котором дерево положено на бок. Каждый уровень дерева выводите в 4-х позициях и
используйте выравнивание по правому краю. При наличии нескольких подряд идущих одинаковых операций дерево должно строиться по правилу:
операции одинакового приоритета вычисляются по порядку слева направо. Иными словами, выражение 2+3+4+5, например, должно трактоваться как ((2+3)+4)+5,
и не может трактоваться как (2+3)+(4+5) или 2+(3+(4+5)). Результаты всех вычислений, включая промежуточные, принадлежат типу int.
*/

#include "calctree.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename_in = "FN1";
    std::string filename_out = "FN2";
    std::string expression_str;
    int x_value;

    std::ifstream infile(filename_in);
    if (infile.is_open()) {
        std::getline(infile, expression_str);
        infile.close();
    } else {
        std::cerr << "Не удалось открыть файл: " << filename_in << std::endl;
        return 1;
    }

    std::cout << "Введите значение переменной x: ";
    std::cin >> x_value;

    std::vector<std::string> infix_tokens = Tokenize(expression_str);

    std::vector<std::string> postfix_tokens = Infix_to_postfix(infix_tokens);

    Node* root = Build_expression_tree(postfix_tokens);

    int result = Evaluate(root, x_value);

    Node* transformed_root = Transform_tree(root);

    std::ofstream outfile(filename_out);
    if (outfile.is_open()) {
        outfile << "Результат вычисления: " << result << std::endl << std::endl;
        outfile << "Преобразованное дерево:" << std::endl;
        Print_tree(transformed_root, outfile);
        outfile.close();
    } else {
        std::cerr << "Не удалось открыть файл: " << filename_out << std::endl;
        Delete_tree(transformed_root);
        return 1;
    }

    Delete_tree(transformed_root);

    return 0;
}
