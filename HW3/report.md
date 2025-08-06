# 41141106

作業三

## 解題說明

本題實作了一個Polynomial來表示和操作具有整數係數的單變數多項式，使用帶標頭節點的循環連結串列，且多項式中的每一項都將表示為一個節點。節點有三個資料成員coef(係數)、exp(指數)、link(指向下一項的指標)。還包含輸入輸出、支援多項式的基本運算：加減法、乘法運算及評估、 記憶體管理。

### 解題策略

1. 設計 struct Node，包含係數、指數、指標。
2. 環形鏈結串列使用header節點的設計。
3. 使用addTerm()函數來負責維持多項式的標準形式。
4. 運算子重載

    ● 加法：複製p1，加入p2的所有項目

    ● 減法：複製p1，加入p2項目的負值

    ● 乘法：雙重循環，將p1的每項與p2的每項相乘

## 程式實作

```cpp
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

class Polynomial {
private:
    struct Node {
        float coef;  
        int exp;    
        Node* link;  
        Node(float c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
    };
    
    Node* header;  

public:
    
    Polynomial() {
        header = new Node();
        header->link = header;  
    }
    
    Polynomial(const Polynomial& a) {
        header = new Node();
        header->link = header;
        
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp);
            current = current->link;
        }
    }
    
    ~Polynomial() {
        Node* current = header->link;
        while (current != header) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        delete header;
    }
    
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            Node* current = header->link;
            while (current != header) {
                Node* temp = current;
                current = current->link;
                delete temp;
            }
            header->link = header;
            
            current = a.header->link;
            while (current != a.header) {
                addTerm(current->coef, current->exp);
                current = current->link;
            }
        }
        return *this;
    }
   
    void addTerm(float coef, int exp) {
        if (coef == 0) return;  
        
        Node* prev = header;
        Node* current = header->link;
        
        while (current != header && current->exp > exp) {
            prev = current;
            current = current->link;
        }
        
        if (current != header && current->exp == exp) {
            current->coef += coef;
            if (current->coef == 0) { 
                prev->link = current->link;
                delete current;
            }
        } else {

            Node* newNode = new Node(coef, exp, current);
            prev->link = newNode;
        }
    }
    
    friend istream& operator>>(istream& is, Polynomial& x) {
        cout << "Enter number of terms: ";
        int numTerms;
        is >> numTerms;
        
        cout << "Enter terms (coefficient exponent pairs):\n";
        for (int i = 0; i < numTerms; i++) {
            float coef;
            int exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }
    
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.header->link;
        bool first = true;
        
        if (current == x.header) {
            os << "0";
            return os;
        }
        
        while (current != x.header) {
            if (!first && current->coef > 0) {
                os << " + ";
            } else if (current->coef < 0) {
                os << (first ? "-" : " - ");
            }
            
            float absCoef = (current->coef < 0) ? -current->coef : current->coef;
            
            if (current->exp == 0) {
                os << absCoef;
            } else if (current->exp == 1) {
                if (absCoef == 1 && !first) {
                    os << "x";
                } else if (absCoef == 1 && first) {
                    os << "x";
                } else {
                    os << absCoef << "x";
                }
            } else {
                if (absCoef == 1 && !first) {
                    os << "x^" << current->exp;
                } else if (absCoef == 1 && first) {
                    os << "x^" << current->exp;
                } else {
                    os << absCoef << "x^" << current->exp;
                }
            }
            
            first = false;
            current = current->link;
        }
        return os;
    }
    
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        
        Node* current = header->link;
        while (current != header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        current = b.header->link;
        while (current != b.header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        return result;
    }
    
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        
        Node* current = header->link;
        while (current != header) {
            result.addTerm(current->coef, current->exp);
            current = current->link;
        }
        
        current = b.header->link;
        while (current != b.header) {
            result.addTerm(-current->coef, current->exp);
            current = current->link;
        }
        
        return result;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        
        Node* current1 = header->link;
        while (current1 != header) {
            Node* current2 = b.header->link;
            while (current2 != b.header) {
                float newCoef = current1->coef * current2->coef;
                int newExp = current1->exp + current2->exp;
                result.addTerm(newCoef, newExp);
                current2 = current2->link;
            }
            current1 = current1->link;
        }
        
        return result;
    }

    float Evaluate(float x) const {
        float result = 0;
        Node* current = header->link;
        
        while (current != header) {
            float termValue = current->coef * pow(x, current->exp);
            result += termValue;
            current = current->link;
        }
        
        return result;
    }
    
    bool isEmpty() const {
        return header->link == header;
    }
    
    void clear() {
        Node* current = header->link;
        while (current != header) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        header->link = header;
    }
};

int main() {
    Polynomial p1, p2;
    
    cout << "Enter polynomial P1:\n";
    cin >> p1;
    cout << "P1 = " << p1 << "\n";
    
    cout << "Enter polynomial P2:\n";
    cin >> p2;
    cout << "P2 = " << p2 << "\n";
    
    cout << "P1 + P2 = " << p1 + p2 << "\n";
    cout << "P1 - P2 = " << p1 - p2 << "\n";
    cout << "P1 * P2 = " << p1 * p2 << "\n";
      
    return 0;
}
```
## 效能分析

1. 時間複雜度：

    AddTerm()：O(n)

    加減法：O(n + m)

    乘法：O(n * m)

    Evaluate()：O(n)

2. 空間複雜度：

    儲存空間：O(n)，其中n為多項式的項目數

## 測試與驗證

### 測試案例

input 

// P1 = 3x^2 + 2x + 1

p1.addTerm(3, 2);

p1.addTerm(2, 1);

p1.addTerm(1, 0);
    
// P2 = 2x^3 - x + 4

p2.addTerm(2, 3);

p2.addTerm(-1, 1);

p2.addTerm(4, 0);
    
output

P1 = 3x^2 + 2x + 1

P2 = 2x^3 - x + 4

P1 + P2 = 2x^3 + 3x^2 + x + 5

P1 - P2 = -2x^3 + 3x^2 + 3x - 3

P1 * P2 = 6x^5 + 4x^4 - x^3 + 10x^2 + 7x + 4

### 編譯與執行指令
```shell
$ g++ -o polynomial polynomial.cpp  
$./polynomial
```

### 結論

這C++多項式類別實作展現了完整且高效的資料結構設計。程式採用環形鏈結串列配合header節點的架構，不僅節省記憶體空間更避免了NULL指標判斷。所有的核心功能包括加減乘運算、輸入輸出操作及evaluate求值功能均完整實作，並能正確處理正負指數和常數項等各種複雜場景。

## 申論及開發報告

1. **header節點**  

    使用header節點的環形鏈結串列(header->link = header)，解決了空串列和邊界條件問題。
   
2.  **記憶體部分** 

    利用了建構子、解構子、拷貝建構子和賦值運算子的形成這是完整的RAII體系。

3.  **addTerm()**  
  
    addTerm()是整個類別的核心包含了基本運算(加減乘)、evaluate。
