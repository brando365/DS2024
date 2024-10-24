#include <iostream>
#include <cmath>
#include "vector.cpp"
#include <chrono>
#include <ctime>
using namespace std;
// �����ඨ��
class Complex
{
public:
    double real;
    double imag;
    // ���������
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    double modulus() const
    {return sqrt(real * real + imag * imag);}
    // ���� <= ������
    bool operator<=(const Complex &other) const
    {return (real <= other.real && imag <= other.imag);}
    // ���� > ������
    bool operator>(const Complex &other) const
    {return (real > other.real || (real == other.real && imag > other.imag));}
    // ����С������������ڱȽϸ���ģ��˳��
    bool operator<(const Complex &other) const
    {return modulus() < other.modulus() || (modulus() == other.modulus() && real < other.real);}
    // ���� != �����
    bool operator!=(const Complex &other) const
    {return (real != other.real || imag != other.imag);}
    // ����==
    bool operator==(const Complex &other) const
    {return real == other.real && imag == other.imag;}
    friend ostream &operator<<(ostream &os, const Complex &c)
    {os << "(" << c.real << ", " << c.imag << ")";return os;}
};
void print(Complex &c){
    cout<<c.real<<"+"<<c.imag<<"i ";
}
//�����������
Vector<Complex> GRV(int size){
    Vector<Complex> vec;
    int s = size-1;
    Vector<Complex> vec1;
    for(int i=0;i<s;i++){
        double real = rand() % 10; // ʵ���� 0 �� 9 ֮��
        double imag = rand() % 10; // �鲿�� 0 �� 9 ֮��
        vec1.insert(Complex(real, imag));
        vec.insert(Complex(real, imag)); // ���뵽���յ�������
    }
    int randomIndex = rand() % s; // ��ΨһԪ�������ѡ��
        vec.insert(vec1[randomIndex]);
    return vec;
}

// ����ģ˳������
void SortV(Vector<Complex> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        Complex key = arr[i];
        int j = i - 1;
        // ��������ģ˳������ģ���ʱ��ʵ������
        while (j >= 0 && key < arr[j])
        {arr[j + 1] = arr[j];j = j - 1;}
        arr[j + 1] = key;
    }
}
//ģ�������
Vector<Complex> findInRange(const Vector<Complex> &arr, double m1, double m2)
{
    Vector<Complex> result;
    int n = arr.size();
    for (size_t i = 0; i < n; ++i)
    {
        double modulus = arr[i].modulus();
        if (modulus >= m1 && modulus < m2)
        {result.insert(arr[i]);}
    }
    return result;
}
bool compare(const Complex& a, const Complex& b) {
	if(a.modulus() == b.modulus()) {
		return a.real < b.real;
	}
	return a.modulus() < b.modulus();
}
void merge(Vector<Complex>& v, Vector<Complex>& left, Vector<Complex>& right) {
	int i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size()) {
		if (compare(left[i], right[j])) {
			v[k++] = left[i++];
		} else {
			v[k++] = right[j++];
		}
	}
	while (i < left.size()) {
		v[k++] = left[i++];
	}
	while (j < right.size()) {
		v[k++] = right[j++];
	}
}

void mergeSort(Vector<Complex>& v) {
	if (v.size() <= 1) {
		return;
	}
	Vector<Complex> left, right;
	for (int i = 0; i < v.size() / 2; i++) {
		left.insert(i, v[i]);
	}
	for (int i = v.size() / 2; i < v.size(); i++) {
		right.insert(i - v.size() / 2, v[i]);
	}
	mergeSort(left);
	mergeSort(right);
	merge(v, left, right);
}

// ��������������
Vector<Complex> unGRV(int size){
    Vector<Complex> vec;
    int s = size-1;
    Vector<Complex> vec1;
    for(int i=s-1;i>=0;i--){
        double real = rand() % 10; // ʵ���� 0 �� 9 ֮��
        double imag = rand() % 10; // �鲿�� 0 �� 9 ֮��
        vec1.insert(Complex(real, imag));
        vec.insert(Complex(real, imag)); // ���뵽���յ�������
    }
    int randomIndex = rand() % s; // ��ΨһԪ�������ѡ��
        vec.insert(vec1[randomIndex]);
    return vec;
}



int main(){
    int n = 100;
    Vector<Complex> vec = GRV(n);
    vec.traverse(print);
    cout<<"\n"<<"���Һ�"<<endl;
    vec.unsort(0,n);
    vec.traverse(print);
    Complex comp1(1,1);
    Rank find = vec.find(comp1);
    if(find == -1 )
        cout<<"\n"<<"δ�ҳ�����"<<comp1;
    else
        cout<<"\n"<<"�ҳ�����"<<comp1<<"��"<<find;
    Complex comp2(3,2);
    vec.insert(2,comp2);
    cout<<"\n"<<"����"<<comp2<<"��"<<endl;
    vec.traverse(print);
    vec.remove(10);
    cout<<"\n"<<"ɾ��"<<vec[10]<<"��"<<endl;
    vec.traverse(print);
    vec.deduplicate();
    cout <<"\n"<< "Ψһ����\n";
    vec.traverse(print);
    SortV(vec);
    cout <<"\n"<< "�����\n";
    vec.traverse(print);
    Vector<Complex> vecfind = findInRange(vec,3.0,8.0);
    cout <<"\n"<< "����ģ������[3,8)��Ԫ��\n";
    vecfind.traverse(print);

    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    vec.bubbleSort(0, vec.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\n˳�������������ʱ��:%f\n", total_t  );
    
    start_t = clock();
    mergeSort(vec);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("˳��鲢�������ʱ�䣺%f\n", total_t  );

    vec.unsort(0,n);
    start_t = clock();
    vec.bubbleSort(0, vec.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("���������������ʱ��:%f\n", total_t  );

    start_t = clock();
    mergeSort(vec);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("���ҹ鲢�������ʱ�䣺%f\n", total_t  );

    Vector<Complex> vec2 = unGRV(n);
    start_t = clock();
    vec2.bubbleSort(0, vec2.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("���������������ʱ��:%f\n", total_t  );

    start_t = clock();
    mergeSort(vec2);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("����鲢�������ʱ�䣺%f\n", total_t  );




}