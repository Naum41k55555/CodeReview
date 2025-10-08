/* 
В текстовом файле с именем FN1 дано арифметическое выражение в инфиксной
форме. В выражении могут использоваться операции: сложение(+), вычитание(-), умножение(*),
деление нацело(/), остаток от деления(%), возведение в степень(^), а так же целые числа из 
промежутка [1; 30] и переменная x. Для операции возведения в степень показатель степени неотрицательное целое число. 
Постройте дерево выражения. После этого вычислите значение выражения при заданном значении переменной x и выведите результат в текстовый файл с именем FN2.
Преобразуйте дерево, заменив все поддеревья вида x*A на A*x, где A - некоторое поддерево, а x
- переменная. Распечатайте дерево после преобразования в файл FN2 используя многострочный
формат, в котором дерево положено на бок. Каждый уровень дерева выводите в 4-х позициях и
используйте выравнивание по правому краю. При наличии нескольких подряд идущих одинаковых операций дерево должно 
строиться по правилу: операции одинакового приоритета вычисляются по порядку слева направо. Иными словами, выражение 2+3+4+5,
например, должно трактоваться как ((2+3)+4)+5, и не может трактоваться как (2+3)+(4+5) или 2+(3+(4+5)). Результаты всех
вычислений, включая промежуточные, принадлежат типу int.
*/

#include "calctree.h"
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>

Node::Node(std::string val) : value(val), left(nullptr), right(nullptr) {}

int Get_priority(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^") return 3;
    return 0;
}

bool Is_number(const std::string& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

bool Is_operator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^";
}

std::vector<std::string> Tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string current_token;
    for (char c : expression) {
        if (isspace(c)) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
        } else if (isdigit(c)) {
            current_token += c;
        } else if (Is_operator(std::string(1, c)) || c == '(' || c == ')') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(std::string(1, c));
        } else if (c == 'x') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back("x");
        }
    }
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    return tokens;
}

Node* Build_expression_tree(std::vector<std::string>& postfix_tokens) {
    std::stack<Node*> node_stack;
    for (const std::string& token : postfix_tokens) {
        if (Is_number(token) || token == "x") {
            node_stack.push(new Node(token));
        } else if (Is_operator(token)) {
            Node *right_operand = node_stack.top();
            node_stack.pop();
            Node *left_operand = node_stack.top();
            node_stack.pop();
            Node *op_node = new Node(token);
            op_node->left = left_operand;
            op_node->right = right_operand;
            node_stack.push(op_node);
        }
    }
    return node_stack.top();
}

std::vector<std::string> Infix_to_postfix(const std::vector<std::string>& infix_tokens) {
    std::vector<std::string> postfix_tokens;
    std::stack<std::string> operator_stack;

    for (const std::string& token : infix_tokens) {
        if (Is_number(token) || token == "x") {
            postfix_tokens.push_back(token);
        } else if (token == "(") {
            operator_stack.push(token);
        } else if (token == ")") {
            while (!operator_stack.empty() && operator_stack.top() != "(") {
                postfix_tokens.push_back(operator_stack.top());
                operator_stack.pop();
            }
            if (!operator_stack.empty() && operator_stack.top() == "(") {
                operator_stack.pop();
            }
        } else if (Is_operator(token)) {
            while (!operator_stack.empty() && Get_priority(operator_stack.top()) >= Get_priority(token)) {
                postfix_tokens.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(token);
        }
    }

    while (!operator_stack.empty()) {
        postfix_tokens.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return postfix_tokens;
}

int Evaluate(Node* node, int x_value) {
    if (!node) return 0;
    if (Is_number(node->value)) {
        return std::stoi(node->value);
    } else if (node->value == "x") {
        return x_value;
    } else {
        int left_val = Evaluate(node->left, x_value);
        int right_val = Evaluate(node->right, x_value);
        if (node->value == "+") return left_val + right_val;
        if (node->value == "-") return left_val - right_val;
        if (node->value == "*") return left_val * right_val;
        if (node->value == "/") return left_val / right_val;
        if (node->value == "%") return left_val % right_val;
        if (node->value == "^") return std::pow(left_val, right_val);
    }
    return 0;
}

Node* Transform_tree(Node* node) {
    if (!node) return nullptr;

    node->left = Transform_tree(node->left);
    node->right = Transform_tree(node->right);

    if (node->value == "*" && node->left && node->left->value == "x") {
        std::swap(node->left, node->right);
    }

    return node;
}

void Print_tree_helper(Node* node, int level, std::ofstream& outfile) {
    if (!node) return;

    Print_tree_helper(node->right, level + 1, outfile);

    outfile << std::setw(level * 4) << std::right << node->value << std::endl;

    Print_tree_helper(node->left, level + 1, outfile);
}

void Print_tree(Node* root, std::ofstream& outfile) {
    Print_tree_helper(root, 0, outfile);
}

void Delete_tree(Node* node) {
    if (node) {
        Delete_tree(node->left);
        Delete_tree(node->right);
        delete node;
    }
}
