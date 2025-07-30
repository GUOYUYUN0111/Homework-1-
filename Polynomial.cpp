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
        
        // 檢查是否已存在相同指數
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
        
        // 按指數降序插入
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