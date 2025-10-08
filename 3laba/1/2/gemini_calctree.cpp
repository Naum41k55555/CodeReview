#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Структура узла дерева выражения
struct Node {
    string value;
    Node *left;
    Node *right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для определения приоритета операторов
int get_priority(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^") return 3;
    return 0;
}

// Функция для проверки, является ли строка числом
bool is_number(const string& s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

// Функция для проверки, является ли строка оператором
bool is_operator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^";
}

// Функция для лексического анализа выражения
vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    string current_token;
    for (char c : expression) {
        if (isspace(c)) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
        } else if (isdigit(c)) {
            current_token += c;
        } else if (is_operator(string(1, c)) || c == '(' || c == ')') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(string(1, c));
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

// Функция для построения дерева выражения из постфиксной нотации
Node* build_expression_tree(vector<string>& postfix_tokens) {
    stack<Node*> node_stack;
    for (const string& token : postfix_tokens) {
        if (is_number(token) || token == "x") {
            node_stack.push(new Node(token));
        } else if (is_operator(token)) {
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

// Функция для преобразования инфиксной нотации в постфиксную (обратная польская запись)
vector<string> infix_to_postfix(const vector<string>& infix_tokens) {
    vector<string> postfix_tokens;
    stack<string> operator_stack;

    for (const string& token : infix_tokens) {
        if (is_number(token) || token == "x") {
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
        } else if (is_operator(token)) {
            while (!operator_stack.empty() && get_priority(operator_stack.top()) >= get_priority(token)) {
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

// Функция для вычисления значения выражения
int evaluate(Node* node, int x_value) {
    if (!node) return 0;
    if (is_number(node->value)) {
        return stoi(node->value);
    } else if (node->value == "x") {
        return x_value;
    } else {
        int left_val = evaluate(node->left, x_value);
        int right_val = evaluate(node->right, x_value);
        if (node->value == "+") return left_val + right_val;
        if (node->value == "-") return left_val - right_val;
        if (node->value == "*") return left_val * right_val;
        if (node->value == "/") return left_val / right_val;
        if (node->value == "%") return left_val % right_val;
        if (node->value == "^") return pow(left_val, right_val);
    }
    return 0; // Никогда не должно достичь этой точки
}

// Функция для преобразования поддеревьев x * A в A * x
Node* transform_tree(Node* node) {
    if (!node) return nullptr;

    node->left = transform_tree(node->left);
    node->right = transform_tree(node->right);

    if (node->value == "*" && node->left && node->left->value == "x") {
        swap(node->left, node->right);
    }

    return node;
}

// Функция для печати дерева (рекурсивная)
void print_tree_helper(Node* node, int level, ofstream& outfile) {
    if (!node) return;

    print_tree_helper(node->right, level + 1, outfile);

    outfile << setw(level * 4) << right << node->value << endl;

    print_tree_helper(node->left, level + 1, outfile);
}

// Функция для печати дерева в файл
void print_tree(Node* root, ofstream& outfile) {
    print_tree_helper(root, 0, outfile);
}

// Функция для освобождения памяти, занятой деревом
void delete_tree(Node* node) {
    if (node) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

int main() {
    string filename_in = "FN1";
    string filename_out = "FN2";
    string expression_str;
    int x_value;

    // Чтение выражения из файла FN1
    ifstream infile(filename_in);
    if (infile.is_open()) {
        getline(infile, expression_str);
        infile.close();
    } else {
        cerr << "Не удалось открыть файл: " << filename_in << endl;
        return 1;
    }

    // Ввод значения переменной x
    cout << "Введите значение переменной x: ";
    cin >> x_value;

    // Лексический анализ
    vector<string> infix_tokens = tokenize(expression_str);

    // Преобразование в постфиксную нотацию
    vector<string> postfix_tokens = infix_to_postfix(infix_tokens);

    // Построение дерева выражения
    Node* root = build_expression_tree(postfix_tokens);

    // Вычисление значения выражения
    int result = evaluate(root, x_value);

    // Преобразование дерева
    Node* transformed_root = transform_tree(root);

    // Запись результата и преобразованного дерева в файл FN2
    ofstream outfile(filename_out);
    if (outfile.is_open()) {
        outfile << "Результат вычисления: " << result << endl << endl;
        outfile << "Преобразованное дерево:" << endl;
        print_tree(transformed_root, outfile);
        outfile.close();
    } else {
        cerr << "Не удалось открыть файл: " << filename_out << endl;
        delete_tree(transformed_root);
        return 1;
    }

    // Освобождение памяти
    delete_tree(transformed_root);

    return 0;
}
