# 41141106

作業一

Problem 1: Ackermann Function

## 解題說明

本題說明Ackermann 函數是一種極端增長的遞迴函數，常用於研究遞迴函數的運作效率與極限。
題目要求實作遞迴版本 的 Ackermann 函數和非遞迴版本的演算法。
Ackermann 函數定義如下：
    A(0, n) = n + 1
    A(m, 0) = A(m-1, 1)，當 m > 0
    A(m, n) = A(m-1, A(m, n-1))，當 m > 0 且 n 

### 解題策略

遞迴版本:
    若 m = 0，則回傳 n + 1；
    若 n = 0，則回傳 A(m-1, 1)；
    否則回傳 A(m-1, A(m, n-1))。

非遞迴版本:
    Ackermann 函數本質上是高度遞迴的，直接用迴圈無法處理其巢狀呼叫，因此需用「手動模擬遞迴」的方式。

## 程式實作

遞迴版本：
```cpp
#include <iostream>
using namespace std;

int Ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return Ackermann(m - 1, 1);
    else
        return Ackermann(m - 1, Ackermann(m, n - 1));
}

int main() {
    int m = 1;
    int n = 1;

    cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m, n) << endl;
    return 0;
}
```

非遞迴版本：
```cpp
#include <iostream>
using namespace std;

int AckermannIterative(int m, int n) {
    const int MAX = 1000; // 根據需求可調整
    int mStack[MAX];
    int top = -1;

    mStack[++top] = m;

    while (top >= 0) {
        m = mStack[top--];

        if (m == 0)
            n = n + 1;
        else if (n == 0) {
            n = 1;
            mStack[++top] = m - 1;
        } else {
            mStack[++top] = m - 1;
            mStack[++top] = m;
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 1;
    int n = 1;

    cout << "Ackermann (non-recursive)(" << m << ", " << n << ") = " << AckermannIterative(m, n) << endl;
    return 0;
}
```
## 效能分析
遞迴
1. 時間複雜度：O(A(m,n))
2. 空間複雜度：O(A(m,n))

非遞迴
1. 時間複雜度：O(A(m,n))
2. 空間複雜度：O(A(m,n))

## 測試與驗證

### 測試案例

| 測試案例 | 輸入(m,n) | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | m=1 n=1      | 3        | 3        |
| 測試二   | m=2 n=1      | 5        | 5        |
| 測試三   | m=2 n=2      | 7        | 7        |
| 測試四   | m=3 n=2      | 29       | 29       |
| 測試五   | m=3 n=3      | 61       | 61       |

### 編譯與執行指令
```shell
$ ./ackermann_recursive
Ackermann(1, 1) = 3

$ ./ackermann_nonrecursive
Ackermann(non-recursive)(1, 1) = 3
```

### 結論

1. 遞迴版本實作簡單、清晰，但不適合處理 m 或 n 較大的情況，容易導致堆疊溢位。  
2. 非遞迴版本結構較複雜，但在應用中具有安全性與穩定性。


## 申論及開發報告

1. **遞迴與非遞迴之比較學習**  
    遞迴版本雖然結構直觀，但在輸入值較大時會導致堆疊溢位；透過非遞迴的 stack 模擬方法，可有效減少系統呼叫層數，提升執行穩定性。
2. **增進堆疊邏輯理解**  
    非遞迴版本的實作過程，訓練了我使用 stack 模擬呼叫堆疊的邏輯，理解每次函數呼叫對變數狀態的影響，是程式控制流程設計的實作訓練。

Problem 2: Powerset Generation

## 解題說明
本題要求撰寫一個遞迴函數來計算一個集合𝑆。
S的冪集合（Power Set）。所謂冪集合，是指所有「子集合」的集合，包含空集合與集合本身。

### 解題策略
給定一個集合 𝑆（包含 n 個元素）。
任一個元素都有「選或不選」兩種選擇，所以總共會有$(2^n)$種子集合，需使用遞迴方式依序列出所有子集合。

## 程式實作

```cpp
#include <iostream>
#include <string>
using namespace std;

void generatePowerSet(char set[], int n, int index, string current) {
    if (index == n) {
        if (current.empty())
            cout << "{}" << endl;
        else
            cout << "{ " << current << "}" << endl;
        return;
    }


    generatePowerSet(set, n, index + 1, current);

    generatePowerSet(set, n, index + 1, current + set[index] + " ");
}

int main() {
    char S[] = {'a', 'b', 'c'};
    int size = 3;

    cout << "Power Set of {a, b, c}:" << endl;
    generatePowerSet(S, size, 0, "");

    return 0;
}
```

## 效能分析

1. 時間複雜度：O($(2^n)$⋅n)
2. 空間複雜度：O(n)

## 測試與驗證

### 測試案例
測試案例：S = {a, b, c}

預期輸出：{{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}

實際輸出：{{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}

### 編譯與執行指令

```shell
$ ./powerset
Power Set of {a, b, c}:
{}
{c }
{b }
{b c }
{a }
{a c }
{a b }
{a b c }
```

### 結論
1. 程式使用遞迴將問題拆解為更小的子問題，理解與實作 power set 是一種自然的方式。  
2. 完整列出所有子集合，包含空集合與原集合本身，總共有$(2^n)$個子集合。

## 申論及開發報告
1. **組合邏輯與遞迴設計**  
    Powerset是組合展開問題，透過遞迴實現「每個元素選或不選」的二元選擇邏輯，是遞迴設計的經典應用之一。
2. **驗證測試與時間複雜度分析**  
    對集合 {a, b, c} 執行 powerset 測試，預期產生 8 種子集合，結果與預期一致；並分析時間複雜度為 
𝑂($(2^n)$⋅𝑛)。