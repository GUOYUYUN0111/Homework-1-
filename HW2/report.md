# 41141106

作業二

## 解題說明

本題實作了一個多項式 (Polynomial) 類別，建立兩個多項式。使用加法運算計算兩個多項式的和、乘法運算計算兩個多項式的乘積、求值運算計算多項式在代 x 值後的結果為多少。且輸入輸出使用 << 和 >> 運算子進行多項式的顯示和輸入。

### 解題策略

使用動態陣列配置和維持指數降序排列，新增項目時找到正確位置插入，並且將相同指數的項目自動合併係數。

運算實作：

    加法：兩個多項式的所有項目相加，指數相同的係數相加
    乘法：對每一項進行積的運算，係數相乘、指數相加
    求值：使用 pow() 函數計算每項的值並累加


## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
    float* coeff;
    int* exp;
    int size, capacity;
    
    void resize() {
        float* tempCoeff = new float[capacity * 2];
        int* tempExp = new int[capacity * 2];
        for (int i = 0; i < size; i++) {
            tempCoeff[i] = coeff[i];
            tempExp[i] = exp[i];
        }
        delete[] coeff;
        delete[] exp;
        coeff = tempCoeff;
        exp = tempExp;
        capacity *= 2;
    }
    
public:
    Polynomial() : size(0), capacity(2) {
        coeff = new float[capacity];
        exp = new int[capacity];
    }
    
    Polynomial(const Polynomial& p) : size(p.size), capacity(p.capacity) {
        coeff = new float[capacity];
        exp = new int[capacity];
        for (int i = 0; i < size; i++) {
            coeff[i] = p.coeff[i];
            exp[i] = p.exp[i];
        }
    }
    
    ~Polynomial() { 
        delete[] coeff; 
        delete[] exp; 
    }
    
    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            delete[] coeff;
            delete[] exp;
            size = p.size;
            capacity = p.capacity;
            coeff = new float[capacity];
            exp = new int[capacity];
            for (int i = 0; i < size; i++) {
                coeff[i] = p.coeff[i];
                exp[i] = p.exp[i];
            }
        }
        return *this;
    }
    
    void AddTerm(float c, int e) {
        if (c == 0) return;
        
        for (int i = 0; i < size; i++) {
            if (exp[i] == e) {
                coeff[i] += c;
                if (coeff[i] == 0) {
                    for (int j = i; j < size - 1; j++) {
                        coeff[j] = coeff[j + 1];
                        exp[j] = exp[j + 1];
                    }
                    size--;
                }
                return;
            }
        }
        
        if (size == capacity) resize();
        
        int pos = size;
        for (int i = 0; i < size; i++) {
            if (e > exp[i]) {
                pos = i;
                break;
            }
        }
        
        for (int i = size; i > pos; i--) {
            coeff[i] = coeff[i - 1];
            exp[i] = exp[i - 1];
        }
        coeff[pos] = c;
        exp[pos] = e;
        size++;
    }
    
    Polynomial Add(const Polynomial& p) const {
        Polynomial result = *this;
        for (int i = 0; i < p.size; i++) {
            result.AddTerm(p.coeff[i], p.exp[i]);
        }
        return result;
    }
    
    Polynomial Mult(const Polynomial& p) const {
        Polynomial result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < p.size; j++) {
                result.AddTerm(coeff[i] * p.coeff[j], exp[i] + p.exp[j]);
            }
        }
        return result;
    }
    
    float Eval(float x) const {
        float result = 0;
        for (int i = 0; i < size; i++) {
            result += coeff[i] * pow(x, exp[i]);
        }
        return result;
    }
    
    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        if (p.size == 0) return os << "0";
        
        for (int i = 0; i < p.size; i++) {
            if (i > 0 && p.coeff[i] > 0) os << " + ";
            else if (i > 0) os << " ";
            
            if (p.coeff[i] < 0) os << "- " << -p.coeff[i];
            else if (i > 0) os << p.coeff[i];
            else os << p.coeff[i];
            
            if (p.exp[i] > 1) os << "x^" << p.exp[i];
            else if (p.exp[i] == 1) os << "x";
        }
        return os;
    }
};

int main() {
    Polynomial p1, p2;
    
    cout << "輸入p1: " << p1 << endl;
    cout << "輸入p2: " << p2 << endl;
    
    cout << "Sum: " << p1.Add(p2) << endl;
    cout << "Mult: " << p1.Mult(p2) << endl;
    
    cout << "p1 = " << p1.Eval(2) << endl;
    cout << "p2 = " << p2.Eval(2) << endl;
    
    return 0;
}
```
## 效能分析

1. 時間複雜度：
    AddTerm()：O(n)
    Add()：O(m * n)
    Mult()：O(n² * m²)
    Eval()：O(n log e)
    operator<<:O(n)

2. 空間複雜度：
    AddTerm()：O(n)
    Add()：O(n + m)
    Mult()：O(n * m)
    Eval()：O(1)
     operator<<:O(1)

## 測試與驗證

### 測試案例

// p1 = 3x^2 + 1

    p1.AddTerm(3,2);
    p1.AddTerm(1, 0);

// p2 = 5x^2 + 2x

    p2.AddTerm(5, 2);
    p2.AddTerm(2,1);
    
output

    輸入p1: 3x^2 + 1
    輸入p2: 5x^2 + 2x
    Sum: 8x^2 + 2x + 1
    Mult: 15x^4 + 6x^3 + 5x^2 + 2x
    p1 = 13
    p2 = 24


### 編譯與執行指令
```shell
$ g++ -o polynomial polynomial.cpp 
$./polynomial
```

### 結論

實作一個完整的多項式類別，採用雙陣列結構分別儲存係數和指數來實作多項式的基本運算功能，包括加法、乘法、求值操作。在過程中乘法的實作篇複雜，需要每一項與每一項相乘。但使用了AddTerm() 函數來處理項目合併，簡化了許多。

## 申論及開發報告

1. **項目排序與合併**  
    在新增項目時需要維持指數降序排列，並且處理相同指數項目，所以使用了resize()函數，配合完整的建構子和解構子系統。
2. **多項式的乘法實作**  
    需要處理所有項目對的乘積組合，所以使用雙層迴圈，利用 AddTerm() 自動處理重複項目。


