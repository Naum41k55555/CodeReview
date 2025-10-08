#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
#include <map>

using namespace std;

// Структура узла дерева
struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Приоритеты операций
map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};

// Проверка, является ли символ оператором
bool isOperator(char c) {
    return precedence.find(c) != precedence.end();
}

// Проверка, является ли символ цифрой
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Преобразование инфиксного выражения в дерево
Node* buildExpressionTree(const string& expr) {
    stack<Node*> nodes;
    stack<char> ops;

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (isspace(c)) continue;

        if (isDigit(c)) {
            string num(1, c);
            while (i + 1 < expr.length() && isDigit(expr[i + 1])) {
                num += expr[++i];
            }
            nodes.push(new Node(num));
        } else if (c == 'x') {
            nodes.push(new Node("x"));
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top();
                ops.pop();
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(string(1, op));
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.pop();
        } else if (isOperator(c)) {
            while (!ops.empty() && precedence[ops.top()] >= precedence[c]) {
                char op = ops.top();
                ops.pop();
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(string(1, op));
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.push(c);
        }
    }

    while (!ops.empty()) {
        char op = ops.top();
        ops.pop();
        Node* right = nodes.top(); nodes.pop();
        Node* left = nodes.top(); nodes.pop();
        Node* opNode = new Node(string(1, op));
        opNode->left = left;
        opNode->right = right;
        nodes.push(opNode);
    }

    return nodes.top();
}

// Вычисление значения дерева при заданном x
int evaluate(Node* root, int x) {
    if (!root) return 0;

    if (root->value == "x") return x;

    if (isdigit(root->value[0])) {
        return stoi(root->value);
    }

    int left = evaluate(root->left, x);
    int right = evaluate(root->right, x);

    if (root->value == "+") return left + right;
    if (root->value == "-") return left - right;
    if (root->value == "*") return left * right;
    if (root->value == "/") return left / right;
    if (root->value == "%") return left % right;
    if (root->value == "^") return pow(left, right);

    return 0;
}

// Преобразование дерева: x*A -> A*x
Node* transform(Node* root) {
    if (!root) return nullptr;

    root->left = transform(root->left);
    root->right = transform(root->right);

    if (root->value == "*" && root->left && root->left->value == "x") {
        swap(root->left, root->right);
    }

    return root;
}

// Вывод дерева в многострочном формате
void printTree(Node* root, int level = 0) {
    if (!root) return;

    printTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->value << endl;
    printTree(root->left, level + 1);
}

int main() {
    ifstream inputFile("FN1.txt");
    ofstream outputFile("FN2.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла FN1.txt" << endl;
        return 1;
    }

    string expr;
    getline(inputFile, expr);
    inputFile.close();

    Node* root = buildExpressionTree(expr);
    int x;
    cout << "Введите значение x: ";
    cin >> x;

    int result = evaluate(root, x);
    cout << "Результат вычисления: " << result << endl;

    outputFile << "Результат вычисления: " << result << endl;

    root = transform(root);
    outputFile << "Преобразованное дерево:" << endl;
    printTree(root);

   
::contentReference[oaicite:0]{index=0}
 
