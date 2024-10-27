#include <iostream>
#include "stack.cpp"
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
using namespace std;


// ��������������ȼ�
int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        case '!': return 4;
        default: return 0;
    }
}

// ����������������һ���������Ľ��
double evaluate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '^': return pow(a, b);
        case '!':
            if (a < 0) throw runtime_error("Gamma function is not defined for negative values");
            return tgamma(a + 1);
        default: throw runtime_error("Invalid operator");
    }
}

// ����ַ��Ƿ�Ϊ������
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!';
}

// ����ַ��Ƿ�Ϊ����
bool isNumber(char c) {
    return isdigit(c) || c == '.';
}

// ������ʽ��ֵ
double calculate(const string &expression) {
    Stack<double> numStack;  // ������ջ
    Stack<char> opStack;     // �����ջ
    string numBuffer;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (isspace(c)) continue;
        if (isNumber(c)) {
            numBuffer += c;
        } else {
            if (!numBuffer.empty()) {
                numStack.push(stod(numBuffer));
                numBuffer.clear();
            }

            if (isOperator(c)) {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                    double b = numStack.top(); numStack.pop();
                    double a = numStack.top(); numStack.pop();
                    char op = opStack.top(); opStack.pop();
                    numStack.push(evaluate(a, b, op));
                }
                opStack.push(c);
            } else if (c == '(') {
                opStack.push(c);
            } else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    double b = numStack.top(); numStack.pop();
                    double a = numStack.top(); numStack.pop();
                    char op = opStack.top(); opStack.pop();
                    numStack.push(evaluate(a, b, op));
                }
                opStack.pop();
            }
        }
    }

    if (!numBuffer.empty()) {
        numStack.push(stod(numBuffer));
    }
    while (!opStack.empty()) {
        double b = numStack.top(); numStack.pop();
        double a = numStack.top(); numStack.pop();
        char op = opStack.top(); opStack.pop();
        numStack.push(evaluate(a, b, op));
    }
    return numStack.top();
}

// ��չ��֧�����Ǻ���
double sin(const string &expression) {
    size_t start = expression.find('(');
    size_t end = expression.find(')');
    if (start == string::npos || end == string::npos || start > end) {
        throw runtime_error("Invalid trigonometric expression");
    }
    double angle = stod(expression.substr(start + 1, end - start - 1));
    return sin(angle * M_PI / 180.0); // ���Ƕ�ת��Ϊ����
}
double cos(const string &expression) {
    size_t start = expression.find('(');
    size_t end = expression.find(')');
    if (start == string::npos || end == string::npos || start > end) {
        throw runtime_error("Invalid trigonometric expression");
    }
    double angle = stod(expression.substr(start + 1, end - start - 1));
    return cos(angle * M_PI / 180.0);
}
//��������
double ln(const string &expression) {
    size_t start = expression.find('(');
    size_t end = expression.find(')');
    if (start == string::npos || end == string::npos || start > end) {
        throw runtime_error("Invalid logarithm expression");
    }
    double num = stod(expression.substr(start + 1, end - start - 1));
    return log(num);
}
// ����״ͼ�����������
int largestarea(const vector<int> &heights) {
    Stack<int> st;
    int maxArea = 0;
    int n = heights.size();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()]; st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    while (!st.empty()) {
        int h = heights[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        maxArea = max(maxArea, h * width);
    }
    return maxArea;
}

// ������ɲ�������
void generatetest(int numTests) {
    srand(time(0)); // ��ʼ�����������
    for (int i = 0; i < numTests; ++i) {
        int length = rand() % 105 + 1; // ���������״ͼ���� (1 �� 105)
        vector<int> heights(length);
        cout << "����" << i + 1 << ": [ ";
        for (int j = 0; j < length; ++j) {
            heights[j] = rand() % 104; // ����������Ӹ߶� (0 �� 104)
            cout << heights[j] << " ";
        }
        cout << "]" << endl;
        int maxArea = largestarea(heights);
        cout << "���: " << maxArea << endl << endl;
    }
}

int main() {
    // �ַ���������ʾ������
    string A1 = "5 ^ 3 - 2.4 * 16 / 2";
    cout << "��������: " << A1 << " = " << calculate(A1) << endl << endl;
    string A2 = "(8 - 2) * 5";
    cout << "��������: " << A2 << " = " << calculate(A2) << endl << endl;
    string A3 = "cos(30)";
    cout << "��������: " << A3 << " = " << cos(A3) << endl << endl;
    string A4 = "ln(10)";
    cout << "��������: " << A4 << " = " << ln(A3) << endl << endl;
    // ������״ͼ���������
    vector<int> B1 = {2, 1, 5, 6, 2, 3};
    vector<int> B2 = {2, 4};
    cout << "����: [2, 1, 5, 6, 2, 3]" << endl;
    cout << "���: " << largestarea(B1) << endl << endl;
    cout << "����: [2, 4]" << endl;
    cout << "���: " << largestarea(B2) << endl << endl;
    // ������� 10 ���������
    generatetest(10);
    return 0;
}