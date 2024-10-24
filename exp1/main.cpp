#include <iostream>
#include <cmath>
#include "vector.cpp"
#include <chrono>
#include <ctime>
using namespace std;
// 复数类定义
class Complex
{
public:
    double real;
    double imag;
    // 运算符重载
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    double modulus() const
    {return sqrt(real * real + imag * imag);}
    // 重载 <= 操作符
    bool operator<=(const Complex &other) const
    {return (real <= other.real && imag <= other.imag);}
    // 重载 > 操作符
    bool operator>(const Complex &other) const
    {return (real > other.real || (real == other.real && imag > other.imag));}
    // 定义小于运算符，用于比较复数模（顺序）
    bool operator<(const Complex &other) const
    {return modulus() < other.modulus() || (modulus() == other.modulus() && real < other.real);}
    // 重载 != 运算符
    bool operator!=(const Complex &other) const
    {return (real != other.real || imag != other.imag);}
    // 重载==
    bool operator==(const Complex &other) const
    {return real == other.real && imag == other.imag;}
    friend ostream &operator<<(ostream &os, const Complex &c)
    {os << "(" << c.real << ", " << c.imag << ")";return os;}
};
void print(Complex &c){
    cout<<c.real<<"+"<<c.imag<<"i ";
}
//生成随机复数
Vector<Complex> GRV(int size){
    Vector<Complex> vec;
    int s = size-1;
    Vector<Complex> vec1;
    for(int i=0;i<s;i++){
        double real = rand() % 10; // 实部在 0 到 9 之间
        double imag = rand() % 10; // 虚部在 0 到 9 之间
        vec1.insert(Complex(real, imag));
        vec.insert(Complex(real, imag)); // 插入到最终的向量中
    }
    int randomIndex = rand() % s; // 从唯一元素中随机选择
        vec.insert(vec1[randomIndex]);
    return vec;
}

// 复数模顺序排序
void SortV(Vector<Complex> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        Complex key = arr[i];
        int j = i - 1;
        // 按复数的模顺序排序，模相等时按实部排序
        while (j >= 0 && key < arr[j])
        {arr[j + 1] = arr[j];j = j - 1;}
        arr[j + 1] = key;
    }
}
//模区间查找
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

// 生成逆序复数向量
Vector<Complex> unGRV(int size){
    Vector<Complex> vec;
    int s = size-1;
    Vector<Complex> vec1;
    for(int i=s-1;i>=0;i--){
        double real = rand() % 10; // 实部在 0 到 9 之间
        double imag = rand() % 10; // 虚部在 0 到 9 之间
        vec1.insert(Complex(real, imag));
        vec.insert(Complex(real, imag)); // 插入到最终的向量中
    }
    int randomIndex = rand() % s; // 从唯一元素中随机选择
        vec.insert(vec1[randomIndex]);
    return vec;
}



int main(){
    int n = 100;
    Vector<Complex> vec = GRV(n);
    vec.traverse(print);
    cout<<"\n"<<"置乱后"<<endl;
    vec.unsort(0,n);
    vec.traverse(print);
    Complex comp1(1,1);
    Rank find = vec.find(comp1);
    if(find == -1 )
        cout<<"\n"<<"未找出复数"<<comp1;
    else
        cout<<"\n"<<"找出复数"<<comp1<<"在"<<find;
    Complex comp2(3,2);
    vec.insert(2,comp2);
    cout<<"\n"<<"插入"<<comp2<<"后"<<endl;
    vec.traverse(print);
    vec.remove(10);
    cout<<"\n"<<"删除"<<vec[10]<<"后"<<endl;
    vec.traverse(print);
    vec.deduplicate();
    cout <<"\n"<< "唯一化后\n";
    vec.traverse(print);
    SortV(vec);
    cout <<"\n"<< "排序后\n";
    vec.traverse(print);
    Vector<Complex> vecfind = findInRange(vec,3.0,8.0);
    cout <<"\n"<< "查找模区间在[3,8)的元素\n";
    vecfind.traverse(print);

    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    vec.bubbleSort(0, vec.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\n顺序起泡排序的总时间:%f\n", total_t  );
    
    start_t = clock();
    mergeSort(vec);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("顺序归并排序的总时间：%f\n", total_t  );

    vec.unsort(0,n);
    start_t = clock();
    vec.bubbleSort(0, vec.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("置乱起泡排序的总时间:%f\n", total_t  );

    start_t = clock();
    mergeSort(vec);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("置乱归并排序的总时间：%f\n", total_t  );

    Vector<Complex> vec2 = unGRV(n);
    start_t = clock();
    vec2.bubbleSort(0, vec2.size()-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("逆序起泡排序的总时间:%f\n", total_t  );

    start_t = clock();
    mergeSort(vec2);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("逆序归并排序的总时间：%f\n", total_t  );




}