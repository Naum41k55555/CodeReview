#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// Класс для узла дерева выражений
class TreeNode {
public:
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для проверки, является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// Функция для определения приоритета оператора
int getPriority(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/' || op == '%') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

// Функция для преобразования инфиксной записи в постфиксную (ОПН)
vector<string> infixToPostfix(const string& expression) {
    vector<string> output;
    stack<char> operators;
    string numBuffer;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (isdigit(c)) {
            numBuffer += c;
            continue;
        }

        if (!numBuffer.empty()) {
            output.push_back(numBuffer);
            numBuffer.clear();
        }

        if (c == 'x') {
            output.push_back("x");
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop(); // Удаляем '(' из стека
        }
        else if (isOperator(c)) {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(c)) {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(c);
        }
    }

    if (!numBuffer.empty()) {
        output.push_back(numBuffer);
    }

    while (!operators.empty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

// Функция для построения дерева выражений из постфиксной записи
TreeNode* buildExpressionTree(const vector<string>& postfix) {
    stack<TreeNode*> nodeStack;

    for (const string& token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^") {
            TreeNode* node = new TreeNode(token);
            node->right = nodeStack.top();
            nodeStack.pop();
            node->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(node);
        }
        else {
            nodeStack.push(new TreeNode(token));
        }
    }

    return nodeStack.top();
}

// Функция для вычисления значения выражения
int evaluate(TreeNode* root, int x) {
    if (!root) return 0;

    if (root->value == "x") {
        return x;
    }
    else if (isdigit(root->value[0])) {
        return stoi(root->value);
    }

    int leftVal = evaluate(root->left, x);
    int rightVal = evaluate(root->right, x);

    if (root->value == "+") return leftVal + rightVal;
    if (root->value == "-") return leftVal - rightVal;
    if (root->value == "*") return leftVal * rightVal;
    if (root->value == "/") return leftVal / rightVal;
    if (root->value == "%") return leftVal % rightVal;
    if (root->value == "^") return (int)pow(leftVal, rightVal);

    return 0;
}

// Функция для преобразования дерева (x*A → A*x)
void transformTree(TreeNode* root) {
    if (!root) return;

    transformTree(root->left);
    transformTree(root->right);

    if (root->value == "*") {
        if (root->left && root->left->value == "x") {
            // Меняем местами левый и правый узлы
            TreeNode* temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
    }
}

// Функция для печати дерева в файл
void printTree(TreeNode* root, ofstream& outFile, int depth = 0) {
    if (!root) return;

    printTree(root->right, outFile, depth + 1);

    outFile << setw(4 * depth) << "" << root->value << endl;

    printTree(root->left, outFile, depth + 1);
}

// Основная функция
int main() {
    ifstream inFile("FN1.txt");
    ofstream outFile("FN2.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    string expression;
    getline(inFile, expression);

    // Удаляем пробелы из выражения
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    // Преобразуем в постфиксную форму
    vector<string> postfix = infixToPostfix(expression);

    // Строим дерево выражений
    TreeNode* root = buildExpressionTree(postfix);

    // Запрашиваем значение x
    int x;
    cout << "Введите значение переменной x: ";
    cin >> x;

    // Вычисляем значение выражения
    int result = evaluate(root, x);
    outFile << "Результат вычисления: " << result << endl << endl;

    // Преобразуем дерево
    transformTree(root);

    // Печатаем преобразованное дерево
    outFile << "Дерево выражения после преобразования:" << endl;
    printTree(root, outFile);

    // Закрываем файлы
    inFile.close();
    outFile.close();

    cout << "Результат записан в файл FN2.txt" << endl;

    return 0;
}
