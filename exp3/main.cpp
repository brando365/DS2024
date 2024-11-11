#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
using namespace std;

// Bitmap �ࣺ��ʾһ��λͼ��֧��ͨ��������ȡ����չλͼ��С��
class Bitmap {
public:
    Bitmap(int n) : bits(n) {} // ���캯������ʼ��λͼ��λͼ�Ĵ�СΪn
    void set(int index, bool value) { if (index < bits.size()) bits[index] = value; }
    bool test(int index) const { return index < bits.size() && bits[index]; }
    void expand(int index) { if (index >= bits.size()) bits.resize(index + 1); }
private:
    vector<bool> bits; // �洢λͼ���ݵ�����
};

// HuffCode �ࣺ�̳��� Bitmap �࣬��ʾ���������롣
// ���ڴ洢�͹����������������
class HuffCode : public Bitmap {
public:
    HuffCode() : Bitmap(8) {}
    HuffCode(int n) : Bitmap(n) {}
};

// HuffChar �ṹ�壺��ʾ���������е��ַ��ڵ㡣
// �����ַ����ַ���Ȩ�أ�Ƶ�ʣ��Լ����������롣
struct HuffChar {
    char ch;
    int weight;
    HuffCode code;
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}
};

template <typename T>
struct BinNode {
    T data;
    BinNode<T>* left;
    BinNode<T>* right;
    BinNode<T>* parent;
    
    BinNode(T e, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, BinNode<T>* p = nullptr)
        : data(e), left(l), right(r), parent(p) {}
};

// HuffTree �ࣺ��ʾ�����������ṩ��������������ɺͱ���Ĳ�����
// ����ͨ��������������������ÿ���ַ��Ļ��������룬֧�ֱ���ʹ�ӡ��������
class HuffTree {
private:
    BinNode<HuffChar>* root;  // ���������ĸ��ڵ�
    vector<BinNode<HuffChar>*> forest; 
    void buildHuffTree(int* freq, int n) {
        struct CompareNode {
            bool operator()(BinNode<HuffChar>* a, BinNode<HuffChar>* b) {
                return a->data.weight > b->data.weight; // ��Ȩ����������
            }
        };
        priority_queue<BinNode<HuffChar>*, vector<BinNode<HuffChar>*>, CompareNode> pq;  // ���ȶ��У���Ȩ������
        for (int i = 0; i < n; i++) {
            if (freq[i] > 0) {
                BinNode<HuffChar>* node = new BinNode<HuffChar>(HuffChar(i + 'a', freq[i]));
                forest.push_back(node);
                pq.push(node);
            }
        }
        // �ϲ��ڵ�ֱ��ֻʣһ�����ڵ�
        while (pq.size() > 1) {
            BinNode<HuffChar>* left = pq.top(); pq.pop();
            BinNode<HuffChar>* right = pq.top(); pq.pop();          
            BinNode<HuffChar>* parent = new BinNode<HuffChar>(
                HuffChar('^', left->data.weight + right->data.weight), left, right, nullptr);
            left->parent = parent;
            right->parent = parent;  
            forest.push_back(parent);
            pq.push(parent);
        }
        root = pq.empty() ? nullptr : pq.top(); // ���ø��ڵ�
    }
    void generateCodes(BinNode<HuffChar>* node, HuffCode& prefix, int length, HuffCode codeTable[], int n) {
        if (!node) return; // �����սڵ㷵��
        // Ҷ�ӽڵ㣨�ַ��ڵ㣩���������
        if (!node->left && !node->right) {
            codeTable[node->data.ch - 'a'] = prefix;
            codeTable[node->data.ch - 'a'].expand(length);
            return;
        }
        // �ݹ������������ı��루0��
        if (node->left) {
            prefix.set(length, 0);
            generateCodes(node->left, prefix, length + 1, codeTable, n);
        }
        // �ݹ������������ı��루1��
        if (node->right) {
            prefix.set(length, 1);
            generateCodes(node->right, prefix, length + 1, codeTable, n);
        }
    }
public:
    // ���캯����ͨ��Ƶ�����鹹����������
    HuffTree(int* freq, int n) : root(nullptr) {
        buildHuffTree(freq, n);
    }
    // �����������ͷ����ж�̬����Ľڵ�
    ~HuffTree() {
        for (auto node : forest) {
            delete node;
        }
    }
    // ���ɻ���������
    void generateCodes(HuffCode codeTable[], int n) {
        if (!root) return;
        HuffCode prefix(n * 8); // ����ǰ׺�����֧��8λ���룩
        generateCodes(root, prefix, 0, codeTable, n);
    }
    // ��ӡ����������
    void printCodes(HuffCode codeTable[], int n) {
        cout<<"����������:"<<endl;
        for (int i = 0; i < n; i++) {
            if (forest.size() > 0) {
                for (auto node : forest) {
                    if (node->data.ch == char(i + 'a')) {
                        cout << char(i + 'a') << ": ";
                        for (int j = 0; j < n * 8; j++) {
                            if (j > 0 && !codeTable[i].test(j)) {
                                bool allZeros = true;
                                for (int k = j + 1; k < n * 8; k++) {
                                    if (codeTable[i].test(k)) {
                                        allZeros = false;
                                        break;
                                    }
                                }
                                if (allZeros) break;
                            }
                            cout << (codeTable[i].test(j) ? "1" : "0");
                        }
                        cout << "\n";
                        break;
                    }
                }
            }
        }
    }
};

// encodeWord ��������ָ���ĵ��ʱ��벢�����
// word ΪҪ����ĵ��ʣ�codeTable Ϊ�����������n Ϊ�ַ�����
void encodeWord(const string& word, HuffCode codeTable[], int n) {
    cout << "���� " << word << " : ";
    for (char c : word) {
        if (isalpha(c)) {
            HuffCode& code = codeTable[tolower(c) - 'a'];
            for (int j = 0; j < n * 8; j++) {
                if (j > 0 && !code.test(j)) {
                    bool allZeros = true;
                    for (int k = j + 1; k < n * 8; k++) {
                        if (code.test(k)) {
                            allZeros = false;
                            break;
                        }
                    }
                    if (allZeros) break;
                }
                cout << (code.test(j) ? "1" : "0");
            }
            cout << " ";
        }
    }
    cout << "\n";
}

void huffmanExample() {
    const int N_CHAR = 26; // 26����ĸ
    // ���ļ�
    ifstream inputFile("word.txt");  
    string text;
    // ��ȡ�ļ�����
    char c;
    while (inputFile.get(c)) {
        text += c;
    }
    inputFile.close();
    int freq[N_CHAR] = {0};
    // ����Ƶ��
    for (char c : text) {
        if (isalpha(c)) {
            freq[tolower(c) - 'a']++;
        }
    }
    // ��ӡÿ����ĸ��Ƶ��
    cout << "��ĸƵ��ͳ�ƣ�" << endl;
    for (int i = 0; i < N_CHAR; i++) {
        cout << char(i + 'a') << ": " << freq[i] << endl;
    }
    HuffTree* tree = new HuffTree(freq, N_CHAR);
    HuffCode codeTable[N_CHAR];
    tree->generateCodes(codeTable, N_CHAR);
    tree->printCodes(codeTable, N_CHAR);
    // �����ض�����
    encodeWord("dream", codeTable, N_CHAR);
    encodeWord("love", codeTable, N_CHAR);
    encodeWord("is", codeTable, N_CHAR);
    encodeWord("you", codeTable, N_CHAR);
    
    cout << endl;
    delete tree;
}

int main() {
    huffmanExample();
    return 0;
}